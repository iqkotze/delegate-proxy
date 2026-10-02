/*////////////////////////////////////////////////////////////////////////
Copyright (c) 2005-2006 National Institute of Advanced Industrial Science and Technology (AIST)

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
Program:	gzip.c
Author:		Yutaka Sato <ysato@delegate.org>
Description:

History:
	050501	created
//////////////////////////////////////////////////////////////////////#*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "ystring.h"
#include "log.h"
#include "proc.h"
#include "fpoll.h"
#include "ysignal.h"
#include <zlib.h>

#define GZDBG lZLIB()==0?0:fprintf

int setCloseOnFork(PCStr(wh),int fd);
int clearCloseOnFork(PCStr(wh),int fd);


static int DGzlibVer;
int withDGZlib(){
	return DGzlibVer;
}

int getthreadid();
int strCRC32(PCStr(str),int len);
int strCRC32add(int crc,PCStr(str),int len);
extern int inGzip;
extern const char *FL_F_Gzip;
extern int FL_L_Gzip;

int gzipInit0(){
	return 0;
}
/*
#define GZdopen(fd,mode) gzdopen(fd,mode)
*/
gzFile GZdopen(int fd,const char *mode){
	gzFile gz;
	inGzip++; FL_F_Gzip = "Gzdopen"; FL_L_Gzip = __LINE__;
	gz = gzdopen(fd,mode);
	inGzip--;
	return gz;
}
/* gztell()/malloc() should be sigblocked ... */
long GZtell(gzFile file){
	long off;
	inGzip++; FL_F_Gzip = "Gztell"; FL_L_Gzip = __LINE__;
	off = gztell(file);
	inGzip--;
	return off;
}
int GZclose(gzFile file){
	int rcode;
	inGzip++; FL_F_Gzip = "Gzclose"; FL_L_Gzip = __LINE__;
	rcode = gzclose(file);
	inGzip--;
	return rcode;
}

int SocketOf(int fd);
int ShutdownSocket(int fd);
int Gzip_NoFlush;
int fdebug(FILE *fp,const char *mode);

static int zlib_dl;
static int zlib_pid;
int withZlib(){
	return 0 < zlib_dl;
}
static int _dg_zlib;
int withDG_Zlib(){
	return 0 < _dg_zlib;
}
int gzipInit(){
	int code;

	if( 0 < zlib_dl ){
		if( isCYGWIN() ){
			if( zlib_pid != getpid() ){
				zlib_pid = 0;
				zlib_dl = 0;
			}
		}
	}
	if( zlib_dl != 0 ){
		if( 0 < zlib_dl )
			return 0;
		else	return -1;
	}
	code = gzipInit0();
	if( code == 0 ){
		InitLog("+++ linked Zlib %s\n",zlibVersion());
		zlib_pid = getpid();
		zlib_dl = 1;
	}else{
		zlib_dl = -1;
	}
	return code;
}
const char *ZlibVersion(){
	if( 0 < zlib_dl )
	{
		if( isCYGWIN() ){
			gzipInit();
		}
		return zlibVersion();
	}
	if( zlib_dl == 0 )
		return "Not Yet";
	return "Not Found";
}
void putZLIBver(FILE *fp){
	if( 0 < zlib_dl )
		fprintf(fp,"Loaded: Zlib %s\r\n",zlibVersion());
}

#include "file.h"

#ifdef MMAP
#include <sys/mman.h>

int gzipMmap(int do_comp,FILE *in,FILE *out){
	double Start = Time();
	int ifd,ofd;
	int iz,izm;
	unsigned long oz;
	Byte *ia,*iam;
	Byte *oa,*oam;
	int rcode;
	int ioff;
	int ooff;

	ifd = fileno(in);
	ofd = fileno(out);
	if( !file_isreg(ifd) || !file_isreg(ofd) ){
		syslog_ERROR("--- gzipMmap: not reg-file: %d %d\n",ifd,ofd);
		return -1;
	}

	ioff = lseek(ifd,0,1);
	ooff = lseek(ofd,0,1);
	izm = file_size(ifd);
	iz = izm - ioff;
	if( do_comp )
		oz = 1024+iz;
	else	oz = 1024+iz*20;

	iam = (Byte*)mmap(0,izm,PROT_READ,MAP_SHARED,ifd,0);
	if( iam == 0 ){
		syslog_ERROR("--- gzipMmap: can't open in mmap(%d)\n",ifd);
		return -1;
	}
	ia = iam + ioff;

	oa = (Byte*)mmap(0,oz,PROT_READ|PROT_WRITE,MAP_SHARED,ofd,ooff);
	if( oa == 0 ){
		syslog_ERROR("--- gzipMmap: can't open out mmap(%d)\n",ofd);
		munmap(iam,iz);
		return -1;
	}

	lseek(ofd,oz-1,1);
	write(ofd,"",1);
	if( do_comp ){
		/*
		Byte *op = oa;
		*op++ = 0x1F; *op++ = 0x8B; *op++ = 8;
		*op++ = 0; *op++ = 0; *op++ = 0; *op++ = 0;
		*op++ = 0; *op++ = 0; *op++ = 3;
		rcode = compress2(op,&oz,ia,iz,-1);
		if( rcode == 0 ){
			oz += (op - oa);
		}
		*/
		rcode = compress2(oa,&oz,ia,iz,-1);
	}else{
		rcode = uncompress(oa,&oz,ia,iz);
	}

	munmap(iam,izm);
	munmap(oa,oz);

	syslog_ERROR("(%.4f)g%szip/mmap(%d) %d -> %d\n",
		Time()-Start,do_comp?"":"un",rcode,iz,oz);

	if( rcode == 0 ){
		Ftruncate(out,ooff+oz,0);
		fseek(out,0,0);
		if( do_comp )
			return iz;
		else	return oz;
	}
	lseek(ifd,ioff,0);
	lseek(ofd,ooff,0);
	Ftruncate(out,0,1);
	return -1;
}
#endif

int setNonblockingIO(int,int);
int finputReady(FILE *fs,FILE *ts);
int ready_cc(FILE *fp);

static int xread(FILE *fp,PVStr(buf),int siz){
	int rcc;
	int ch;

	if( 0 < ready_cc(fp) ){
		for( rcc = 0; rcc < siz; rcc++ ){
			if( ready_cc(fp) <= 0 ){
				break;
			}
			ch = getc(fp);
			if( ch == EOF )
				break;
			setVStrElem(buf,rcc,ch);
		}
	}else{
		rcc = read(fileno(fp),(char*)buf,siz);
	}
	return rcc;
}

FileSize Lseek(int,FileSize,int);
int IsConnected(int sock,const char **reason);
int file_isSOCKET(int fd);
int gotSIGPIPE();
/*
int GZIPready = -1;
static void sendsync(int fd,int code){
	CStr(stat,1);
	if( fd < 0 ){
	}else{
		setVStrElem(stat,0,code);
		write(fd,stat,1);
		close(fd);
	}
}
*/
typedef int SyncXF(void *sp,int si,int code);
static void sendsyncX(SyncXF syncf,void *sp,int si,int code){
	if( syncf != 0 ){
		syslog_ERROR("--- gzipFX SYNC %X(%X,%d,%d)\n",xp2i(syncf),p2i(sp),si,code);
		(*syncf)(sp,si,code);
	}
}
#define sendsync(fd,code) sendsyncX(syncf,sp,si,code)
int gzipFilterX(FILE *in,FILE *out,SyncXF syncf,void *sp,int si);
int gzipFilter(FILE *in,FILE *out){
	int leng;
	leng = gzipFilterX(in,out,0,0,0);
	return leng;
}
int gzipFilterX(FILE *in,FILE *out,SyncXF syncf,void *sp,int si){
	gzFile gz;
	int len,rcc;
	CStr(buf,1024*8);
	int size;
	int gsize;
	int wcc;
	int bcc = 0;
	double Start = Time();
	double Prevf = 0;
	int ibz = sizeof(buf);
	int gi;
	int fd = -1;
	int ofd = fileno(out);
	int xfd;
	int zerr = 0;
	/*
	int rready = -1;
	*/

	errno = 0;
	fd = dup(fileno(out));
	if( fd < 0 ){
		syslog_ERROR("--gzipFilter[%d]<-[%d] errno=%d\n",fd,ofd,errno);
		return -1;
	}

	/*
	if( 0 <= GZIPready )
		rready = dup(GZIPready);
	*/
	len = 0;
	/*
	if( gz = GZdopen(dup(fileno(out)),"w") ){
	*/
	if( file_isSOCKET(ofd) || file_ISSOCK(ofd) )
	if( !IsConnected(ofd,NULL) || !IsAlive(ofd) ){

fprintf(stderr,"[%d.%X] gzip DISCONN\n",getpid(),getthreadid());
fprintf(stderr,"[%d.%X] gzip DISCONN fd[%d] con=%d isSOCK=%d,%d,%d\n",
getpid(),getthreadid(),ofd,IsConnected(ofd,NULL),
file_isSOCKET(ofd),file_ISSOCK(ofd),file_issock(ofd));

		sendsync(rready,1);
		close(fd);
		return -1;
	}
	gz = GZdopen(fd,"w");
	if( file_isSOCKET(ofd) || file_ISSOCK(ofd) )
	if( !IsConnected(ofd,NULL) || !IsAlive(ofd) ){

fprintf(stderr,"[%d.%X] gzip DISCONN gx=%d\n",getpid(),getthreadid(),p2i(gz));
fprintf(stderr,"[%d.%X] gzip DISCONN fd[%d] con=%d isSOCK=%d,%d,%d\n",
getpid(),getthreadid(),ofd,IsConnected(ofd,NULL),
file_isSOCKET(ofd),file_ISSOCK(ofd),file_issock(ofd));

		close(fd);
		sendsync(rready,2);
		close(fd);
		return -1;
	}

	if( gz ){
		LOGX_gzip++;
		if( Gzip_NoFlush ){
			GZDBG(stderr,"-- %X gzip flush disabled(%d)\n",
				TID,Gzip_NoFlush);
		}
		Prevf = Time();

		sendsync(rready,0);
		setCloseOnFork("GZIPstart",fd);
		/*
		while( rcc = fread(buf,1,sizeof(buf),in) ){
		*/
		for( gi = 0;; gi++ ){
			if( gotsigTERM("gzip gi=%d",gi) ){
				if( numthreads() && !ismainthread() ){
					thread_exit(0);
				}
				break;
			}
			if( !Gzip_NoFlush )
			if( bcc )
			if( 0 < len && finputReady(in,NULL) == 0 ){
				zerr =
				gzflush(gz,Z_SYNC_FLUSH);
if( zerr ){
porting_dbg("+++EPIPE[%d] gzflush() zerr=%d %d SIG*%d",fd,zerr,len,gotSIGPIPE());
}
				bcc = 0;
			}
			if( lSINGLEP() ) /* could be generic */
			{
				if( 0 < len )
				if( !Gzip_NoFlush
				 || 4 < gi && 5 < Time()-Prevf
				){
				GZDBG(stderr,"-- %X gzip flush %d(%f) %d/%d\n",
				TID,Gzip_NoFlush,Time()-Start,len,gi);
					Prevf = Time();
					zerr = gzflush(gz,Z_SYNC_FLUSH);
					bcc = 0;
					if( zerr ){
				GZDBG(stderr,"-- %X gzip gzflush()%d err=%d\n",
				TID,len,zerr);
						break;
					}
				}
			}
			/*
			rcc = fread(buf,1,sizeof(buf),in);
			*/
			rcc = xread(in,AVStr(buf),QVSSize(buf,ibz));

			if( rcc <= 0 ){
				break;
			}
			wcc =
			gzwrite(gz,buf,rcc);

//fprintf(stderr,"[%d] Gzwrite %d/%d / %d\n",getpid(),wcc,rcc,len);

if( wcc <= 0 ){
porting_dbg("+++EPIPE[%d] gzwrite() %d/%d %d SIG*%d",fd,wcc,rcc,len,gotSIGPIPE());
fprintf(stderr,"[%d] Gzwrite %d/%d / %d\n",getpid(),wcc,rcc,len);
break;
}

			if( wcc != rcc ){
				syslog_ERROR("gzwrite %d/%d\n",wcc,rcc);
			}
			if( 0 < wcc ){
				bcc += wcc;
			}
			if( sizeof(buf) <= len ){
				ibz = sizeof(buf);
			}
			if( !Gzip_NoFlush )
			if( bcc )
			if( sizeof(buf) <= bcc || len < 16*1024 ){
				zerr =
				gzflush(gz,Z_SYNC_FLUSH);
				bcc = 0;
			}
			if( zerr || gotSIGPIPE() ){
porting_dbg("+++EPIPE[%d] gzflush() zerr=%d %d SIG*%d",fd,zerr,len,gotSIGPIPE());
				break;
			}
			len += rcc;
		}
		if( len == 0 ){
			const char *em;
			int en;
			int ef;
			em = gzerror(gz,&en);
			ef = gzeof(gz);
			if( en == -1 /* see errno */ && errno == 0 ){
				/* no error */
			}else{
			daemonlog("F","FATAL: gzwrite(%d)=%d/%d eof=%d %d %s\n",
				fd,len,bcc,ef,en,em);
			porting_dbg("FATAL: gzwrite(%d)=%d/%d eof=%d %d %s",
				fd,len,bcc,ef,en,em);
			}
		}
		clearCloseOnFork("GZIPend",fd);
		gzflush(gz,Z_SYNC_FLUSH);
		xfd = dup(fd);
		gsize = GZtell(gz);
		GZclose(gz);
		if( lMULTIST() ){
			/* duplicated close of fd is harmful */
		} /* to clear osf-handle mapping */
		Lseek(xfd,0,2);
		size = Lseek(xfd,0,1);
		Lseek(xfd,0,0);
		close(xfd);
		syslog_DEBUG("(%f)gzipFilter %d -> %d / %d\n",Time()-Start,
			len,gsize,size);
		return len;
	}
	sendsync(rready,3);
	close(fd);
	return 0;
}
typedef int SyncF(void *sp,int si);
int gunzipFilterX(FILE *in,FILE *out,SyncF syncf,void *sp,int si);
int gunzipFilter(FILE *in,FILE *out){
	int leng;
	leng = gunzipFilterX(in,out,0,0,0);
	return leng;
}
int gunzipFilterX(FILE *in,FILE *out,SyncF syncf,void *sp,int si){
	gzFile gz;
	int rcc;
	int wcc;
	int werr;
	CStr(buf,1024*8);
	int size;
	double Start = Time();
	const char *em;
	int en;
	int ef;
	int ready;
	int rd;
	int eof = 0;
	int nonblock;
	int serrno = 0;

	int ibz = sizeof(buf);
	int gi;
	int fd = -1;

	errno = 0;
	fd = dup(fileno(in));

    {
	/*
	 * to make smooth streaming of data relayed on narrow network
	 * apply NBIO to gzopen() which will do fread() at the start.
	 * applying NBIO also to gzread() seems to break the gzip.
	 */
	/*
	setNonblockingIO(fileno(in),1);
	*/
	setNonblockingIO(fd,1);
	nonblock = 1;
	ready = fPollIn(in,10*1000);
	if( ready == 0 ){
fprintf(stderr,"----[%d] gunzipFilter: ready[%d]=%d\n",
getpid(),fileno(in),ready);
	}
	/*
	gz = GZdopen(fd = dup(fileno(in)),"r");
	*/
	gz = GZdopen(fd,"r");
	if( DGzlibVer == 0 )
	{
		/*
	setNonblockingIO(fileno(in),0);
		*/
		setNonblockingIO(fd,0);
		nonblock = 0;
	}
    }
	if( syncf != 0 ){
		syslog_ERROR("--- gunzipFX SYNC %X(%X,%d)\n",xp2i(syncf),p2i(sp),si);
		(*syncf)(sp,si);
	}

	ibz = 1024;
	//ibz = 256;

	size = 0;
	/*
	if( gz = GZdopen(dup(fileno(in)),"r") ){
	*/
	if( gz ){
		LOGX_gunzip++;
		setCloseOnFork("GUNZIPstart",fd);
		em = gzerror(gz,&en);
		/*
		while( 0 < (rcc = gzread(gz,buf,sizeof(buf))) ){
		*/
		for( gi = 0;; gi++ ){
			if( gotsigTERM("gunzip gi=%d em=%X",gi,p2i(em)) ){
				if( numthreads() ){
					if( em ){
						putfLog("thread-gunzip gi=%d _exit() em=(%s)",gi,em?em:"");
						_exit(0);
					}
					thread_exit(0);
				}
				break;
			}
			if( nonblock ){
				if( 0 < gi ){
					/*
					setNonblockingIO(fileno(in),0);
					*/
					setNonblockingIO(fd,0);
					nonblock = 0;
				}
			}
			/*
			if( 0 < size && inputReady(fileno(in),NULL) == 0 ){
			*/
			/*
			if( 0 < size && inputReady(fd,NULL) == 0 ){
			*/
			if( eof == 0 )
			if( 0 < size )
			if( ready = inputReady(fd,&rd) ){
				if( ready == 2 ){ /* both PS_IN and PS_PRI */
					eof = 1;
				}
			}else{
//fprintf(stderr,"[%d] -- gzread#%d %d / %d FLUSH\n",getpid(),gi,rcc,size);
				fflush(out);
			}
			ready = fPollIn(in,10*1000);
			errno = 0;
			rcc = gzread(gz,buf,QVSSize(buf,ibz));
			serrno = errno;
			if( rcc <= 0 ){
				break;
			}
//fprintf(stderr,"[%d] -- gzread %d / %d\n",getpid(),rcc,size);
			wcc =
			fwrite(buf,1,rcc,out);
			/* this fflush seems significant */
			werr =
			fflush(out);
			if( wcc < rcc || werr || ferror(out) || gotSIGPIPE() ){
porting_dbg("+++EPIPE[%d] gunzip fwrite() %d/%d err=%d/%d %d SIG*%d",fileno(out),wcc,rcc,werr,ferror(out),size,gotSIGPIPE());
				break;
			}

			size += rcc;
			if( size < sizeof(buf) ){
				fflush(out);
			}else{
				ibz = sizeof(buf);
			}
		}
		fflush(out);
		if( rcc < 0 || size == 0 ){
			em = gzerror(gz,&en);
			ef = gzeof(gz);
			if( en == -1 /* see errno */ && serrno == 0 ){
				/* no error */
			}else{
			daemonlog("F","FATAL: gzread(%d)=%d/%d eof=%d %d %s %d\n",
				fd,rcc,size,ef,en,em,serrno);
			porting_dbg("FATAL: gzread(%d)=%d/%d eof=%d %d %s",
				fd,rcc,size,ef,en,em);
			if( lTHREAD() )
			fprintf(stderr,"--[%d]gzread(%d)=%d/%d eof=%d %d %s\n",
				getpid(),fd,rcc,size,ef,en,em);
			}
		}
		clearCloseOnFork("GUNZIPend",fd);
		GZclose(gz);
		if( lMULTIST() ){
			/* duplicated close of fd is harmful */
		}
		fseek(out,0,0);
		syslog_DEBUG("(%f)gunzipFilter -> %d\n",Time()-Start,size);
		return size;
	}
	return 0;
}

/*
int inflateFilter(FILE *in,FILE *out){
	int rcc;
	CStr(ibuf,1024*8);
	int size;
	double Start = Time();
	const char *em;
	int en;
	int ibz = sizeof(buf);
	int gi;
	int fd = -1;

	ibz = 512;
	if( gz ){
		for( gi = 0;; gi++ ){
			if( 0 < size && inputReady(fileno(in),NULL) == 0 ){
				fflush(out);
			}
			rcc = fread(gz,buf,QVSSize(buf,ibz));
			if( rcc <= 0 ){
				break;
			}
			inflate();
			fwrite(buf,1,rcc,out);
			size += rcc;
			if( size < sizeof(buf) ){
				fflush(out);
			}else{
				ibz = sizeof(buf);
			}
		}
		if( rcc < 0 ){
			em = gzerror(gz,&en);
			daemonlog("F","FATAL: gzread()=%d %d %s\n",rcc,en,em);
		}
		fseek(out,0,0);
		syslog_DEBUG("(%f)gunzipFilter -> %d\n",Time()-Start,size);
		return size;
	}
	return 0;
}
*/


static void *zalloc(void *opq,unsigned int ne,unsigned int siz){
	Z1Ctx *Zc = (Z1Ctx*)opq;
	void *ptr;

	ptr = calloc(ne,siz);
	if( ptr == 0 ){
		fprintf(stderr,"----Za no more memory\r\n");
		syslog_ERROR("----Za no more memory\n");
		exit(-1);
	}
	Zc->z1_asize += ne*siz;
	Zc->z1_acnt++;
	if( Zc->z1_debug ){
		fprintf(stderr,"----Za %6d (%d,%d) = %X, OPQ=%X %d %d\r\n",
			ne*siz,ne,siz,p2i(ptr),p2i(opq),Zc->z1_acnt,Zc->z1_asize);
	}
	return ptr;
}
static void zfree(void *opq,void *ptr){
	Z1Ctx *Zc = (Z1Ctx*)opq;

	if( ptr == 0 ){
		return;
	}
	if( Zc->z1_debug ){
		fprintf(stderr,"----Zf %8X\r\n",p2i(ptr));
	}
	free(ptr);
	Zc->z1_fcnt++;
}
int XdeflateInit_(Z1Ctx *Zc,int level,const char *version,int siz){
	if( deflateInit_((z_streamp)Zc->z1_Z1,level,version,sizeof(z_stream)) == Z_OK ){
		Zc->z1_ssize = sizeof(z_stream);
		return Z_OK;
	}
	return Z_VERSION_ERROR;
}
int XinflateInit_(Z1Ctx *Zc,const char *version,int siz){
	if( inflateInit_((z_streamp)Zc->z1_Z1,version,sizeof(z_stream)) == Z_OK ){
		Zc->z1_ssize = sizeof(z_stream);
		return Z_OK;
	}
	return Z_VERSION_ERROR;
}
int Xdeflate(Z1Ctx *Zc,int flush){
	return deflate((z_streamp)Zc->z1_Z1,flush);
}
int Xinflate(Z1Ctx *Zc,int flush){
	return inflate((z_streamp)Zc->z1_Z1,flush);
}
int XdeflateEnd(Z1Ctx *Zc){
	return deflateEnd((z_streamp)Zc->z1_Z1);
}
int XinflateEnd(Z1Ctx *Zc){
	return inflateEnd((z_streamp)Zc->z1_Z1);
}

Z1Ctx *createZ1(Z1Ctx *Zc,int de){
	int siz = sizeof(z_stream);
	const char *ver;
	z_stream *Z1;
	int rcode;

	if( gzipInit() != 0 ){
		fprintf(stderr,"----createZ1 FATAL Zlib unavailable\n");
		return 0;
	}
	ver = zlibVersion();
	Z1 = (z_stream*)malloc(siz);
	bzero(Z1,siz);

	Z1->zalloc = (alloc_func)zalloc;
	Z1->zfree = (free_func)zfree;
	Z1->opaque = Zc;
	Zc->z1_Z1 = Z1;
	if( de ){
		rcode = XdeflateInit_(Zc,Z_BEST_SPEED,ver,siz);
	}else{
		rcode = XinflateInit_(Zc,ver,siz);
	}
	if( rcode != Z_OK ){
		fprintf(stderr,"----createZ1(de=%d)=%X rcode=%d\n",de,p2i(Z1),rcode);
	}
	return Zc;
}
Z1Ctx *deflateZ1new(Z1Ctx *Zc){
	return createZ1(Zc,1);
}
Z1Ctx *inflateZ1new(Z1Ctx *Zc){
	return createZ1(Zc,0);
}
int deflateZ1end(Z1Ctx *Zc){
	XdeflateEnd(Zc);
	free(Zc->z1_Z1);
	return 0;
}
int inflateZ1end(Z1Ctx *Zc){
	XinflateEnd(Zc);
	free(Zc->z1_Z1);
	return 0;
}
int deflateZ1(Z1Ctx *Zc,PCStr(in),int len,PVStr(out),int osz){
	z_stream *Z1 = (z_stream*)Zc->z1_Z1;
	int rcode;

	Z1->next_in = (Bytef*)in;
	Z1->avail_in = len;
	Z1->next_out = (Bytef*)out;
	Z1->avail_out = osz;
	rcode = Xdeflate(Zc,Z_SYNC_FLUSH);
	return (char*)Z1->next_out - (char*)out;
}
int inflateZ1(Z1Ctx *Zc,PCStr(in),int len,PVStr(out),int osz){
	z_stream *Z1 = (z_stream*)Zc->z1_Z1;
	int rcode;

	Z1->next_in = (Bytef*)in;
	Z1->avail_in = len;
	Z1->next_out = (Bytef*)out;
	Z1->avail_out = osz;
	rcode = Xinflate(Zc,Z_SYNC_FLUSH);
	return (char*)Z1->next_out - (char*)out;
}
int Zsize(int *asize){
	Z1Ctx eZcb,*eZc = &eZcb;
	Z1Ctx dZcb,*dZc = &dZcb;
	const char *sb = "012345678901234567890123456789";
	IStr(eb,1024);
	IStr(xb,1024);
	int slen,elen,xlen;

	if( gzipInit() < 0 ){
		*asize = 0;
		return 0;
	}
	bzero(eZc,sizeof(Z1Ctx));
	bzero(dZc,sizeof(Z1Ctx));
	deflateZ1new(eZc);
	inflateZ1new(dZc);
	slen = strlen(sb)+1;
	elen = deflateZ1(eZc,sb,slen,AVStr(eb),sizeof(eb));
	xlen = inflateZ1(dZc,eb,elen,AVStr(xb),sizeof(xb));
	inflateZ1end(dZc);
	deflateZ1end(eZc);
	*asize = eZc->z1_asize+dZc->z1_asize;
	return eZc->z1_ssize;
}

int zlib_main(int ac,const char *av[]){
	Z1Ctx eZcb,*eZc = &eZcb;
	Z1Ctx dZcb,*dZc = &dZcb;
	const char *sb = "012345678901234567890123456789";
	IStr(eb,1024);
	IStr(xb,1024);
	int slen,elen,xlen;
	int ssize,asize;

	gzipInit();
	ssize = Zsize(&asize);
	fprintf(stderr,"----Zlib: %s (%d %d)\n",zlibVersion(),ssize,asize);
	bzero(eZc,sizeof(Z1Ctx));
	bzero(dZc,sizeof(Z1Ctx));
	eZc->z1_debug = 1;
	dZc->z1_debug = 1;

	deflateZ1new(eZc);
	if( eZc->z1_ssize == 0 ){
		exit(-1);
	}
	slen = strlen(sb)+1;
	elen = deflateZ1(eZc,sb,slen,AVStr(eb),sizeof(eb));

	inflateZ1new(dZc);
	xlen = inflateZ1(dZc,eb,elen,AVStr(xb),sizeof(xb));
	fprintf(stderr,"----Z: %d => %d => %d [%s]\n",slen,elen,xlen,xb);

	deflateZ1end(eZc);
	inflateZ1end(dZc);
	fprintf(stderr,"----Zlib-deflate-mem: (%d %d %d %d)\n",
		eZc->z1_ssize,eZc->z1_asize,eZc->z1_acnt,eZc->z1_fcnt);
	fprintf(stderr,"----Zlib-inflate-mem: (%d %d %d %d)\n",
		dZc->z1_ssize,dZc->z1_asize,dZc->z1_acnt,dZc->z1_fcnt);
	fprintf(stderr,"----Zlib--mem: (%d %d %d %d)\n",
		dZc->z1_ssize,
		dZc->z1_asize+eZc->z1_asize,
		dZc->z1_acnt+eZc->z1_acnt,
		dZc->z1_fcnt+eZc->z1_fcnt
	);
	return 0;
}

int zlibUncompress(void *in,int isiz,void *out,int osiz){
	int stat;
	int dlen;

	dlen = osiz;
	stat = uncompress((Byte*)out,(uLong*)&dlen,(const Byte*)in,(uLong)isiz);
	if( stat == 0 )
		return dlen;
	else	return -1;
}
