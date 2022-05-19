/*////////////////////////////////////////////////////////////////////////
Copyright (c) 2014 National Institute of Advanced Industrial Science and Technology (AIST)
AIST-Product-ID: 2000-ETL-198715-01, H14PRO-049, H15PRO-165, H18PRO-443

Permission to use this material for noncommercial and/or evaluation
purpose, copy this material for your own use, and distribute the copies
via publicly accessible on-line media, without fee, is hereby granted
provided that the above copyright notice and this permission notice
appear in all copies.
AIST MAKES NO REPRESENTATIONS ABOUT THE ACCURACY OR SUITABILITY OF THIS
MATERIAL FOR ANY PURPOSE.  IT IS PROVIDED "AS IS", WITHOUT ANY EXPRESS
OR IMPLIED WARRANTIES.
/////////////////////////////////////////////////////////////////////////
Content-Type:	program/C; charset=US-ASCII
Program:	htstat.c
Author:		Yutaka Sato <ysato@delegate.org>
Description:
History:
	140515	created /* new-140515a */
//////////////////////////////////////////////////////////////////////#*/
#include "ystring.h"
#include "delegate.h"
#include "fpoll.h"
#include "file.h"
#include "proc.h"
#include "http.h"
#include "auth.h"

#define ME_7bit		((char*)0)

#define MAXARGS		256		/* given as arg1&arg2& ... */
#define HLNSIZ		(2*URLSZ)	/* max. length of a line in PROTOLOG file */
#define MAXLINES	10000		/* max. lines in a HTML page */
#define MAXBYTES	(1024*1024)	/* max. page size for a HTML page, 1MB */

extern const char *DELEGATE_LOGFILE;
extern const char *DELEGATE_PROTOLOG;
void logurl_escapeX(PCStr(src),PVStr(dst),int siz);
int StrSubstDateXX(PVStr(str),PVStr(cur),int now);
int scanftime(PCStr(stime),PCStr(fmt));
int strCRC32(PCStr(str),int len);
static const char *defaultArgs = "lines=20&size=100&exclude=301,404,500";

typedef struct _protolog {
	MStr(pl_name,16);
	MStr(pl_path,256-16);
} ProtoLog;
static ProtoLog *PROTOLOGV;
static int PROTOLOGN;
static int PROTOLOGX;

/*
 * HTSTATS="pl:Name[,Option]:Path"  -- PROTOLOG
 *   Example -- HTSTATS="protolog:http:log[date+/y%Y/%m/%d]/80.http"
 *   Option -- baseurl{http://server/}
 * HTSTATS="lf:Name[,Option]:Path"  -- LOGFILE
 * HTSTATS="hf:Command-Line-Option:Path-Of-History-Filter-Command"
 */
void scan_HTSTATS(Connection *Conn,PCStr(spec)){
	IStr(name,16);
	IStr(value,256);
	IStr(opts,256);
	IStr(path,256);
	int ival;

	fieldScan(spec,name,value);
	ival = atoi(value);

	if( strcaseeq(name,"pl") ){
		ProtoLog *pl;
		fieldScan(value,opts,path);
		if( PROTOLOGV == 0 ){
			PROTOLOGN = 8;
			PROTOLOGX = 0;
			PROTOLOGV = (ProtoLog*)calloc(PROTOLOGN,sizeof(ProtoLog));
		}
		if( 8 <= PROTOLOGX ){
			syslog_ERROR("FATAL: too many PROTOLOG specified.\n");
			return;
		}
		pl = &PROTOLOGV[PROTOLOGX++];
		strcpy(pl->pl_name,opts);
		strcpy(pl->pl_path,path);
	}else
	if( strcaseeq(name,"max-history-pagesize") ){
		/*
		MAXBYTES = ival;
		 */
	}else
	if( strcaseeq(name,"max-history-pagelines") ){
		/*
		MAXLINES = ival;
		 */
	}else{
		syslog_ERROR("ERROR: HTSTATS=(unknown spec)%s:%s\n",name,value);
	}
}
/*
 * the evaluated path name of the PROTOLOG file
 */
static const char *HISTORYPATH(Connection *Conn,PCStr(name),PVStr(path),int date){
	IStr(lpath,URLSZ);
	refQStr(fmp,path);

	if( PROTOLOGV ){
		strcpy(path,PROTOLOGV[0].pl_path);
	}else{
		strcpy(path,DELEGATE_PROTOLOG);
	}
	if( fmp = strchr(path,':') )
		setVStrEnd(fmp,0);
	DELEGATE_substfile(AVStr(path),CLNT_PROTO,VStrNULL,VStrNULL,VStrNULL);
	StrSubstDateXX(BVStr(path),AVStr(lpath),date);
	return path;
}

typedef struct _Maxima {
	MStr(mx_name,32);
	int	 mx_min;
	int	 mx_dflt;
	int	 mx_max;
} Maxima;

typedef struct _statsEnv {
	int	 se_argc;
    const char	*se_argv[MAXARGS];
	MStr(	 se_argbuf,1024);
	defQStr( se_argp);
	int	 se_maximac;
	Maxima	 se_maximav[64];
	FileSize se_history_begin;
	FileSize se_history_end;
	int	 se_islatest; /* current history is the latest one */
	MStr(	 se_message,1024);
	MStr(	 se_emessage,1024);
} StatsEnv;

/*
 * Maxima specified in DHTML as ${maxima.min,dflt,max}
 */
static int setMaxima(StatsEnv *StE,PCStr(name),int min,int dflt,int max){
	if( elnumof(StE->se_maximav) <= StE->se_maximac ){
		return -1;
	}else{ 
		strcpy(StE->se_maximav[StE->se_maximac].mx_name,name);
		StE->se_maximav[StE->se_maximac].mx_min  = min;
		StE->se_maximav[StE->se_maximac].mx_dflt = dflt;
		StE->se_maximav[StE->se_maximac].mx_max  = max;
		StE->se_maximac += 1;
		return 0;
	}
}
static int getMaxima(StatsEnv *StE,PCStr(name),int *min,int *dflt,int *max){
	int mi;
	for( mi = 0;  mi < StE->se_maximac; mi++ ){
		if( streq(StE->se_maximav[mi].mx_name,name) ){
			if( min ) *min = StE->se_maximav[mi].mx_min;
			if( dflt) *dflt= StE->se_maximav[mi].mx_dflt;
			if( max ) *max = StE->se_maximav[mi].mx_max;
			return 1;
		}
	}
	return 0;
}
static int limitVal(StatsEnv *StE,PCStr(name),PCStr(oval),PVStr(nval)){
	int min = 0;
	int dflt = 0;
	int max = 0;

	if( oval )
		strcpy(nval,oval);
	else	strcpy(nval,"");
	if( getMaxima(StE,name,&min,&dflt,&max) ){
		if( oval == 0 || *oval == 0 ){
			sprintf(nval,"%d",dflt);
		}else
		if( atoi(oval) < min ){
			sprintf(nval,"%d",min);
		}else
		if( max < atoi(oval) ){
			sprintf(nval,"%d",max);
		}else{
			sprintf(nval,"%d",atoi(oval));
		}
	}
	return atoi(nval);
}
static int limit(StatsEnv *StE,PCStr(name),PCStr(oval)){
	IStr(nval,128);
	return limitVal(StE,name,oval,AVStr(nval));
}
static int setformv(StatsEnv *StE,PCStr(name),PCStr(value)){
	int nlen = strlen(name);
	int ai;
	const char *arg1;
	int nset = 0;
	int min = 0;
	int dflt = 0;
	int max = 0;
	IStr(param,1024);

	for( ai = 0; arg1 = StE->se_argv[ai]; ai++ ){
		getMaxima(StE,name,&min,&dflt,&max);
		if( strneq(arg1,name,nlen) && arg1[nlen] == '=' ){
			if( strcaseeq(value,"${dflt}") ){
				sprintf(param,"%s=%d",name,dflt);
			}else
			if( strcaseeq(value,"${min}") ){
				sprintf(param,"%s=%d",name,min);
			}else
			if( strcaseeq(value,"${max}") ){
				sprintf(param,"%s=%d",name,max);
			}else{
				sprintf(param,"%s=%s",name,value);
			}
			StE->se_argv[ai] = StE->se_argp;
			strcpy(StE->se_argp,param);
			StE->se_argp += strlen(StE->se_argp) + 1;
			nset += 1;
		}
	}
	return nset;
}
static int unsetformv(StatsEnv *StE,PCStr(name)){
	int nlen = strlen(name);
	const char *arg1;
	int ndel = 0;
	int ai;
	int ax = 0;

	for( ai = 0; arg1 = StE->se_argv[ai]; ai++ ){
		if( strneq(arg1,name,nlen) && arg1[nlen] == '=' ){
			ndel += 1;
			continue;
		}
		StE->se_argv[ax++] = StE->se_argv[ai];
	}
	return 0;
}

/*
 * reverse MOUNT to show the virtual URL from the viewpoint of clients.
 */
static const char *revMount(Connection *Conn,PCStr(url),PVStr(xurl)){
	IStr(proto,MaxHostNameLen);
	IStr(site,MaxHostNameLen);
	IStr(upath,URLSZ);
	const char *mopt;
	IStr(dgproto,MaxHostNameLen);
	IStr(dghost,MaxHostNameLen);

	strcpy(dgproto,"http");
	strcpy(dghost,"DeleGate");
	if( *url == '/' ){
		/* vhost, nvhost MountOption should be used for dghost */
		mopt = CTX_mount_url_fromL(Conn,BVStr(xurl),
			"file","localhost",url+1,0,dgproto,dghost);
		if( mopt != NULL ){
			decomp_absurl(xurl,AVStr(proto),AVStr(site),
				AVStr(upath),sizeof(upath));
			sprintf(xurl,"/%s",upath);
		}else
		if( strneq(url,"/-/",3) ){
			sprintf(xurl,"%s",upath);
			mopt = "";
		}
	}else{
		decomp_absurl(url,AVStr(proto),AVStr(site),AVStr(upath),
			sizeof(upath));
		if( strneq(upath,"-/",2) ){
			sprintf(xurl,"/%s",upath);
			return "";
		}
		mopt = CTX_mount_url_fromL(Conn,BVStr(xurl),proto,site,upath,0,
			dgproto,dghost);
		if( mopt ){
			decomp_absurl(xurl,AVStr(proto),AVStr(site),
				AVStr(upath),sizeof(upath));
			if( streq(dgproto,proto) && strcaseeq(dghost,site) ){
				sprintf(xurl,"/%s",upath);
			}
		}else
		if( strneq(upath,"-/",2) ){
			sprintf(xurl,"/%s",url);
			mopt = "";
		}
	}
	return mopt;
}

/*
 * data: URL interpreter for User Agents without the support (MSIE)
 */
int UAwithDataURL(PCStr(UA)){
	if( strstr(UA,"MSIE ") ){ return 0; }
	if( strstr(UA,"Chrome/") 
	 || strstr(UA,"Firefox/")
	 || strstr(UA,"Safari/")
	){
		return 1;
	}
	return 0;
}
int toDataURL(Connection *Conn,PCStr(data),PVStr(dataURL)){
	IStr(UAesc,URLSZ);

	logurl_escapeX(data,AVStr(UAesc),sizeof(UAesc));
	if( UAwithDataURL(REQ_UA) ){
		sprintf(dataURL,"data:;,%s",UAesc);
	}else{
		sprintf(dataURL,"-/data:;,%s",UAesc);
	}
	return 1;
}
int toDataURLlink(Connection *Conn,PCStr(url),PVStr(linkURL)){
	IStr(datasrc,URLSZ);
	IStr(escurl,URLSZ);

	logurl_escapeX(url,AVStr(escurl),sizeof(escurl));
	sprintf(datasrc,"<a href=%s>%s</a>",escurl,escurl);
	if( UAwithDataURL(REQ_UA) ){
		sprintf(linkURL,"data:text/html;,%s",datasrc);
	}else{
		sprintf(linkURL,"-/data:text/html;,%s",datasrc);
	}
	return 1;
}

#define sgetv(name)	getv(StE->se_argv,name)

/*
 * PROTOLOG filter
 */
static int filter_history(Connection *Conn,FILE *in,FILE *out,StatsEnv *StE,int myhost,int sizeB,int lines){
	int hsizeB = 0;
	int iln;
	IStr(iline,HLNSIZ);
	IStr(quser,HLNSIZ);
	IStr(qauth,HLNSIZ);
	IStr(hreq,HLNSIZ);
	IStr(url,HLNSIZ);
	IStr(xurl,HLNSIZ);
	IStr(oline,HLNSIZ);
	IStr(referer,HLNSIZ);
	IStr(UA,HLNSIZ);
	IStr(UAdata,HLNSIZ);
	IStr(host,MaxHostNameLen);
	IStr(method,256);
	int xhost;
	IStr(date,128);
	IStr(hver,128);
	int hcode = 0;
	int hsize = 0;
	int itime = 0;
	IStr(stime,128);
	const char *fval;
	const char *Exclude;
	const char *Include;
	int simplefmt = 0;
	int hideday = 0;
	int hidehost = 0;
	int hidemethod = 0;
	int hidecode = 0;
	int hidereferer = 0;
	int hideagent = 0;
	int mineonly = 0;
	int excludemine = 0;
	const char *timefmt;
	const char *URLinc;
	const char *URLexc;
	int hshown = 0;
	int hbroken = 0;
	int hexcluded = 0;
	FileSize fend;

	if( (fval = sgetv("simplefmt"))   && *fval ) simplefmt = 1;
	if( (fval = sgetv("hideday"))     && *fval ) hideday = 1;
	if( (fval = sgetv("hidehost"))    && *fval ) hidehost = 1;
	if( (fval = sgetv("hidemethod"))  && *fval ) hidemethod = 1;
	if( (fval = sgetv("hidecode"))    && *fval ) hidecode = 1;
	if( (fval = sgetv("hidereferer")) && *fval ) hidereferer = 1;
	if( (fval = sgetv("hideagent"))   && *fval ) hideagent = 1;
	if( (fval = sgetv("mineonly"))    && *fval ) mineonly  = 1;
	if( (fval = sgetv("excludemine")) && *fval ) excludemine = 1;
	Include = sgetv("includes");
	Exclude = sgetv("excludes");
	URLinc = sgetv("URLinc");
	URLexc = sgetv("URLexc");

	fprintf(out,"<input type=hidden name=history_begin value=%llu>\n",Ftello(in));
	StE->se_history_begin = Ftello(in);
	fprintf(out,"<pre><font face=\"courier new\">");

	for( iln = 0; iln < lines && fgets(iline,sizeof(iline),in) != NULL; iln++ ){
		if( sizeB <= hsizeB+strlen(iline) ){
			break;
		}
		hsizeB += strlen(iline);

		setVStrEnd(referer,0);
		setVStrEnd(UA,0);
		strsubst(AVStr(iline),"\"\"","\"-\"");

		Xsscanf(iline,
		"%s %s %s [%[^]]] \"%[^\"\r\n]\" %d %d \"%[^\"]\" \"%[^\"]\"",
			AVStr(host),AVStr(quser),AVStr(qauth),
			AVStr(date),AVStr(hreq),&hcode,&hsize,
			AVStr(referer),AVStr(UA));
		Xsscanf(hreq,"%s %s %s",AVStr(method),AVStr(url),AVStr(hver));

		if( streq(referer,"-") ) setVStrEnd(referer,0);
		if( streq(UA,"-") )      setVStrEnd(UA,0);

		if( hreq[0] == 0 || hcode == 0 ){
			hbroken += 1;
			continue;
		}
		/*
		if( streq(method,"ERR") ){
			hbroken += 1;
			continue;
		}
		*/

		if( Include && *Include ){
			IStr(shcode,128);
			sprintf(shcode,"%d",hcode);
			if( !strstr(Include,shcode) ){
				hexcluded += 1;
				continue;
			}
		}else
		if( Exclude && *Exclude ){
			IStr(shcode,128);
			sprintf(shcode,"%d",hcode);
			if( strstr(Exclude,shcode) ){
				hexcluded += 1;
				continue;
			}
		}
		itime = scanftime(date,TIMEFORM_HTTPD);
		if( hideday || simplefmt )
			timefmt = "%H:%M:%S";
		else	timefmt = "%m/%d-%H:%M:%S";
		StrftimeLocal(AVStr(stime),sizeof(stime),timefmt,itime,0);
		xhost = strCRC32(host,strlen(host)) & 0xFFFF;

		if( excludemine && xhost == (myhost & 0xFFFF) ){
			hexcluded += 1;
			continue;
		}
		if( mineonly && xhost != (myhost & 0xFFFF) ){
			hexcluded += 1;
			continue;
		}
		if( revMount(Conn,url,AVStr(xurl)) ){
			strcpy(url,xurl);
		}
		if( URLinc && *URLinc ){
			if( isinListX(URLinc,url,"s") ){
			}else{
				hexcluded += 1;
				continue;
			}
		}
		if( URLexc && *URLexc ){
			if( isinListX(URLexc,url,"s") ){
				hexcluded += 1;
				continue;
			}else{
			}
		}

		hshown += 1;
		logurl_escapeX(url,AVStr(xurl),sizeof(xurl));
		strcpy(url,xurl);

		sprintf(oline,"%s",stime);
		if( !hidehost && !simplefmt ){
			Xsprintf(TVStr(oline)," %04x",xhost);
		}
		if( !hidemethod && !simplefmt ){
			Xsprintf(TVStr(oline)," %c",*method);
		}
		if( !hidecode && !simplefmt ){
			Xsprintf(TVStr(oline)," %3d",hcode);
		}
		if( hidereferer || simplefmt ){
		}else
		if( *referer ){
			IStr(refdata,URLSZ);
			toDataURLlink(Conn,referer,AVStr(refdata));
			Xsprintf(TVStr(oline)," <a href=\"%s\">R</a>",refdata);
		}else{
			Xsprintf(TVStr(oline)," -");
		}

		if( hideagent || simplefmt ){
		}else
		if( *UA ){
			toDataURL(Conn,UA,AVStr(UAdata));
			Xsprintf(TVStr(oline)," <a href=\"%s\">U</a>",UAdata);
		}else{
			Xsprintf(TVStr(oline)," -");
		}
		Xsprintf(TVStr(oline)," <a href=\"%s\">%s</a>\r\n",url,url);
		fputs(oline,out);
	}
	fprintf(out,"</font></pre>\n");
	fend = Ftello(in) - 1;
	if( fend < 0 ){
		fend = 0;
	}
	fprintf(out,"<input type=hidden name=history_end value=%llu>\n",fend);
	StE->se_history_end = fend;
	fflush(out);

		sprintf(StE->se_message,"scanned %d lines / %.3f KB (%d shown, %d excluded, %d broken)\n",
		iln,hsizeB/1000.0,hshown,hexcluded,hbroken);
	return hsizeB;
}

/*
 * Seek to the first line of specified date/time in a PROTOLOG.
 */
static int cueingByDateSmall(FILE *hfp,int fromtime,PVStr(iline)){
	IStr(pline,HLNSIZ);
	IStr(idate,128);
	int ltime;
	FileSize off;
	FileSize coff;
	int iln;

	coff = Ftello(hfp);
	for( iln = 0; ; iln++ ){
		off = Ftello(hfp);
		if( fgets(pline,sizeof(pline),hfp) == NULL ){
			break;
		}
		strcpy(iline,pline);
		coff = off;
		Xsscanf(iline,"%*s %*s %*s [%[^]]]",AVStr(idate));
		ltime = scanftime(idate,TIMEFORM_HTTPD);
		if( fromtime <= ltime ){
			Fseeko(hfp,off,0);
			break;
		}
	}
	Fseeko(hfp,coff,0);
	return 0;
}
static int cueingByDate(FILE *hfp,int fromtime){
	IStr(sftime,128);
	IStr(sltime,128);
	IStr(iline,HLNSIZ);
	IStr(idate,128);
	int ltime;
	FileSize coff;
	FileSize noff;
	FileSize size = file_sizeX(fileno(hfp));
	FileSize range;
	int iln;

	StrftimeLocal(AVStr(sftime),sizeof(sftime),"%y/%m/%d-%H:%M:%S",fromtime,0);
		sv1log("HTSTATS.h: search time[%s] size=%llu\n",sftime,size);

	if( size < 256*1024 ){
		return cueingByDateSmall(hfp,fromtime,AVStr(iline));
	}
	range = size / 2;
	Fseeko(hfp,range,0);
	for( ; 128*1024 < range; range /= 2 ){
		fgets(iline,sizeof(iline),hfp);
		coff = Ftello(hfp);
		fgets(iline,sizeof(iline),hfp);

		Xsscanf(iline,"%*s %*s %*s [%[^]]]",AVStr(idate));
		ltime = scanftime(idate,TIMEFORM_HTTPD);
		if( 0 ){
			StrftimeLocal(AVStr(sltime),sizeof(sltime),
				"%y/%m/%d-%H:%M:%S",ltime,0);
		sv1log("HTSTATS.h: bsearch off=%8llu range=%8u [%s] ? %d\n",
				coff,range,sltime,fromtime<ltime);
		}

		if( fromtime < ltime ){
			noff = Ftello(hfp) - range / 2;
		}else{
			noff = Ftello(hfp) + range / 2;
		}
		Fseeko(hfp,noff,0);
	}
	if( 256*1024 < Ftello(hfp) )
		noff = Ftello(hfp) - 256*1024;
	else	noff = 0;
	Fseeko(hfp,noff,0);
	cueingByDateSmall(hfp,fromtime,AVStr(iline));

	if( 1 ){
		Xsscanf(iline,"%*s %*s %*s [%[^]]]",AVStr(idate));
		ltime = scanftime(idate,TIMEFORM_HTTPD);
		StrftimeLocal(AVStr(sltime),sizeof(sltime),
			"%y/%m/%d-%H:%M:%S",ltime,0);
		sv1log("HTSTATS.h: bserach off=%8llu range=%8u [%s] = %d\n",
			Ftello(hfp),range,sltime,fromtime<ltime);
	}
	return 0;
}
/*
 * Seek to the line of which position is less than size/lines.
 */
int tailLines(FILE *tmp,int lines,int endoff){
	IStr(line,HLNSIZ);
	FileSize savoff;
	FileSize curoff;
	FileSize offv[MAXLINES+1];
	int iln;
	int ilx = 0;
	int jlx;

	savoff = Ftello(tmp);
	for( iln = 0; ; iln++ ){
		curoff = Ftello(tmp);
		if( endoff && endoff <= curoff ){
			break;
		}
		offv[ilx] = curoff;
		if( fgets(line,sizeof(line),tmp) == NULL ){
			break;
		}
		ilx = (ilx + 1) % elnumof(offv);
	}
	clearerr(tmp);

	if( iln < lines ){
 sv1log("HTSTAS; DEBUG: taiLine -- case 1 (iln=%d < lines=%d)\n",iln,lines);
		Fseeko(tmp,savoff,0);
	}else{
		if( ilx < elnumof(offv) ){
			jlx = ilx - lines;
			if( jlx < 0 ){
 sv1log("HTSTAS; DEBUG: taiLine -- case 2 (jlx=%d < 0) ilx=%d lines=%d\n",jlx,ilx,lines);
				jlx = 0;
			}else{
				/* usual case */
			}
		}else{
			jlx = elnumof(offv)-1 - (lines - ilx); 
 sv1log("HTSTAS; DEBUG: taiLine -- case 3 (ilx=%d jlx=%d)\n",ilx,jlx);
		}
		Fseeko(tmp,offv[jlx],0);
	}
	return iln;
}
static int cueingLastPage(StatsEnv *StE,PCStr(act),FILE *hfp,FileSize fsize,int fileId,FileSize fbegin,FileSize fend,FileSize sizeKB,int lines){
	IStr(hline,HLNSIZ);
	FileSize noff;

	const char *fval;
	int ifval = 0;

	if( fval = sgetv("fileId") ){
		sscanf(fval,"%X",&ifval);
	}
	if( ifval != fileId ){
		sv1log("HTSTATS.h: reset offsets(%llu - %llu), file changed (%X != %X)\n",fbegin,fend,ifval,fileId);
		fbegin = fend = 0;
	}

	noff = fsize - sizeKB*1000;
	if( 0 < fend && 0 < fbegin && fsize <= fend ){
		noff = fbegin;
		if( act && streq(act,"TAIL") ){
		strcpy(StE->se_emessage,"You are already at the end of the history.");
		}
	}
	if( 0 <= noff ){
		Fseeko(hfp,noff,0);
		if( noff == fbegin ){
			/* fbegin points the top of line */
		}else{
			fgets(hline,sizeof(hline),hfp); /* discard the odd line */
		}
	}
	tailLines(hfp,lines,0);
	return 0;
}

/*
 * time format scanner
 */
int dHMtoSec(PCStr(dHM)){
	int day = 0;
	int hour = 0;
	int min = 0;

	sscanf(dHM,"%d-%d-%d",&day,&hour,&min);
	return day*24*60*60 + hour*60*60 + min*60;
}
int HHMMtoSec(PCStr(hhmm)){
	int hour = 0;
	int min = 0;
	sscanf(hhmm,"%d-%d",&hour,&min);
	return (hour*60 + min)*60;
}
int ymdHMStoi(PCStr(sdate),PCStr(stime)){
	int itime = 0;
	IStr(hdate,128);
	IStr(nsdate,128);
	IStr(nstime,128);
	int y = 0;
	int m = 0;
	int d = 0;
	int H = 0;
	int M = 0;
	int S = 0;

	sscanf(sdate,"%u-%u-%u",&y,&m,&d);
	sprintf(nsdate,"%02d-%02d-%02d",y%100,m%13,d%32);
	sscanf(stime,"%u-%u-%u",&H,&M,&S);
	sprintf(nstime,"%02d-%02d-%02d",H%60,M%60,S%60);
	sprintf(hdate,"%s %s %s",nsdate,nstime,"+900");
	itime = scanftime(hdate,"%y-%m-%d %H-%M-%S %z");
	return itime;
}
int formv2str(const char *argv[],PVStr(buf)){
	int ai;
	int ax = 0;
	const char *arg1;
	refQStr(bp,buf);

	for( ai = 0; arg1 = argv[ai]; ai++ ){
		if( strncaseeq(arg1,"act=",4) ){
			/* to be excluded as formv.ALL.not.act */
			continue;
		}
		/* must escape &<>% */
		if( bp == buf )
			sprintf(bp,"%s",arg1);
		else	sprintf(bp,"&%s",arg1);
		bp += strlen(bp);
		ax += 1;
	}
	return ax;
}

/*
 * the interpreter of ${name.arg} referred in history.dhtml
 */
int DHTML_printStats(Connection *Conn,FILE *fp,PCStr(fmt),PCStr(name),PCStr(arg),StatsEnv *StE){
	const char *act = sgetv("act");
	IStr(path,URLSZ);
	IStr(valb,URLSZ);

	const char *fval;
	IStr(arg1,URLSZ);
	const char *arg2;
	int eqop = 0;

	if( arg2 = wordScanY(arg,arg1,"^.") ){
		if( *arg2 == '.' ){
			eqop = 1;
			arg2++;
		}
	}
	if( strcaseeq(name,"formv") && strcaseeq(arg1,"ALL") ){
		if( fp ){
			IStr(buf,URLSZ);
			refQStr(bp,buf);
			int ai;
			const char *arg1;

			if( strcaseeq(arg2,"hidden") ){
				for( ai = 0; ai < StE->se_argc; ai++ ){
					IStr(name,256);
					IStr(value,256);

					arg1 = StE->se_argv[ai];

					/* to be removed */ {
					  if( strncaseeq(arg1,"act=",4)
					   || strncaseeq(arg1,"talt=",5)
					   || strncaseeq(arg1,"ago=",4)
					   || strncaseeq(arg1,"fromdate=",9)
					   || strncaseeq(arg1,"fromtime=",9)
					  ){
						/* formv.ALL.hidden is called only from Cueing currently.
						 * so ignore input exist in Cueing.
						 */
						continue;
					  }
					}

		Xsscanf(arg1,"%[^=]=%[^\r\n]",AVStr(name),AVStr(value));
		sprintf(bp,"<input type=hidden name=%s value=\"%s\">\r\n",name,value);
					bp += strlen(bp);
				}
			}else{
				formv2str(StE->se_argv,AVStr(buf));
			}
			fprintf(fp,"%s",buf);
		}
		return StE->se_argc;
	}
	if( strcaseeq(name,"maxima") ){
		int min = 0,dflt = 0,max = 0;
		sscanf(arg2,"%d,%d,%d",&min,&dflt,&max);
		setMaxima(StE,arg1,min,dflt,max);
		if( fp ) fprintf(fp,"{maxima %s min=%d default=%d max=%d}",
				arg1,min,dflt,max);
		return 1;
	}
	if( strcaseeq(name,"limit") ){
		if( fp ) fprintf(fp,"%d",limit(StE,arg,sgetv(arg)));
		return 1;
	}
	if( strcaseeq(name,"default") ){
		/* ... should set the values into StatsEnv ... */
		if( fp ) fprintf(fp,"{default %s %s}",arg1,arg2);
		return 1;
	}
	if( strcaseeq(name,"setformv") ){
		setformv(StE,arg1,arg2);
		return 1;
	}

	if( strcaseeq(arg1,"formv") ){
		fval = sgetv(arg2);
	}else
	if( strcaseeq(name,"formv") ){
		fval = sgetv(arg1);
	}else{
		fval = arg;
	}

	if( strcaseeq(name,"formv") ){
		if( fval ){
			if( fp ) fprintf(fp,"%s",fval);
			if( eqop ){
				return strcaseeq(fval,arg2);
			}else{
				return 1;
			}
		}else{
			return 0;
		}
	}else
	if( strcaseeq(name,"url") ){
		if( strcaseeq(arg,"self.relative") ){
			if( fp ) fprintf(fp,"history.dhtml");
		}else
		if( strcaseeq(arg,"self.full") ){
			IStr(url,URLSZ);
			const char *upath = "/-/stats/history.dhtml";
			HTTP_baseURLrelative(Conn,upath,AVStr(url));
			if( fp ) fprintf(fp,"%s",url);
		}
		return 1;
	}else
	if( strcaseeq(name,"auth") ){
		if( *arg == 0 ){
			if( fp ) fprintf(fp,"%s@%s",ClientAuthUser,ClientAuthHost);
			return *ClientAuthHost != 0;
		}else
		if( strcaseeq(arg,"user") ){
			if( fp ) fprintf(fp,"%s",ClientAuthUser);
			return *ClientAuthUser != 0;
		}else
		if( strcaseeq(arg,"host") ){
			if( fp ) fprintf(fp,"%s",ClientAuthHost);
			return *ClientAuthHost != 0;
		}
		return 0;
	}else
	if( streq(name,"message") ){
		if( streq(arg,"error") ){
			if( fp ) fprintf(fp,"%s",StE->se_emessage);
			return StE->se_emessage[0] != 0;
		}else{
			if( fp ) fprintf(fp,"%s",StE->se_message);
			return StE->se_message[0] != 0;
		}
	}else
	if( strcaseeq(name,"history") ){
		int sizeKB = 0;
		int lines = 0;
		int leng = 0;
		FileSize foff = 0; /* offset specified in the form */
		FileSize noff;
		FileSize fsize;
		FileSize fbegin;
		FileSize htill;
		FileSize fend;
		int fileId = 0;
		FILE *hfp;
		const char *soff = 0;
		int myhost = strCRC32(Client_Host,strlen(Client_Host));
		int fromtime = 0;
		IStr(sfromtime,128);
		IStr(lpath,URLSZ);
		const char *hname = "";

		if( streq(arg,"islatest") ){
			return StE->se_islatest;
		}else
		if( streq(arg,"begin") ){
			if( fp ) fprintf(fp,"%llu",StE->se_history_begin);
			return StE->se_history_begin;
		}else
		if( streq(arg,"end") ){
			if( fp ) fprintf(fp,"%llu",StE->se_history_end);
			return StE->se_history_end;
		}else
		if( act && strcaseeq(act,"Cueing") ){
			if( strcaseeq(arg1,"sinceago") ){
				const char *fago;
				if( fago = sgetv("ago") ){
					fromtime = time(0) - dHMtoSec(fago);
				}
			}else
			if( strcaseeq(arg1,"fromdate") ){
				fromtime = ymdHMStoi(sgetv("fromdate"),
					sgetv("fromtime"));
			}else
			if( strcaseeq(arg1,"last") ){
				fromtime = time(0);
			}else{
		sv1log("HTSTATS.h: ERROR: unknown Cueing[%s]\n",arg1);
			}
		}else{
			fromtime = time(0);
			if( fval = sgetv("CueingTime") ){
				sscanf(fval,"%u",&fromtime);
				if( strcaseeq(arg1,"last") ){
					HISTORYPATH(Conn,hname,AVStr(path),fromtime);
					HISTORYPATH(Conn,hname,AVStr(lpath),time(0));
					if( !streq(path,lpath) ){
		sv1log("HTSTATS.h: switched last to the latet\n");
		strcpy(StE->se_emessage,"Automaticaly switched to the latest history.");
						unsetformv(StE,"history_begin");
						unsetformv(StE,"history_end");
						fromtime = time(0);
					}
				}
			}
		}
		if( fromtime == -1 ){
			if( fp ){
				fprintf(fp,"Bad time specification.\n");
			}
			return 0;
		}
		StrftimeLocal(AVStr(sfromtime),sizeof(sfromtime),
			"%Y-%m-%d %H:%M:%S",fromtime,0);

		HISTORYPATH(Conn,hname,AVStr(path),fromtime);
		HISTORYPATH(Conn,hname,AVStr(lpath),time(0));
		if( streq(path,lpath) ){
			StE->se_islatest = 1;
		}else{
		}

		hfp = fopen(path,"r");
		sv1log("HTSTATS.h: putting act=%s [%s] %s path=%s\n",act?act:"NULL",
			sfromtime,hfp?"FOUND":"NOT FOUND",path);

		if( hfp == NULL ){
			IStr(etime,128);
			StrfTimeLocal(AVStr(etime),sizeof(etime),"%y%m%d-%H%M%S%.3s",Time());
			if( fp ){
				int compressed = 0;
				IStr(zpath,URLSZ);
				sprintf(zpath,"%s.gz",path);
				if( File_is(zpath) ){
					compressed = 1;
				}else{
					sprintf(zpath,"%s.bz2",path);
					if( File_is(zpath) ){
						compressed = 2;
					}
				}
 fprintf(fp,"<br><font color=red>The history file around %s is not found%s,\
  See the LOGFILE of DeleGate and search the line including a string \
  'time=%s'</font>\n",
  sfromtime,compressed?"(compressed)":"",etime);
			}
		sv1log("HTSTATS.h: ERROR: time=%s: Cannot open the PROTOLOG\
  file around [%s] %s\n",
  etime,sfromtime,path);
			return 0;
		}

		fsize = Fsizeo(hfp);
		fileId = strCRC32(path,strlen(path));

		fval = sgetv("lines");
		lines = limit(StE,"lines",fval);
		fval = sgetv("psize");
		sizeKB = limit(StE,"psize",fval);
		if( soff = sgetv("history_begin") ){
			sscanf(soff,"%llu",&fbegin);
		}
		if( soff = sgetv("history_end") ){
			sscanf(soff,"%llu",&fend);
		}

		if( act && strcaseeq(act,"Refresh") || act == 0 || *act == 0 ){
			/* default action */
			if( 0 < fbegin ){
				/* refresh the current page */
				Fseeko(hfp,fbegin,0);
			}else
			if( streq(arg1,"last") ){
				cueingLastPage(StE,act,hfp,fsize,fileId,fbegin,fend,sizeKB,lines);
			}else{
				cueingByDate(hfp,fromtime);
			}
		}else
		if( act && strcaseeq(act,"TOP") ){
			if( fbegin == 0 ){
		strcpy(StE->se_emessage,"You are already at the top of the history.");
			}
		}else
		if( act && strcaseeq(act,"NEXT") ){
			if( 0 < fend ){
				if( fend < 0 ){
				}else
				if( fend < fsize ){
					Fseeko(hfp,fend+1,0);
				}else{
		strcpy(StE->se_emessage,"You are already at the end of the history.");
					if( 0 < fbegin && fbegin < fsize ){
						Fseeko(hfp,fbegin,0);
					}else{
						Fseeko(hfp,0,2);
					}
				}
			}else{
			}
		}else
		if( act && strcaseeq(act,"PREV") ){
			noff = fbegin - sizeKB*1000;
			if( noff < 0 && fbegin == 0 ){
		strcpy(StE->se_emessage,"You are already at the top of the history.");
			}else{
				IStr(iline,URLSZ);
				if( noff < 0 ){
					noff = 0;
				}
				Fseeko(hfp,noff,0);
				if( 0 < Ftello(hfp) ){
					fgets(iline,sizeof(iline),hfp); /* odd line */
				}
				tailLines(hfp,lines,fbegin);
			}
		}else
		if( act == NULL || strcaseeq(act,"TAIL") || strcaseeq(arg1,"last") ){
			cueingLastPage(StE,act,hfp,fsize,fileId,fbegin,fend,sizeKB,lines);
		}else
		if( act && strcaseeq(act,"Cueing") ){
			cueingByDate(hfp,fromtime);
		}
		if( fp ){
			fprintf(fp,"<input type=hidden name=CueingTime value=%u>\n",
				fromtime);
			fprintf(fp,"<input type=hidden name=fileId value=%X>\n",fileId);
			leng = filter_history(Conn,hfp,fp,StE,
				myhost,sizeKB*1000,lines);
		}
		fclose(hfp);
		return 1;
	}else
	if( strcaseeq(name,"psize") ){
		if( fval ){
			if( fp ) fprintf(fp,"%d",limit(StE,"psize",fval));
			return 1;
		}else{
			return 0;
		}
	}else
	if( strcaseeq(name,"lines") ){
		if( fval ){
			if( fp ) fprintf(fp,"%d",limit(StE,"lines",fval));
			return 1;
		}else{
			return 0;
		}
	}else
	if( strcaseeq(name,"client") ){
		if( fp ){ fprintf(fp,"%s",Client_Host); }
		return 1;
	}else
	if( strcaseeq(name,"clientx") ){
		int xhost;
		xhost = strCRC32(Client_Host,strlen(Client_Host)) & 0xFFFF;
		if( fp ){ fprintf(fp,"%x",xhost); }
		return 1;
	}else
	if( strcaseeq(name,"now") ){
		IStr(stime,128);
		StrftimeLocal(AVStr(stime),sizeof(stime),arg1,time(0),0);
		if( fp ) fprintf(fp,"%s",stime);
		return 1;
	}else
	if( strcaseeq(name,"date") ){
		int ago = time(0) - dHMtoSec(fval);
		StrftimeLocal(AVStr(valb),sizeof(valb),"%y-%m-%d",ago,0);
		if( fp ) fprintf(fp,"%s",valb);
		return 1;
	}else
	if( strcaseeq(name,"time") ){
		int ago = time(0) - dHMtoSec(fval);
		StrftimeLocal(AVStr(valb),sizeof(valb),"%H-%M-%S",ago,0);
		if( fp ) fprintf(fp,"%s",valb);
		return 1;
	}else
	if( strcaseeq(name,"ago") ){
	}else
	if( strcaseeq(name,"dorefresh") ){
		if( fval && *fval ) return 1;
		return 0;
	}else
	if( strcaseeq(name,"refresh") ){
		if( fp && fval != NULL ){
			fprintf(fp,"%d",limit(StE,"refresh",fval));
		}
		if( fval && *fval ) return 1;
		return 0;
	}else
	{
		return 0;
	}
	return 0;
}

/*
 * filter for malusing form value/URL
 * (should utilize urlescape.c)
 */
int escapeEntities(int argc,const char *argv[],PVStr(buff)){
	refQStr(bp,buff);
	const char *bp0;
	const char *arg1;
	const char *ap;
	int ac;

	for( ac = 0; ac < argc && argv[ac] != NULL; ac++ ){
		arg1 = argv[ac];
		Verbose("--formv[%d][%s]\n",ac,arg1);
		if( strpbrk(arg1,"%<>") ){
			argv[ac] = bp;
			for( ap = arg1; *ap; ap++ ){
				if( strchr("%<>",*ap) ){
					continue;
				}
				setVStrPtrInc(bp,*ap);
			}
			setVStrPtrInc(bp,0);
		}
	}
	return 0;
}

/*
 * the generator of /-/stats/ page.
 */
static const char *CookieName = "Query";
int stats_page(Connection *Conn,PCStr(req),FILE *fc,FILE *tc,int vno,PCStr(path),int *stcodep){
	int leng = 0;
	int cleng;
	IStr(upath,URLSZ);
	refQStr(qp,upath);
	refQStr(pp,upath);
	IStr(ubuff,URLSZ);
	FILE *tmp;
	const char *ctype;
	IStr(query,URLSZ);
	StatsEnv StEbuf;
	StatsEnv *StE = &StEbuf;
	int mtime = -1;
	int expire = 0;
	const char *fval;
	IStr(Cookie,URLSZ);

	if( strneq(path,"-/data:",7) ){
		/* stats local "data:" interpreter new-140521b */
		leng = HTTP_putData(Conn,tc,vno,path+7);
		return leng;
	}
	if( *path == 0 ){
		path = "welcome.dhtml";
	}
	sprintf(upath,"stats/%s",path);

	if( qp = strchr(upath,'?') ){
		setVStrEnd(qp,0);
		qp++;
	}
	tmp = TMPFILE("HistoryPage");
	bzero(&StEbuf,sizeof(StatsEnv));
	StE->se_argc = 0;
	setQStr(StE->se_argp,StE->se_argbuf,sizeof(StE->se_argbuf));

	if( strneq(req,"POST ",5) ){
		StE->se_argc = HTTP_form2v(Conn,fc,elnumof(StE->se_argv),StE->se_argv);
		StE->se_argv[StE->se_argc] = 0;
		escapeEntities(StE->se_argc,StE->se_argv,AVStr(ubuff));

		if( StE->se_argc == 0 || getv(StE->se_argv,"act")==NULL ){
			/* not initialized ? */
			IStr(args,URLSZ);
			formv2str(StE->se_argv,AVStr(args));
		sv1log("HTSTATS.h: (meaning unknown now) fallback to the default(%s), ignoring(%s)\n",defaultArgs,args);
			strcpy(query,defaultArgs);
			StE->se_argc = form2v(AVStr(query),elnumof(StE->se_argv),StE->se_argv);
			StE->se_argv[StE->se_argc] = 0;
		}
	}else
	/* set formv from qp */
	if( qp && *qp != 0 ){
		strcpy(query,qp);
		StE->se_argc = form2v(AVStr(query),elnumof(StE->se_argv),StE->se_argv);
		StE->se_argv[StE->se_argc] = 0;
		escapeEntities(StE->se_argc,StE->se_argv,AVStr(ubuff));
	}

	if( StE->se_argc == 0 ){
		HTTP_getRequestField(Conn,"Cookie",AVStr(Cookie),sizeof(Cookie));
		sv1log("HTSTATS.h: got Cookie: %s\n",Cookie);
		if( *Cookie ){
			getParamX(AVStr(Cookie),CookieName,AVStr(query),
				sizeof(query),0,1);
			StE->se_argc = form2v(AVStr(query),
				elnumof(StE->se_argv),StE->se_argv);
			StE->se_argv[StE->se_argc] = 0;
		}
	}

	if( StE->se_argc == 0 && !streq(upath,"stats/welcome.dhtml") ){
		strcpy(query,defaultArgs);
		StE->se_argc = form2v(AVStr(query),elnumof(StE->se_argv),StE->se_argv);
		StE->se_argv[StE->se_argc] = 0;
	}

	expire = time(0);
	leng = putBuiltinHTML(Conn,tmp,"StatsPage",upath,NULL,
		(iFUNCP)DHTML_printStats,StE);

	if( leng <= 0 ){
		fclose(tmp);
		return 0;
	}
	fflush(tmp); cleng = Ftello(tmp); Fseeko(tmp,0,0);
	ctype = filename2ctype(upath);
	if( ctype == NULL ){
		ctype = "text/plain";
	}

	/*
	mtime = mtimeOfBuiltinData(upath);
	 */
	if( (fval = getv(StE->se_argv,"remember")) && *fval  ){
		IStr(params,URLSZ);
		formv2str(StE->se_argv,AVStr(params));
		sprintf(addRespHeaders,"Set-Cookie: %s=%s\r\n",CookieName,params);
		sv1log("HTSTATS.h: add Heaer: %s",addRespHeaders);
	}else{
		if( *Cookie ){
			/* discard client's memory, by expire */
		}
	}
	putHttpHeader1X(Conn,tc,vno,NULL,ctype,ME_7bit,cleng,mtime,expire,NULL);
	if( RespWithBody ) copyfile1(tmp,tc);
	fclose(tmp);

	return leng;
}
