/*
 * RFC text to HTML converter
 * (c) Yutaka Sato,  June 2014
 *
 * v0.1 new-140618c created
 * v0.1 new-140619h using Abstract part as meta-description
 * v0.1 new-140619b prev/next link for existent RFC
 * v0.1 new-140620c hyper linking "RFC XXXX" to the RFC
 *
 */
const char *RHVER = "v0.1 (June 19, 2014)";

#include <stdio.h>
#include <string.h>

#define dbgout stderr

/*
 * maybe should larger for another search engines refering META tag.
 */
#define LINSZ    256 /* enough for RFC text, 80 bytes per line */
#define DSCSZ   1024 /* enough, at most 256 bytes used in any2fdif/FreyaSX */
#define MAXAUTH    2 /* restriction not to too consume FreyaSX digest */

/*
 * status transition in RFC text
 */
#define PRE_S	   1 /* in preamble space */
#define HEAD	   2 /* in header part */
#define HEAD_S	   3 /* in empty lines after header */
#define TITLE	   4 /* in something seems title */
#define TITLE_S	   5 /* in empty lines after title */
#define DESC	   6 /* in something seems description */
#define DESC_S	   7 /* in empty lines after description */
#define BODY	   8 /* in body part */
#define BODY_S	   9 /* in empty line in body */

static const char *swhere[] = {
	"",
	"PRE_S",
	"HEAD",
	"HEAD_S",
	"TITLE",
	"TITLE_S",
	"DESC",
	"DESC_S",
	"BODY",
};

/*
 * status of extraction of inAbst(act) / inIntro(duction)
 */
#define SEC_NONE   0 /* no Abstract encountered yet */
#define SEC_PRE_S  1 /* waiting empty line before the body */
#define SEC_BODY   2 /* the body of Abstract */
#define SEC_DONE   3 /* Abstract is got already */

static char *fgetsLine(char *line,int size,FILE *ifp){
	char *rp;
	char *ep;
	if( rp = fgets(line,size,ifp) ){
		if( ep = strpbrk(line,"\r\n") )
			*ep = 0;
		return rp;
	}else{
		return NULL;
	}
}

static void escHtmlChar(const char *iline,char *eline){
	const char *ilp;
	char *elp = eline;
	for( ilp = iline; *ilp; ilp++ ){
		if( *ilp == '\f' ){
		}else
		if( *ilp == '<' ){ strcpy(elp,"&lt;");   elp += strlen(elp);
		}else
		if( *ilp == '>' ){ strcpy(elp,"&gt;");   elp += strlen(elp);
		}else
		if( *ilp == '&' ){ strcpy(elp,"&amp;");  elp += strlen(elp);
		}else
		if( *ilp == '"' ){ strcpy(elp,"&quot;"); elp += strlen(elp);
		}else{
			*elp++ = *ilp;
		}
	}
	*elp = 0;
}

/*
 * erase leading and trailing spaces and inline '\f'
 */
static char *stripSpaces(const char *in,char *out){
	const char *ip;
	char *op = out;
	char *lastnonsp = 0;
	for( ip = in; *ip; ip++ )
		if( *ip != ' ' && *ip != '\t' )
			break;
	for(; *ip; ip++ ){
		if( *ip == '\f'
		){
			continue;
		}
		if( *ip != ' ' ){
			lastnonsp = op;
		}
		*op++ = *ip;
	}
	*op = 0;
	if( lastnonsp && lastnonsp[1] != 0 ){
		/* truncate trailing spaces */
		lastnonsp[1] = 0;
	}
	return out;
}
static numSpaces(const char *str){
	int nsp = 0;
	const char *sp;

	for( sp = str; *sp; sp++ ){
		if( *sp == ' ' ){
			nsp += 1;
		}else
		if( *sp == '\t' ){
			nsp += 4;
		}else{
			break;
		}
	}
	return nsp;
}
static dashOnly(const char *str){
	const char *sp;
	for( sp = str; *sp; sp++ ){
		if( *sp != '-' )
			return 0;
	}
	return 1;
}

/*
 * get left and right part in a RFC header line
 *
 * each header line could be as follows:
 * "Left"
 * "Left              Right"
 * "    Left          Right"
 * "                  Right"
 */
static int getLeftRight(const char *line,char *left,char *right){
	const char *lip;
	int lch;
	char *lep;
	char *rip;

	*left = *right = 0;
	for( lip = line; (lch = *lip) && (lip - line) <= 8; lip++ ){
		if( lch != ' ' && lch != '\t' )
			break;	
	}
	if( *lip != ' ' ){
		lep = left; 
		for( ; (lch = *lip); lip++ ){
			if( 5 <= numSpaces(lip) )
				break;
			if( lch == '\t' ){
				*lep++ = ' ';
			}else{
				*lep++ = lch;
			}
		}
		*lep = 0;
	}
	while( *lip == ' ' || *lip == '\t' )
		lip++;

	rip = right; 
	for( ; (lch = *lip); lip++ ){
		if( lch == '\t' ){
			*rip++ = ' ';
		}else{
			*rip++ = lch;
		}
	}
	*rip = 0;

	if( left[0] == 0 && right[0] != 0 && (lip-line) < 70 ){
		/* seems at center */
		strcpy(left,right);
		right[0] = 0;
	}
	if( *left || *right ){
/*
 fprintf(dbgout,"-- Left{%s}  Right{%s}\n",left,right);
*/
	}
	return 1;
}
static int getTriple(const char *line,char *left,char *center,char *right){
	char righter[LINSZ];

	getLeftRight(line,left,righter);
	getLeftRight(righter,center,right);
	if( *righter && *center && *right ){
/*
 fprintf(stderr,"-- Triple {%s} {%s} {%s}\n",left,center,right);
*/
		return 1;
	}
	return 0;
}

static char *monthName[] = {
	0,
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December",
	0
};
static int normMonth(char *month){
	int mi;
	char *m1;
	for( mi = 1; m1 = monthName[mi]; mi++ ){
		if( strncasecmp(m1,month,3) == 0 ){
			strcpy(month,m1);
			return mi;
		}
	}
	return 0;
}
static int scanDate(const char *date,int *day,char *month,int *year){
	int match = 0;
	int imonth;
	int day2;

	*year = 1970;
	strcpy(month,"January");
	*day = 1;

	if( sscanf(date,"%d/%d/%d",&imonth,day,year) == 3 ){
		if( 1 <= imonth && imonth <= 12 ){ 
			sprintf(month,"%s",monthName[imonth]);
			match = 101;
		}else
		if( 1 <= *day && *day <= 12 ){
			sprintf(month,"%s",monthName[*day]);
			*day = imonth;
			match = 102;
		}
	}else
	if( sscanf(date,"%*[A-Z] %d %[A-Za-z.] %d",day,month,year) == 3
         && normMonth(month) ){
		match = 103;
	}else
	if( sscanf(date,"%d %[A-Za-z.] %d",day,month,year) == 3
         && normMonth(month) ){
		match = 104;
	}else
	if( sscanf(date,"%d %[A-Za-z.], %d",day,month,year) == 3
         && normMonth(month) ){
		match = 105;
	}else
	if( sscanf(date,"%d %[A-Za-z.] '%d",day,month,year) == 3
         && normMonth(month) ){
		match = 106;
	}else
	if( sscanf(date,"%d, %d %[A-Za-z.] %d",day,&day2,month,year) == 4
         && normMonth(month) ){
		match = 107;
	}else
	if( sscanf(date,"%*[A-Z] %d-%[A-Za-z]-%d",day,month,year) == 3
         && normMonth(month) ){
		match = 108;
	}else
	if( sscanf(date,"%d-%[A-Za-z]-%d",day,month,year) == 3 ){
		match = 109;
	}else
	if( sscanf(date,"%d-%d %[A-Za-z.] %d",day,&day2,month,year) == 4 ){
		match = 110;
	}else
	if( sscanf(date,"%d-%[A-Za-z]-%d",day,month,year) == 3 ){
		match = 111;
	}else
	if( sscanf(date,"%*[A-Za-z] %[A-Za-z.] %d %*d:%*d:%*d %d",month,day,year) == 3 ){
		match = 201;
	}else
	if( sscanf(date,"%[A-Za-z.] %d &amp; %*d, %d",month,day,year) == 3 ){
		match = 202;
	}else
	if( sscanf(date,"(%[A-Za-z.] %d, %d)",month,day,year) == 3 ){
		match = 203;
	}else
	if( sscanf(date,"%[A-Za-z.] %d, %d",month,day,year) == 3 ){
		match = 204;
	}else
	if( sscanf(date,"%[A-Za-z.] %d, l%d",month,day,year) == 3 ){
		*year += 1000; /* typo 'l' for '1' ;-) */
		match = 204;
	}else
	if( sscanf(date,"%[A-Za-z.], %d",month,year) == 2 && normMonth(month) ){
		*day = 1;
		match = 301;
	}else
	if( sscanf(date,"%[A-Za-z.] %d",month,year) == 2 && normMonth(month) ){
		*day = 1;
		match = 302;
	}else
	if( sscanf(date,"%[A-Za-z.] l%d",month,year) == 2 && normMonth(month) ){
		*year += 1000; /* typo 'l' for '1' ;-) */
		*day = 1;
		match = 303;
	}

	if( 0 <= *year && *year < 100 ){
		if( 60 <= *year )
			*year += 1900;
		else	*year += 2000;
	}
	if( match ){
		normMonth(month);
	}
	return match;
}
static int getNormDate(int where,const char *sdate,char *date){
	char month[LINSZ];
	int day;
	int year;
	int match;

	if( match = scanDate(sdate,&day,month,&year) ){
fprintf(stderr,"## %s: found Date %d {%s} %s %d, %d\n",
	swhere[where],match,sdate,month,day,year);
		sprintf(date,"%s %d, %d",month,day,year);
		return 1;
	}
	return 0;
}
static const char *date2mdY(char *sdate,char *mdY){
	char month[LINSZ];
	int day;
	int year;
	int match;
	int mi;

	if( match = scanDate(sdate,&day,month,&year) ){
		mi = normMonth(month);
		sprintf(mdY,"%02d/%02d/%d",mi,day,year);
	}else{
		strcpy(mdY,"01/01/1970");
	}
	return mdY;
}
static int nextSection(char *iline){
	if( iline[0] != ' ' ){ /* next section */
		return 1;
	}
	return 0;
}
static int scanRFCNO(const char *src,char *rfcno,const char **next){
	const char *sp = src;
	char *rfp = rfcno;
	int rno;

	if( strncmp(sp,"RFCs ",5) == 0 ){
		sp += 5;
		strcpy(rfp,"RFCs ");
		rfp += strlen(rfp);
		if( sscanf(sp,"%d",&rno) ){
			if( 0 <= rno && rno < 20000 ){
				while( '0' <= *sp && *sp <= '9' ){
					*rfp++ = *sp++;
				} 
				*rfp = 0;
				*next = sp;
				return rno;
			}
		}
	}
	if( strncmp(sp,"RFC",3) == 0 ){
		sp += 3;
		strcpy(rfp,"RFC");
		rfp += 3;

		if( *sp == ' ' || *sp == '-' ){
			*rfp ++ = *sp++;
		}
		if( sscanf(sp,"%d",&rno) == 1 )
		if( 0 < rno && rno < 20000 ){
			while( '0' <= *sp && *sp <= '9' ){
				*rfp++ = *sp++;
			} 
			*rfp = 0;
			*next = sp;
			return rno;
		}
	}
	return 0;
}
static int hyperLinkRFC(char *eline){
	char buff[4*LINSZ] = {0};
	char *bp = buff;
	const char *ep;
	int pch = ' ';
	char rfcno[32] = {0};
	int nref = 0;
	int rno = 0;

	for( ep = eline; *ep; ){
		if( *ep == 'R' )
		if( pch == ' '
		 || pch == ','
		 || pch == '['
		 || pch == '('
		 || pch == '/'
		)
		if( rno = scanRFCNO(ep,rfcno,&ep) ){
		    nref++;
		    sprintf(bp,"<a href=rfc%04d.shtml>%s<a/>",rno,rfcno);
		    bp += strlen(bp);
		    pch = '0';
		    continue;
		}
		pch = *ep;
		*bp ++ = *ep++;
	}
	*bp = 0;
	strcpy(eline,buff);
	return nref;
}

static void rfc2html(const char *name,int prev,int next,const char *text,FILE *Tfp,FILE *Hfp){
	int lines = 0;             /* total input lines */
	int xlines = 0;            /* the number of non empty lines */
	char iline[LINSZ];         /* original input line */
	char piline[LINSZ];        /* previous input line */
	char eline[4*LINSZ];       /* "<" is encoded to "&lt;" */
	char xline[4*LINSZ];       /* stripped preamble space */
	char left[4*LINSZ];        /* left part of a header line */
	char right[4*LINSZ];       /* right part of a header line */
	char center[4*LINSZ];        /* center part of a body line */
	char author[DSCSZ] = {0};  /* author buffer */
	int nauthor = 0;           /* number of authors */
	char date[DSCSZ] = {0};    /* date buffer */
	char title[DSCSZ] = {0};   /* title buffer */
	char desc[DSCSZ] = {0};    /* text that seems description */
	char abst[DSCSZ] = {0};    /* explicit Abstract */
	char intro[DSCSZ] = {0};   /* explicit Introduction */
	int where = PRE_S;         /* RFC status starts with PRE_S status */
	int inAbst = SEC_NONE;     /* Abstract status */
	int inIntro = SEC_NONE;    /* Introudction status */

	for( lines = 0; fgetsLine(iline,sizeof(iline),Tfp); lines++ ){
		escHtmlChar(iline,eline);
		stripSpaces(eline,xline);

		if( xline[0] == 0 ){
			if( inAbst == SEC_PRE_S ) continue;
			if( inIntro == SEC_PRE_S ) continue;

			switch( where ){
				case PRE_S: continue;
				case HEAD:
					/*
					if( lines < 10 ){
						if( author[0] == 0 )
							continue;
					}
					*/
					where = HEAD_S; continue;
				case HEAD_S: continue;
				case TITLE: where = TITLE_S; continue;
				case TITLE_S: continue;
				case DESC:
					if( lines < 20 ){
						if( author[0] == 0 ){
							continue;
						}
					}
					where = DESC_S; continue;
				case DESC_S: continue;
				case BODY:
					break;
				default: fprintf(dbgout,"## WHAT-SP? where=%d\n",where);
			}
		}else{
			xlines++;

			if( dashOnly(xline) ){
				continue;
			}
			if( inAbst == SEC_PRE_S ){
				inAbst = SEC_BODY; /* first body line */
			}else
			if( inAbst == SEC_BODY ){
				if( nextSection(iline) ){
					inAbst = SEC_DONE;
				}
			}
			if( inIntro == SEC_PRE_S ){
				inIntro = SEC_BODY;
			}else
			if( inIntro == SEC_PRE_S ){
				if( nextSection(iline) ){
					inIntro = SEC_DONE;
				}
			}

			if( where == PRE_S
			 && 8 <= numSpaces(eline)
			 && numSpaces(eline) < 50  /* maybe RFC XXX */
			){
fprintf(stderr,"--(%s)-- jump from %s to TITLE :0: %s\n",name,swhere[where],eline);
				where = TITLE;
			}else
			if( xlines < 20
			 && numSpaces(iline) < 8 /* not in centered title */
			 && strncmp(xline,"Network Working Group",21) == 0
			 && (where == HEAD_S || where == TITLE)
			){
fprintf(stderr,"--(%s)-- reset from %s to HEAD :1: author[%s] title[%s]\n",name,swhere[where],author,title);
				author[0] = 0;
				title[0] = 0;
				where = HEAD;
			}else
			switch( where ){
				case PRE_S: where = HEAD; break;
				case HEAD: break;
				case HEAD_S: where = TITLE; break;
				case TITLE:
					if( nextSection(iline) ){
						where = BODY;
					}
					break;
				case TITLE_S: where = DESC; break;
				case DESC:
					if( nextSection(iline) ){
						where = BODY;
					}
					break;
				case DESC_S: where = BODY; break;
				case BODY:
					break;
				default: fprintf(dbgout,"## WHAT-NONSP? where=%d [%s]\n",where,xline);
			}
		}

		switch( where ){
		    case TITLE:
		    case DESC:
		    {
			getLeftRight(eline,left,right);
			if( right[0] ){
				if( getNormDate(where,right,date) ){
					if( title[0] == 0 ){
fprintf(stderr,"--(%s)-- reset from %s to HEAD :2: %s\n",name,swhere[where],xline);
						where = HEAD;
					}
					continue;
				}
			}

			if( strncasecmp(xline,"Status of This Memo",19) == 0
			){
				where = BODY;
			}

			if( date[0] == 0 && author[0] == 0 )
			if( strncasecmp(xline,"RFC ",4) == 0
			){
fprintf(stderr,"--(%s)-- reset from %s to HEAD :3: %s\n",name,swhere[where],xline);
				title[0] = 0;
				where = HEAD;
				continue;
			}

			if( strncasecmp(xline,"Obsoletes:",10) == 0
			 || strncasecmp(xline,"Obsoletes ",10) == 0
			 || strncasecmp(xline,"Updates:",8) == 0
			 || strncasecmp(xline,"IEN:",4) == 0
			 || strncasecmp(xline,"RFC:",4) == 0
			){
fprintf(stderr,"--(%s)-- reset from %s to HEAD_S :4: %s\n",name,swhere[where],xline);
				title[0] = 0;
				where = HEAD_S;
				continue;
			}
			if( strncasecmp(xline,"NWG/RFC ",8) == 0
			){
fprintf(stderr,"--(%s)-- reset from %s to HEAD :5: %s\n",name,swhere[where],xline);
				title[0] = 0;
				where = HEAD;
			}
			break;
		    }
		}
		if( where == BODY ){
		}else{
			fprintf(dbgout,"-- %s: %s\n",swhere[where],xline);
		}

		if( where == DESC || where == BODY ){
			if( inAbst == SEC_NONE ){
				char secno[LINSZ];
				char title[LINSZ];

				*secno = *title =  0;
				sscanf(xline,"%s %[^\r\n]",secno,title);
				if( atoi(secno) <= 0 ){
					strcpy(title,xline);
				}

				if( strcasecmp(title,"Abstract") == 0
				 || strcasecmp(title,"Summary") == 0
				 || strcasecmp(title,"Overview") == 0
				){
					inAbst = SEC_PRE_S;
				}
			}
			if( inAbst == SEC_BODY )
			if( sizeof(abst) <= strlen(abst)+strlen(xline)+1 ){
	fprintf(stderr,"## %s: WARNING: abstract overflow\n",name);
				inAbst = SEC_DONE;
			}else{
				if( abst[0] != 0 )
					strcat(abst," ");
				strcat(abst,xline);
			}

			if( inIntro == SEC_NONE ){
				if( strcasecmp(xline,"Introduction") == 0 ){
					inIntro = SEC_PRE_S;
				}
			}
			if( inIntro == SEC_BODY )
			if( sizeof(intro) <= strlen(intro)+strlen(xline)+1 ){
	fprintf(stderr,"## %s: WARNING: introduction overflow\n",name);
				inIntro = SEC_DONE;
			}else{
				if( intro[0] != 0 )
					strcat(intro," ");
				strcat(intro,xline);
			}
		}

		switch( where ){
			case BODY:
				if( lines < 100 ){
					if( date[0] == 0 ){
						getNormDate(where,xline,date);
					}
				}
				continue;
			case HEAD: {
				char left[1024];
				char right[1024];
				getLeftRight(eline,left,right);
				if( left[0] ){
					if( getNormDate(where,left,date) ){
					}else{
					}
				}
				if( right[0] ){
					if( getNormDate(where,right,date) ){
					}else
					if( sizeof(author) < strlen(author)+strlen(right)+1 ){
	fprintf(stderr,"## %s: WARNING: author overflow\n",name);
						continue;
					}else{
						if( nauthor < MAXAUTH ){
							if( author[0] != 0 )
								strcat(author,", ");
							strcat(author,right);
						}else{
						}
						nauthor++;
					}
				}
				break;
			}
			case TITLE: {
				getLeftRight(eline,left,right);
				if( date[0] == 0 && getNormDate(where,right,date) ){
					continue;
				}
				if( date[0] == 0 && getNormDate(where,xline,date) ){
					continue;
				}else
				if( sizeof(title) < strlen(title)+strlen(xline)+1 ){
	fprintf(stderr,"## %s: WARNING: title overflow\n",name);
					continue;
				}
				if( title[0] != 0 )
					strcat(title," ");
				strcat(title,xline);
				break;
			case DESC:
				if( date[0] == 0 && getNormDate(where,xline,date) ){
					continue;
				}else
				if( sizeof(desc) < strlen(desc)+strlen(xline)+1 ){
	fprintf(stderr,"## %s: WARNING: description overflow\n",name);
					where = BODY;
					continue;
				}
				if( desc[0] != 0 )
					strcat(desc," ");
				strcat(desc,xline);
				break;
			}
			default:
				break;
		}
	}

	/*
	 * HTML header part
	 */
	{
	char ndate[LINSZ];
	int rno = 0;
	sscanf(name,"rfc%d",&rno);
	fseek(Tfp,0,0);
	fprintf(Hfp,"<html>\n");
	fprintf(Hfp,"<head>\n");
	fprintf(Hfp,"<!-- generated by rfc2html %s -->\n",RHVER);
	if( date[0] ){
		fprintf(Hfp,"<meta name=revised content=\"%s\" />\n",date);
	}else{
		fprintf(Hfp,"<!--X-Date: January 1, 1970 -->\n");
	}
	if( author[0] ){
		fprintf(Hfp,"<meta name=author content=\"%s\" />\n",author);
	}else{
		fprintf(stderr,"--(%s)-- not found Author\n",name);
	}
	fprintf(Hfp,"<title>RFC%d %s</title>\n",rno,title);
	if( abst[0] )
		fprintf(Hfp,"<meta name=description content=\"%s\" />\n",abst);
	else
	if( intro[0] )
		fprintf(Hfp,"<meta name=description content=\"%s\" />\n",intro);
	else	fprintf(Hfp,"<meta name=description content=\"%s\" />\n",desc);
	fprintf(Hfp,"</head>\n");

	/*
	 * heading of body part
	 */
	fprintf(Hfp,"<body>\n");
	fprintf(Hfp,"<div style=width:730px>\n");

	fprintf(Hfp,"<a name=page-%d>\n",0);
	fprintf(Hfp,"<div style=background-color:#f0f0ff>\n");
	fprintf(Hfp,"<form action=/fsx/search>\n");
	fprintf(Hfp,"<input type=hidden name=index value=rfc>\n");
	fprintf(Hfp,"<input type=hidden name=sort value=url>\n");
	fprintf(Hfp,"<a href=/ietf/>home</a>\n");
	fprintf(Hfp,"&nbsp;\n");
	if( prev < 0 )
		fprintf(Hfp,"prev\n",rno-1);
	else	fprintf(Hfp,"<a href=rfc%04d.html>prev</a>\n",prev);
	fprintf(Hfp,"&nbsp;\n");
	if( next < 0 )
		fprintf(Hfp,"next\n",rno+1);
	else	fprintf(Hfp,"<a href=rfc%04d.html>next</a>\n",next);
	fprintf(Hfp,"&nbsp;\n");

	/* this must be generalized, off course !! */
	fprintf(Hfp,"<a href=/fsx/search?index=rfc&sort=date&sxop=OR&key=%%22RFC+%d%%22+RFC%d>search</a> <input type=text name=key>\n",rno,rno);
	fprintf(Hfp,"&nbsp;\n");
	fprintf(Hfp,"<a href=%s>text</a>\n",text);
	fprintf(Hfp,"</form>\n");
	fprintf(Hfp,"</div>\n");
	fprintf(Hfp,"</a>\n");

	fprintf(Hfp,"<pre><font face=\"courier new\">");
	}

	/*
	 * HTML body part
	 */
	{
	int top = 1;
	int rno = 0;
	int pno;
	char secnum[LINSZ];
	char stitle[LINSZ];
	int toSmall = 0;
	int inSmall = 0;
	int nextsect = 0;

	where = BODY_S;
	while( fgetsLine(iline,sizeof(iline),Tfp) ){
		escHtmlChar(iline,eline);
		stripSpaces(eline,xline);
		if( top && xline[0] == 0 ){
			continue;
		}
		top = 0;
		nextsect = 0;
		toSmall = 0;

		if( getTriple(eline,left,center,right)
		 || getLeftRight(eline,left,right)
		){
		    if( sscanf(left,"RFC %d",&rno) == 1 && right[0] != 0 ){
			continue;
		    }
		    if( sscanf(right,"[Page %d]",&pno) == 1 ){
			fprintf(Hfp,"<div align=right style=background-color:#f8f8f8>");
			fprintf(Hfp,"<a href=#page-0>top</a>");
			fprintf(Hfp,"&nbsp;<a href=#page-%d>back</a>",pno-1);
			fprintf(Hfp,"&nbsp;<a href=#page-%d>forw</a>",pno+1);
			fprintf(Hfp,"<a name=page-%d>[Page %d]</a>",pno,pno);
			fprintf(Hfp,"</div>");
			fprintf(Hfp,"\r\n");
			continue;
		    }
		}
		if( xline[0] == 0 ){
			if( where == BODY ){
				where = BODY_S;
				fprintf(Hfp,"\r\n");
				continue;
			}
			if( where == BODY_S ){
				continue;
			}
		}else{
			/*
			if( nextSection(iline) ){
				fprintf(Hfp,"\r\n");
			}
			*/

			if( strcasecmp(xline,"Status of This Memo") == 0
			 || strcasecmp(xline,"Status of the Memo") == 0
			 || strcasecmp(xline,"Copyright Notice") == 0
			 || strcasecmp(xline,"Copyright") == 0
			 || strncasecmp(iline,"Copyright (c) ",14) == 0
			 || strcasecmp(xline,"Notice") == 0
			 || strcasecmp(xline,"Notices") == 0
			 || strcasecmp(xline,"Note") == 0
			 || strcasecmp(xline,"Note:") == 0
			 || strcasecmp(xline,"IANA Note:") == 0
			 || strcasecmp(xline,"IANA Note") == 0
			 || strcasecmp(xline,"IESG Note") == 0
			 || strcasecmp(xline,"IESG Note:") == 0
			 || strcasecmp(xline,"RFC Editor's Note") == 0
			 || strcasecmp(xline,"Author's Note:") == 0
			 || strcasecmp(xline,"Authors' Note") == 0
			 || strcasecmp(xline,"Contributors") == 0
			 || strcasecmp(xline,"Acknowlegements") == 0
			 || strcasecmp(xline,"Acknowledgements") == 0
			 || strcasecmp(xline,"Acknowledgments") == 0
			 || strcasecmp(xline,"Disclaimer") == 0
			 || strcasecmp(xline,"Disclaimer and Acknowledgments") == 0
			){
				nextsect = 1;
				toSmall = 1;
			}
			if( strncmp(iline,"1. ",3) == 0
			 || strncmp(iline,"1.0 ",4) == 0
			 || strncmp(iline,"1  ",3) == 0
			 || strncmp(iline,"1 - ",4) == 0
			){
				nextsect = 1;
			}
			if( strcasecmp(xline,"Abstract") == 0
			 || strcasecmp(xline,"Abstract:") == 0
			 || strcasecmp(xline,"Summary") == 0
			 || strcasecmp(xline,"Overview") == 0
			 || strcasecmp(xline,"Overview and Rational") == 0
			 || strcasecmp(xline,"Overview and Rationale") == 0
			 || strncasecmp(xline,"Overview of ",12) == 0
			 || strncasecmp(xline,"Specification of ",17) == 0
			 || strcasecmp(xline,"Usage and submission") == 0
			 || strcasecmp(xline,"Statement") == 0
			 || strcasecmp(xline,"Conventions") == 0
			 || strncasecmp(xline,"Conventions used",16) == 0
			 || strcasecmp(xline,"Description") == 0
			 || strcasecmp(xline,"Discussion") == 0
			 || strcasecmp(xline,"Discussion/Purpose") == 0
			 || strcasecmp(xline,"Recommendation") == 0
			 || strcasecmp(xline,"Scope") == 0
			 || strcasecmp(xline,"Purpose") == 0
			 || strcasecmp(xline,"Purpose:") == 0
			 || strcasecmp(xline,"Process:") == 0
			 || strcasecmp(xline,"Policy") == 0
			 || strcasecmp(xline,"Remembrance") == 0
			 || strcasecmp(xline,"History") == 0
			 || strcasecmp(xline,"Tribute") == 0
			 || strcasecmp(xline,"Background") == 0
			 || strncasecmp(xline,"Background and ",15) == 0
			 || strcasecmp(xline,"Motivation") == 0
			 || strcasecmp(xline,"Observations") == 0
			 || strcasecmp(xline,"Applicability") == 0
			 || strcasecmp(xline,"Introduction") == 0
			 || strcasecmp(xline,"PREFACE") == 0
			 || strcasecmp(xline,"Preamble") == 0
			 || strcasecmp(xline,"Table") == 0
			 || strcasecmp(xline,"TABLE OF CONTENTS") == 0
			){
				nextsect = 1;
			}
			if (sscanf(xline,"%s %[^\r\n]",secnum,stitle) == 2 )
			if( strcasecmp(stitle,"ABSTRACT") == 0
			 || strcasecmp(stitle,"Summary") == 0
			 || strncasecmp(stitle,"Overview of ",12) == 0
			 || strcasecmp(stitle,"Executive Summary") == 0
			 || strcasecmp(stitle,"Overview") == 0
			 || strcasecmp(stitle,"History") == 0
			 || strcasecmp(stitle,"Background") == 0
			 || strcasecmp(stitle,"Conventions") == 0
			 || strcasecmp(stitle,"Terminology") == 0
			 || strcasecmp(stitle,"Description") == 0
			 || strcasecmp(stitle,"INTRODUCTION") == 0
			 || strcasecmp(stitle,"Introduction.") == 0
			 || strcasecmp(stitle,"Table of Contents") == 0
			){
				nextsect = 1;
			}else
			if( strcasecmp(stitle,"Status of This Memo") == 0 
			 || strcasecmp(stitle,"Status of This Memo.") == 0 
			 || strcasecmp(stitle,"Acknowlegements") == 0 
			 || strcasecmp(stitle,"Acknowledgements") == 0 
			 || strcasecmp(stitle,"Acknowledgments") == 0 
			 || strcasecmp(stitle,"Notice") == 0 
			 || strcasecmp(stitle,"Copyright Notice") == 0
			){
				nextsect = 1;
				toSmall = 1;
			}

			if( where == BODY_S ){
				where == BODY;
			}
			if( hyperLinkRFC(eline) ){
/*
fprintf(stderr,"## hyperLinked: %s\n",eline);
*/
			}
		}
		if( inSmall ){
			if( iline[0] != ' ' || nextsect ){
				fprintf(Hfp,"</i></font></small>");
				inSmall = 0;
			}
		}
		if( nextsect ){
			fprintf(Hfp,"\r\n");
			nextsect = 0;
		}
		fprintf(Hfp,"%s\n",eline);
		if( toSmall ){
			fprintf(Hfp,"<small><font face\"Times New Roman\"><i>");
			inSmall = 1;
		}
	}

	fprintf(Hfp,"</font></pre>\n");
	if( 0 < pno ){
		fprintf(Hfp,"<a name=page-%d></a>\n",pno+1);
	}
	fprintf(Hfp,"</div>\n");
	fprintf(Hfp,"</body>\n");
	fprintf(Hfp,"</html>\n");
	}
}
static int navorRFC(const char *base,int inc){
	int rno;
	int ri;
	char navor[LINSZ];
	char *rp;
	FILE *fp = 0;

	strcpy(navor,base);
	rno = 0;
	if( rp = strrchr(navor,'/') ){
		rp += 1;
		sscanf(rp,"rfc%d",&rno);
	}else{
		rp = navor;
		sscanf(navor,"rfc%d",&rno);
	}
	rno += inc;
	for( ri = 0; ri < 100; ri++ ){
		if( rno <= 0 )
			break;
		sprintf(rp,"rfc%d",rno);
		if( fp = fopen(navor,"r") )
			break;
		sprintf(rp,"rfc%d.txt",rno);
		if( fp = fopen(navor,"r") )
			break;
		rno += inc;
	}
	if( fp ){
		fclose(fp);
		fprintf(stderr,"-- found navor by(%d) (%d) [%s]->[%s]\n",inc,ri+1,base,navor);
		return rno;
	}else{
		fprintf(stderr,"-- not found navor by(%d) (%d) [%s]\n",inc,ri+1,base);
		return -1;
	}
}
int main(int ac,char *av[]){
	int ai;
	char *a1;
	char ext[LINSZ];
	int rno;
	int prev;
	int next;
	char html[LINSZ];
	char text[LINSZ];
	char path[LINSZ];
	char *rfc;
	char rfcb[LINSZ];
	FILE *tp;
	FILE *hp;

	for( ai = 1; ai < ac; ai++ ){
		a1 = av[ai];
		if( rfc = strrchr(a1,'/') )
			rfc++;
		else	rfc = a1;
		if( strncasecmp(rfc,"rfc",3) != 0 ){
			continue;
		}
		ext[0] = 0;
		rno = 0;
		sscanf(rfc,"rfc%d.%s",&rno,ext);
		if( rno <= 0 || ext[0] != 0 && strcmp(ext,"txt") != 0 ){
			fprintf(stderr,"%s skipped\n",a1);
			continue;
		}
		sprintf(rfcb,"rfc%04d",rno);
		rfc = rfcb;
/*
		if( strcmp(ext,"txt") == 0 ){
			char *pp;
			strcpy(path,a1);
			if( pp = strrchr(path,'.') ){
				*pp = 0;
				if( tp = fopen(path,"r") ){
					fclose(tp);
					fprintf(stderr,"-- skip %s\n",a1);
					continue;
				}
			}
		}
*/
		if( ext[0] == 0 ){
			sprintf(path,"%s.txt",a1);
			if( tp = fopen(path,"r") ){
				fclose(tp);
				fprintf(stderr,"-- skip %s\n",a1);
				continue;
			}
		}

		tp = fopen(a1,"r");
		if( tp != NULL ){
			prev = navorRFC(a1,-1);
			next = navorRFC(a1, 1);

			sprintf(text,"../%s",a1);
			sprintf(html,"rfc-html/%s.shtml",rfc);
			hp = fopen(html,"w");
			if( hp == NULL ){
				fprintf(stderr,"## cannot create: %s\n",html);
				return -1;
			}else{
				fprintf(stderr,"++ %s -> %s\n",a1,html);
				rfc2html(rfc,prev,next,text,tp,hp);
				fclose(hp);
			}
			fclose(tp);
		}
	}
	return 0;
}
