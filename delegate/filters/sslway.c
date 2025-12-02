/*
the header is necessary to enable some macros
#include <openssl/ssl.h>
*/

/*////////////////////////////////////////////////////////////////////////
Copyright (c) 1998-2000 Yutaka Sato and ETL,AIST,MITI
Copyright (c) 2001-2007 National Institute of Advanced Industrial Science and Technology (AIST)
AIST-Product-ID: 2000-ETL-198715-01, H14PRO-049, H15PRO-165, H18PRO-443

Permission to use, copy, modify, and distribute this material for any
purpose and without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.
AIST MAKES NO REPRESENTATIONS ABOUT THE ACCURACY OR SUITABILITY OF THIS
MATERIAL FOR ANY PURPOSE.  IT IS PROVIDED "AS IS", WITHOUT ANY EXPRESS
OR IMPLIED WARRANTIES.
/////////////////////////////////////////////////////////////////////////
Content-Type:	program/C; charset=US-ASCII
Program:	sslway.c (SSL encoder/decoder with OpenSSL)
Author:		Yutaka Sato <ysato@etl.go.jp>
Description:

  Modernized version for OpenSSL 3.x (Debian Bookworm/Trixie)
  - TLS 1.2 and TLS 1.3 only
  - ECDSA key support (RSA key generation removed)
  - RC4 support removed
  - Dynamic loading of OpenSSL shared libraries

  Given environment:
    file descriptor 0 is a socket connected to a client
    file descriptor 1 is a socket connected to a server

  Commandline argument:
    -cert file -- certificate (possibly with private key) of this SSLway
                  to be shown to a peer
    -key file -- private key file (if not included in the -cert file)
    -pass arg -- the source of passphrase, pass:string or file:path

    -CAfile file -- the name of file contains a CA's certificate
    -CApath dir -- directory contains CA's certificate files each named with
                   `X509 -hash -noout < certificate.pem`

    -Vrfy -- peer's certificate must be shown and must be authorized
    -vrfy -- peer's certificate, if shown, must be authorized
    -Auth -- peer must show its certificate, but it can be unauthorized
    -auth -- just record the peer's certificate, if exists, into log

    -vd  -- detailed logging
    -vu  -- logging with trace (former default)
    -vt  -- terse logging (current default)
    -vs  -- disalbe any logging

    -ht  through pass if the request is in bare HTTP protocol (GET,HEAD,POST)

    Following options can be omitted when the sslway is called from DeleGate
    with FCL, FSV or FMD since it will be detected automatically.

    -co  apply SSL for the connection to the server [default for FSV]
    -ac  aplly SSL for the accepted connection from the client [default for FCL]
    -ad  accept either SSL or through by auto-detection of SSL-ClientHello
    -ss  negotiate by AUTH SSL for FTP (implicit SSL for data-connection)
    -st  accept STARTTLS (protocol is auto-detect) and SSL tunneling
    -St  require STARTTLS first (protocol is auto-detect) and PBSZ+PROT for FTP
    -{ss|st|St}/protocol enable STARTTLS for the protocol {SMTP,POP,IMAP,FTP}
    -bugs

    -tls12 just talk TLSv1.2
    -tls13 just talk TLSv1.3

  Usage:
    delegated FSV=sslway
    delegated FCL=sslway ...

History:
	980412	created
	980428	renamed from "sslrelay" to "sslway"
	2024xx	modernized for OpenSSL 3.x, TLS 1.2/1.3 only, ECDSA
//////////////////////////////////////////////////////////////////////#*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "ystring.h"
#include "file.h" /* RecvPeek() */
#include "proc.h"
#include "vsignal.h"
#include "ysignal.h"
#include "fpoll.h"

#ifdef daVARGS
#undef VARGS
#define VARGS daVARGS
#define LINESIZE 1024
#endif

#include "log.h"

typedef struct {
	const char **se_av;
	int se_ac;
} SslEnv;

#define _VERSION_H /* include macro definitions only */
#include "../src/version.c"

#ifdef _MSC_VER
#undef ERROR
#undef X509
#undef X509_NAME
#endif

int randstack_call(int strg,iFUNCP func, ...);
char **move_envarg(int ac,const char *av[],const char **areap,int *lengp,int *sizep);
long Gettimeofday(int *usec);
int CFI_init(int ac,const char *av[]);
int PollIns(int timeout,int size,int *mask,int *rmask);
int setNonblockingIO(int fd,int on);
void set_nodelay(int sock,int onoff);
int SocketOf(int sock);
int LIBFILE_IS(PCStr(file),PVStr(xfile));
FILE *CFI_fopenShared(PCStr(mode));
int CFI_sharedLock();
int CFI_exclusiveLock();
int CFI_unLock();
int getthreadid();
const char *CFI_FILTER_ID();
int setCloseOnFork(PCStr(wh),int fd);
int clearCloseOnFork(PCStr(wh),int fd);
int ShutdownSocket(int fd);
void set_linger(int sock,int secs);

#define LSILENT	-1
#define LERROR	0
#define LTRACE	1
#define LDEBUG	2
static int loglevel = LERROR;
#define ERROR	(loglevel < LERROR)?0:DOLOG
#define TRACE	(loglevel < LTRACE)?0:DOLOG
#define DEBUG	(loglevel < LDEBUG)?0:DOLOG
#define VDEBUG	!LOG_VERBOSE?0:DEBUG

static FILE *stdctl;
static const char *client_host;
static int PID;
static int Builtin;
static int DOLOG(PCStr(fmt),...)
{	CStr(xfmt,256);
	CStr(head,256);
	SSigMask sMask;
	VARGS(8,fmt);

	setSSigMask(sMask);
	if( Builtin )
		sprintf(head,"## SSLway");
	else
	sprintf(head,"## SSLway[%d](%s)",PID,client_host);
	sprintf(xfmt,"%%s %s\n",fmt);
	syslog_ERROR(xfmt,head,VA8);
	resetSSigMask(sMask);
	return 0;
}

#ifndef SSL_FILETYPE_PEM /*{*/
/*BEGIN_STAB(ssl)*/
#ifdef __cplusplus
extern "C" {
#endif

/* OpenSSL 3.x compatible type definitions */
#define SSL_FILETYPE_PEM 1
#define SSL_VERIFY_NONE			0x00
#define SSL_VERIFY_PEER			0x01
#define SSL_VERIFY_FAIL_IF_NO_PEER_CERT	0x02
#define SSL_VERIFY_CLIENT_ONCE		0x04

#define SSL_CTRL_OPTIONS		32
#define SSL_CTRL_SET_MIN_PROTO_VERSION	123
#define SSL_CTRL_SET_MAX_PROTO_VERSION	124

/* TLS version constants */
#define TLS1_2_VERSION	0x0303
#define TLS1_3_VERSION	0x0304

/* SSL options for protocol versions */
#define SSL_OP_NO_SSLv2			0x00000000U  /* deprecated/removed in OpenSSL 3.x */
#define SSL_OP_NO_SSLv3			0x02000000U
#define SSL_OP_NO_TLSv1			0x04000000U
#define SSL_OP_NO_TLSv1_1		0x10000000U
#define SSL_OP_NO_TLSv1_2		0x08000000U
#define SSL_OP_NO_TLSv1_3		0x20000000U

typedef void SSL_CTX;
typedef void SSL_METHOD;
typedef void SSL;
typedef void X509;
typedef void X509_NAME;
typedef void X509_STORE;
typedef void X509_STORE_CTX;
typedef void BIO_METHOD;
typedef void BIO;
typedef void SSL_SESSION;
typedef void EVP_PKEY;
typedef void EVP_CIPHER;
typedef void SSL_CIPHER;
typedef void EVP_PKEY_CTX;
typedef void OSSL_PARAM;
typedef void OSSL_PARAM_BLD;
#define BIO_NOCLOSE 0

typedef void BIGNUM;
typedef void EC_KEY;
typedef void EC_GROUP;

/* ECDSA key types */
#define EVP_PKEY_EC 408
#define NID_X9_62_prime256v1 415  /* P-256 curve */
#define NID_secp384r1 715        /* P-384 curve */
#define NID_secp521r1 716        /* P-521 curve */

/* OpenSSL 3.x function declarations */
const char *OpenSSL_version(int t);
#define OPENSSL_VERSION 0

BIO_METHOD *BIO_s_mem();
BIO *BIO_new(BIO_METHOD*);
int BIO_puts(BIO *bp,char *buf);
int BIO_gets(BIO *bp,char *buf,int size);

BIO *BIO_new_fp(FILE *stream, int close_flag);
int BIO_free(BIO *a);
X509 *PEM_read_bio_X509(BIO*,...);
EVP_PKEY *PEM_read_bio_PrivateKey(BIO*,...);

SSL_CTX *SSL_CTX_new(SSL_METHOD *method);
void ERR_clear_error(void);
int OPENSSL_init_ssl(uint64_t opts, void *settings);
#define OPENSSL_INIT_LOAD_SSL_STRINGS 0x00200000L
#define OPENSSL_INIT_LOAD_CRYPTO_STRINGS 0x00000002L
SSL *SSL_new(SSL_CTX *ctx);
int  SSL_set_fd(SSL *ssl, int fd);
int  SSL_connect(SSL *ssl);
int  SSL_accept(SSL *ssl);
SSL_CIPHER *SSL_get_current_cipher(const SSL *ssl);
char *SSL_CIPHER_description(const SSL_CIPHER *sc,char *buf,int size);
int  SSL_write(SSL *ssl, const void *buf, int num);
int  SSL_read(SSL *ssl,void *buf,int num);
int  SSL_pending(SSL *s);
int  SSL_shutdown(SSL *ssl);
#define SSL_SENT_SHUTDOWN 1
#define SSL_RECEIVED_SHUTDOWN 2
int  SSL_get_shutdown(SSL *ssl);
void SSL_set_connect_state(SSL *s);
void SSL_set_accept_state(SSL *s);
int  SSL_get_error(SSL *s,int ret_code);
X509 *SSL_get_peer_certificate(SSL *ssl);

SSL_SESSION *SSL_SESSION_new(void);
SSL_CTX *SSL_set_SSL_CTX(SSL *ssl, SSL_CTX* ctx);/*OPT(0)*/
const char *SSL_get_servername(const SSL *s, const int type);/*OPT(0)*/
int SSL_get_servername_type(const SSL *s);/*OPT(0)*/
long SSL_CTX_callback_ctrl(SSL_CTX *, int, void (*)(void));/*OPT(0)*/
typedef void (*SNCB)();
#define SSL_CTRL_SET_TLSEXT_SERVERNAME_CB 53
#define SSL_CTRL_SET_TLSEXT_HOSTNAME 55
#define TLSEXT_NAMETYPE_host_name 0
#define SSL_CTX_set_tlsext_servername_callback(ctx, cb) \
	SSL_CTX_callback_ctrl(ctx,SSL_CTRL_SET_TLSEXT_SERVERNAME_CB,(SNCB)cb)
#define SSL_set_tlsext_host_name(con,name) \
	SSL_ctrl(con,SSL_CTRL_SET_TLSEXT_HOSTNAME,TLSEXT_NAMETYPE_host_name,(char *)name)

#define SSL_session_reused(ssl) 0
int SSL_CTX_add_session(SSL_CTX *ctx, SSL_SESSION *c);
SSL_SESSION *SSL_get_session(SSL *ssl);
int SSL_set_session(SSL *ssl,SSL_SESSION *sess);
int SSL_CTX_use_certificate(SSL_CTX *ctx, X509 *x);
int SSL_CTX_use_PrivateKey(SSL_CTX *ctx, EVP_PKEY *pkey);
X509 *SSL_get_certificate(SSL *ssl);
EVP_PKEY *SSL_get_privatekey(SSL *ssl);
#define EVP_PKEY_RSA 6
SSL_SESSION *d2i_SSL_SESSION(SSL_SESSION **a,unsigned char **pp,long length);
int i2d_SSL_SESSION(SSL_SESSION *in, unsigned char **pp);
X509 *d2i_X509(X509 **x,unsigned char**in,int len);
int i2d_X509(X509 *x,unsigned char **pp);
EVP_PKEY *d2i_PrivateKey(int type,EVP_PKEY **a,unsigned char **pp,long length);
int i2d_PrivateKey(EVP_PKEY *a,unsigned char **pp);

long SSL_ctrl(SSL *ssl,int cmd, long larg, void *parg);
long SSL_CTX_ctrl(SSL_CTX *ctx,int cmd, long larg, void *parg);
int  SSL_CTX_check_private_key(SSL_CTX *ctx);
X509_STORE *SSL_CTX_get_cert_store(SSL_CTX *);
int SSL_CTX_load_verify_locations(SSL_CTX *ctx,PCStr(CAfile),PCStr(CApath));
int  SSL_CTX_set_cipher_list(SSL_CTX *,PCStr(str));
int  SSL_CTX_set_ciphersuites(SSL_CTX *ctx, const char *str);/*TLS1.3*/
typedef int pem_password_cb(char buf[], int size, int rwflag, void *userdata);
void SSL_CTX_set_default_passwd_cb(SSL_CTX *ctx, pem_password_cb *cb);
int  SSL_CTX_set_default_verify_paths(SSL_CTX *ctx);
void SSL_CTX_set_verify(SSL_CTX *ctx,int mode, int (*callback)(int, X509_STORE_CTX *));
int  SSL_CTX_use_PrivateKey_file(SSL_CTX *ctx,PCStr(file), int type);
int  SSL_CTX_use_certificate_file(SSL_CTX *ctx,PCStr(file), int type);
int  SSL_CTX_use_certificate_chain_file(SSL_CTX *ctx,PCStr(file));/*OPT(0)*/

/* TLS method - OpenSSL 3.x uses flexible methods */
SSL_METHOD *TLS_server_method();
SSL_METHOD *TLS_client_method();
SSL_METHOD *TLS_method();

/* Set min/max protocol versions */
#define SSL_CTX_set_min_proto_version(ctx, version) \
	SSL_CTX_ctrl(ctx, SSL_CTRL_SET_MIN_PROTO_VERSION, version, NULL)
#define SSL_CTX_set_max_proto_version(ctx, version) \
	SSL_CTX_ctrl(ctx, SSL_CTRL_SET_MAX_PROTO_VERSION, version, NULL)

X509_NAME *X509_get_issuer_name(X509 *a);
int i2d_X509_bio(BIO *bp,X509 *x509);
char *X509_NAME_oneline(X509_NAME *a,char buf[],int size);
const char *X509_verify_cert_error_string(long n);
X509 *X509_STORE_CTX_get_current_cert(X509_STORE_CTX *ctx);
int X509_STORE_CTX_get_error(X509_STORE_CTX *ctx);
int X509_STORE_CTX_get_error_depth(X509_STORE_CTX *ctx);
X509_NAME *X509_get_subject_name(X509 *a);
void X509_free(X509 *a);

/* ECDSA/EC key functions for OpenSSL 3.x */
EVP_PKEY *EVP_EC_gen(const char *curve);/*OPT(0)*/
EVP_PKEY *EVP_PKEY_new();
void EVP_PKEY_free(EVP_PKEY *pkey);
int EVP_PKEY_id(const EVP_PKEY *pkey);
int PEM_write_PrivateKey(FILE *fp, EVP_PKEY *x, const EVP_CIPHER *enc,
                         unsigned char *kstr, int klen,
                         pem_password_cb *cb, void *u);
int PEM_write_PUBKEY(FILE *fp, EVP_PKEY *x);
EVP_PKEY *PEM_read_PrivateKey(FILE *fp, EVP_PKEY **x, pem_password_cb *cb, void *u);

/* For signing with ECDSA */
#define NID_sha256 672
#define NID_sha384 673
int EVP_PKEY_size(EVP_PKEY *pkey);
int EVP_DigestSign(void *ctx, unsigned char *sigret, size_t *siglen,
                   const unsigned char *tbs, size_t tbslen);
int EVP_DigestVerify(void *ctx, const unsigned char *sigret, size_t siglen,
                     const unsigned char *tbs, size_t tbslen);

typedef struct {
	int	ssl_version;
 unsigned int	key_arg_length;
 unsigned char	key_arg[8];
	int	master_key_length;
 unsigned char	master_key[48];
 unsigned int	session_id_length;
 unsigned char	session_id[32];
} SessionHead;

void ERR_load_crypto_strings(void);
X509 *PEM_read_X509(FILE*fp,X509**x,pem_password_cb*cb,void *u);
EVP_PKEY *PEM_read_bio_PUBKEY(BIO *bp,EVP_PKEY **x,pem_password_cb *cb,void *u);
EVP_PKEY *X509_get_pubkey(X509 *x);

/* Signature functions - OpenSSL 3.x compatible */
typedef void EVP_MD_CTX;
typedef void EVP_MD;
EVP_MD_CTX *EVP_MD_CTX_new();
void EVP_MD_CTX_free(EVP_MD_CTX *ctx);
const EVP_MD *EVP_sha256();
int EVP_DigestSignInit(EVP_MD_CTX *ctx, EVP_PKEY_CTX **pctx, const EVP_MD *type,
                       void *e, EVP_PKEY *pkey);
int EVP_DigestSignUpdate(EVP_MD_CTX *ctx, const void *d, size_t cnt);
int EVP_DigestSignFinal(EVP_MD_CTX *ctx, unsigned char *sig, size_t *siglen);
int EVP_DigestVerifyInit(EVP_MD_CTX *ctx, EVP_PKEY_CTX **pctx, const EVP_MD *type,
                         void *e, EVP_PKEY *pkey);
int EVP_DigestVerifyUpdate(EVP_MD_CTX *ctx, const void *d, size_t cnt);
int EVP_DigestVerifyFinal(EVP_MD_CTX *ctx, const unsigned char *sig, size_t siglen);

#ifdef __cplusplus
}
#endif
#endif /*}*/

#ifdef __cplusplus
extern "C" {
#endif
unsigned long ERR_get_error(void);
char *ERR_error_string_n(int,char*,int);
void ERR_print_errors_fp(FILE *fp);
void RAND_seed(const void *buf,int num);
void X509_STORE_set_flags(X509_STORE *ctx, long flags);/*OPT(0)*/
#define X509_V_FLAG_CRL_CHECK		0x04
#define X509_V_FLAG_CRL_CHECK_ALL	0x08

int SSL_CTX_set_session_id_context(SSL_CTX*,const unsigned char *sid_ctx,unsigned int sid_ctx_len); /*OPT(0)*/
typedef int (*GEN_SESSION_CB)(const SSL *ssl,unsigned char *id,unsigned int *id_len);
int SSL_CTX_set_generate_session_id(SSL_CTX *ctx, GEN_SESSION_CB cb);/*OPT(0)*/
void OPENSSL_add_all_algorithms_conf(void);/*OPT(0)*/

BIO *BIO_new_file(const char *filename, const char *mode);
typedef void DH;
DH *PEM_read_bio_DHparams(BIO *bp, DH **x, pem_password_cb *cb, void *u);/*OPT(0)*/
void DH_free(DH *dh);/*OPT(0)*/
#define SSL_CTRL_SET_TMP_DH 3
#define SSL_CTX_set_tmp_dh(ctx,dh) \
        SSL_CTX_ctrl(ctx,SSL_CTRL_SET_TMP_DH,0,(char *)dh)

/* ECDH auto selection for TLS 1.2/1.3 */
#define SSL_CTRL_SET_ECDH_AUTO 94
#define SSL_CTX_set_ecdh_auto(ctx, onoff) \
        SSL_CTX_ctrl(ctx, SSL_CTRL_SET_ECDH_AUTO, onoff, NULL)

/* For OpenSSL 3.x - use groups instead of curves */
int SSL_CTX_set1_groups_list(SSL_CTX *ctx, const char *list);/*OPT(0)*/

#ifdef __cplusplus
}
#endif

/*END_STAB*/

static unsigned char *ssid = (unsigned char*)"SSLway";
static int ssid_len = 1;

typedef unsigned char Uchar;
int sslway_dl();
static void putDylibError(){
 fprintf(stderr,"-- ERROR: can't link the SSL/Crypto library.\n");
 fprintf(stderr,"-- Hint: use -vl option to trace the required library,\n");
 fprintf(stderr,"--- For Debian Bookworm/Trixie, ensure libssl3 and libcrypto3 are installed.\n");
 fprintf(stderr,"--- Typical paths: /usr/lib/x86_64-linux-gnu/libssl.so.3\n");
 fprintf(stderr,"--- Set the library version as DYLIB='+,libssl.so.3'\n");
}
static int checkCrypt(){
	if( sslway_dl() == 0 ){
		putDylibError();
		return -1;
	}
	return 0;
}

/* ECDSA signing function using OpenSSL 3.x EVP API */
int signECDSA(EVP_PKEY *pkey, PCStr(data), int dlen, PVStr(sig), size_t *slen){
	EVP_MD_CTX *mdctx;
	int ok = 0;

	if( checkCrypt() < 0 )
		return 0;

	mdctx = EVP_MD_CTX_new();
	if( mdctx == NULL ){
		return 0;
	}

	if( EVP_DigestSignInit(mdctx, NULL, EVP_sha256(), NULL, pkey) <= 0 ){
		EVP_MD_CTX_free(mdctx);
		return 0;
	}

	if( EVP_DigestSignUpdate(mdctx, data, dlen) <= 0 ){
		EVP_MD_CTX_free(mdctx);
		return 0;
	}

	/* Get signature length first */
	if( EVP_DigestSignFinal(mdctx, NULL, slen) <= 0 ){
		EVP_MD_CTX_free(mdctx);
		return 0;
	}

	/* Now sign */
	if( EVP_DigestSignFinal(mdctx, (unsigned char*)sig, slen) <= 0 ){
		EVP_MD_CTX_free(mdctx);
		return 0;
	}

	ok = 1;
	EVP_MD_CTX_free(mdctx);
	return ok;
}

static char *privPEM;
static EVP_PKEY *privKey;

static int pass_cb(char buf[],int size,int rwflag,void *userdata){
	fprintf(stderr,"## Passphrase for KEY requested:%X\n",p2i(userdata));
	Xstrcpy(ZVStr(buf,size),(char*)userdata);
	return strlen((char*)userdata);
}

int SignECDSA(PCStr(privkey),PCStr(data),PCStr(pass),PCStr(md),int mlen,PVStr(sig),size_t *slen){
	EVP_PKEY *pkey;
	int ok;
	CStr(keybuff,8*1024);
	BIO *Bp;
	const char *cbdata = pass;

	if( checkCrypt() < 0 ){
		return 0;
	}

	if( privKey == NULL || privPEM == NULL || strcmp(privPEM,privkey)!=0 ){
		OPENSSL_add_all_algorithms_conf();
		if( data == 0 || *data == 0 ){
			FILE *fp;
			int rcc;
			fp = fopen(privkey,"r");
			if( fp == NULL ){
				fprintf(stderr,"# %s: Can't open\n",privkey);
				return 0;
			}
			rcc = fread(keybuff,1,sizeof(keybuff)-1,fp);
			fclose(fp);

			if( rcc <= 0 ){
				fprintf(stderr,"# %s: Can't read\n",privkey);
				return 0;
			}
			keybuff[rcc] = 0;
			data = keybuff;
		}

		Bp = BIO_new(BIO_s_mem());
		BIO_puts(Bp,(char*)data);
		pkey = NULL;
		ERR_load_crypto_strings();
		if( cbdata == 0 )
			cbdata = "";
		pkey = PEM_read_bio_PrivateKey(Bp,&pkey,NULL,cbdata);
		if( pkey == 0 ){
			fprintf(stderr,"# %s: Can't load\n",privkey);
			return 0;
		}
		privPEM = strdup(privkey);
		privKey = pkey;
		TRACE("loaded %s",privkey);
	}
	if( sig == NULL ){
		return 1;
	}
	ok = signECDSA(privKey,md,mlen,AVStr(sig),slen);
	return ok;
}

int verifyECDSA(EVP_PKEY *pkey, PCStr(data), int dlen, PCStr(sig), size_t slen){
	EVP_MD_CTX *mdctx;
	int ok = 0;

	if( checkCrypt() < 0 )
		return 0;

	mdctx = EVP_MD_CTX_new();
	if( mdctx == NULL ){
		return 0;
	}

	if( EVP_DigestVerifyInit(mdctx, NULL, EVP_sha256(), NULL, pkey) <= 0 ){
		EVP_MD_CTX_free(mdctx);
		return 0;
	}

	if( EVP_DigestVerifyUpdate(mdctx, data, dlen) <= 0 ){
		EVP_MD_CTX_free(mdctx);
		return 0;
	}

	ok = EVP_DigestVerifyFinal(mdctx, (unsigned char*)sig, slen);
	EVP_MD_CTX_free(mdctx);
	return (ok == 1) ? 1 : 0;
}

static char *pubPEM;
static EVP_PKEY *pubKey;

int VerifyECDSA(PCStr(pubkey),PCStr(data),PCStr(md),int mlen,PCStr(sig),size_t slen){
	X509 *x509;
	EVP_PKEY *pkey;
	int ok;
	CStr(keybuff,8*1024);
	BIO *Bp;

	if( checkCrypt() < 0 )
		return 0;

	if( pubKey == NULL || pubPEM == 0 || strcmp(pubPEM,pubkey) != 0 ){
		if( data == 0 || *data == 0 ){
			FILE *fp;
			int rcc;
			fp = fopen(pubkey,"r");
			if( fp == NULL ){
				fprintf(stderr,"# %s: Can't open\n",pubkey);
				return 0;
			}
			rcc = fread(keybuff,1,sizeof(keybuff)-1,fp);
			fclose(fp);
			if( rcc <= 0 ){
				fprintf(stderr,"# %s: Can't read\n",pubkey);
				return 0;
			}
			keybuff[rcc] = 0;
			data = keybuff;
		}
		Bp = BIO_new(BIO_s_mem());
		BIO_puts(Bp,(char*)data);
		pkey = NULL;
		x509 = PEM_read_bio_X509(Bp,NULL,NULL,NULL);
		if( x509 == NULL ){
			fprintf(stderr,"# %s: BAD CERT\n",pubkey);
			return 0;
		}
		pubPEM = strdup(pubkey);
		pkey = X509_get_pubkey(x509);
		pubKey = pkey;
		TRACE("loaded %s",pubkey);
	}

	if( sig == NULL ){
		return 1;
	}
	ok = verifyECDSA(pubKey,md,mlen,sig,slen);
	return ok;
}

static EVP_PKEY *newECpubkey(PCStr(key)){
	BIO *Bp;
	EVP_PKEY *pkey;

	Bp = BIO_new(BIO_s_mem());
	BIO_puts(Bp,(char*)key);
	pkey = PEM_read_bio_PUBKEY(Bp,NULL,NULL,NULL);
	return pkey;
}

#ifndef ISDLIB
#include "randtext.c"
#endif

static double Start;
static double laps[32];
static const char *lapd[32];
static int lapx;
const char *SSLstage;
#define Lap(msg)  ((SSLstage=msg),(loglevel<LDEBUG)?0:((lapd[lapx]=msg),(laps[lapx++]=Time())))
static int nthcall;
static SSL_CTX *ctx_cache;
static int ctx_filter_id;
int (*SSL_fatalCB)(PCStr(mssg),...);
static char *SSLLIBS;

static void opt1(PCStr(arg)){
	if( strncmp(arg,"-vv",3) == 0 || strncmp(arg,"-vd",3) == 0 ){
		loglevel = LDEBUG;
	}else
	if( strncmp(arg,"-vu",3) == 0 ){
		loglevel = LTRACE;
	}else
	if( strncmp(arg,"-vt",3) == 0 ){
		loglevel = LERROR;
	}else
	if( strncmp(arg,"-vs",3) == 0 ){
		loglevel = LSILENT;
	}
}

static void loadSessions(SSL_CTX *ctx,SSL *ssl,int what);
static void saveSessions(SSL_CTX *ctx,SSL *ssl,int what);
#define XACC	0
#define XCON	1
#define XCTX	2
#define MASK_SCACHE  ((1<<XACC)|(1<<XCON))
#define MASK_CACHE   ((1<<XACC)|(1<<XCON)|(1<<XCTX))
static int do_cache = (1<<XACC)|(1<<XCTX);

static int tlsdebug;
#define DBG_SCACHE	1
#define DBG_SCACHEV	2
#define DBG_XCACHE	1

static int SNIopts;
#define SNI_MANDATORY	1
#define SNI_WARN	2

#define OPT_SHUT_SEND	0x0001
#define OPT_SHUT_WAIT	0x0002
#define OPT_SHUT_FLUSH	0x0004 /* flush Shutdown Alert on input if pending */
#define OPT_SHUT_OPTS	(OPT_SHUT_SEND|OPT_SHUT_WAIT|OPT_SHUT_FLUSH)
static int SSLopts[2] = {OPT_SHUT_FLUSH,OPT_SHUT_FLUSH};
static int SHUTwait[2] = {300,300}; /* milli-seconds */

typedef struct DGCtx *DGCp;
static scanListFunc scan_TLSCONF1(PCStr(conf),DGCp ctx){
	CStr(what,128);
	CStr(val,128);

	if( *conf == '-' ){
		opt1(conf);
		return 0;
	}
	fieldScan(conf,what,val);
	if( strcaseeq(what,"debug") ){
		tlsdebug |= DBG_SCACHE | DBG_XCACHE;
	}else
	if( strcaseeq(what,"shutdown") ){
		const char *op;
		int opts = OPT_SHUT_SEND;
		int wms = 0;
		if( op = strstr(val,"wait") ){
			opts = OPT_SHUT_OPTS;
			if( strchr("./",op[4]) && isdigit(op[5]) ){
				wms = atoi(op+5);
			}
		}
		if( streq(val,"none") ){
			SSLopts[XACC] &= ~OPT_SHUT_OPTS;
			SSLopts[XCON] &= ~OPT_SHUT_OPTS;
		}else
		if( streq(val,"flush") ){
			SSLopts[XACC] &= ~OPT_SHUT_OPTS;
			SSLopts[XACC] |=  OPT_SHUT_FLUSH;
			SSLopts[XCON] &= ~OPT_SHUT_OPTS;
			SSLopts[XCON] |=  OPT_SHUT_FLUSH;
		}else
		if( !strstr(val,"acc") && !strstr(val,"con") ){
			SSLopts[XACC] |= opts;
			SSLopts[XCON] |= opts;
			if( wms ) SHUTwait[XACC] = SHUTwait[XCON] = wms;
		}else
		if( strstr(val,"acc" ) ){
			SSLopts[XACC] |= opts;
			if( wms ) SHUTwait[XACC] = wms;
		}else
		if( strstr(val,"con" ) ){
			SSLopts[XCON] |= opts;
			if( wms ) SHUTwait[XCON] = wms;
		}
		if( streq(val,"vrfy") ){
		}
	}else
	if( strcaseeq(what,"sni") ){
		if( streq(val,"only") ) SNIopts |= SNI_MANDATORY;
		if( streq(val,"warn") ) SNIopts |= SNI_WARN;
	}else
	if( strcaseeq(what,"cache") ){
		if( streq(val,"no" ) ) do_cache = 0;
		if( streq(val,"do" ) ) do_cache = MASK_CACHE;
	}else
	if( strcaseeq(what,"xcache") ){
		if( streq(val,"no" ) ) do_cache &= ~(1 << XCTX);
		if( streq(val,"do" ) ) do_cache |=  (1 << XCTX);
	}else
	if( strcaseeq(what,"scache") ){
		int xmask = do_cache & ~MASK_SCACHE;
		if( *val == 0 )
			do_cache = (1 << XACC) | (1 << XCON);
		else{
			if( streq(val,"no" ) ) do_cache &= ~3;
			if( streq(val,"do" ) ) do_cache |= 3;
			if( streq(val,"acc") ) do_cache = (1 << XACC);
			if( streq(val,"con") ) do_cache = (1 << XCON);
		}
		do_cache |= xmask;
	}
	else
	if( strcaseeq(what,"libs") ){
		SSLLIBS = stralloc(val);
	}
	else
	if( strcaseeq(what,"context") ){
		ssid = (Uchar*)stralloc(val);
		ssid_len = strlen(val);
	}
	return 0;
}
void scan_TLSCONFs(DGCp ctx,PCStr(confs)){
	scan_commaListL(confs,0,scanListCall scan_TLSCONF1,ctx);
}

static const char *CERTF_PASS = "common.pas";
static const char *CERTF_ME   = "me.pem";
static const char *CERTF_TOSV = "to-sv.pem";    /* to be shown to servers */
static const char *CERTF_SVP  = "to-sv.%s.pem"; /* to be shown to the server %s */
static const char *CERTF_TOCL = "to-cl.pem";    /* to be shown to clients */
static const char *CERTF_CLP  = "to-cl.%s.pem"; /* to be shown to the client %s */
static const char *CERTF_SNI  = "sn.%s.pem";    /* SNI */
static const char *CERTF_NIF  = "if.%s.pem";    /* for the network interface */
static const char *CERTF_CLA  = "to-sv-if.%s.pem"; /* for outgoing net-if */
static const char *CERTF_SVA  = "sa.%s.pem";    /* for incoming net-if */

static const char *CERTF_SVCA = "ca-sv.pem";
static const char *CERTD_SVCA = "ca-sv";
static const char *CERTF_CLCA = "ca-cl.pem";
static const char *CERTD_CLCA = "ca-cl";

static char *certdir;
static int certdir_set;
void set_CERTDIR(PCStr(dir),int exp){
	syslog_DEBUG("--CERTS %d %s\n",exp,dir?dir:"");
	certdir = stralloc(dir);
	certdir_set = exp;
}

#define ISCLNT	0x0001
#define ISDIR	0x0002
#define GOTCERT	0x0004 /* don't try if the file is not found */
#define SRCHLIB	0x0008

int File_is(PCStr(path));
int fileIsdir(PCStr(path));
int File_isreg(PCStr(path));
static int findcert(PCStr(path),PVStr(xpath),int flags){
	IStr(dirpath,1024);
	int found = 0;

	if( path == 0 ){
		return 0;
	}
	if( certdir ){
		sprintf(dirpath,"%s/%s",certdir,path);
		VDEBUG("--CERTS ? %s",dirpath);
		if( (flags & ISDIR) )
			found = fileIsdir(dirpath);
		else	found = File_is(dirpath);
		if( found ){
			if( xpath )
				strcpy(xpath,dirpath);
			VDEBUG("--CERTS ! %s",dirpath);
			return 1;
		}
		if( certdir_set ){
			return 0;
		}
	}
	if( found == 0 && (flags & SRCHLIB) ){
		found = LIBFILE_IS(path,BVStr(xpath));
	}
	return found;
}
#define LIBFILE_IS(path,xpath) findcert(path,xpath,SRCHLIB)

static int setcert1(SSL_CTX *ctx,PCStr(certfile),PCStr(keyfile),int clnt);
static int getcertdflt(SSL_CTX *ctx,int clnt){
	int gotdflt = 0;
	IStr(path,1024);
	int code;

	if( clnt )
		findcert(CERTF_TOSV,AVStr(path),0);
	else	findcert(CERTF_TOCL,AVStr(path),0);
	if( path[0] == 0 ){
		findcert(CERTF_ME,AVStr(path),0);
	}
	if( path[0] != 0 ){
		code = setcert1(ctx,path,path,clnt);
		VDEBUG("--CERTS got dflt %X [%s] code=%d",clnt,path,code);
		if( code == 0 ){
			gotdflt = 1;
		}
	}
	return gotdflt;
}

static void ssl_printf(SSL *ssl,int fd,PCStr(fmt),...)
{	CStr(buf,0x4000);
	VARGS(8,fmt);

	sprintf(buf,fmt,VA8);
	if( ssl )
		SSL_write(ssl,buf,strlen(buf));
	else{	IGNRETP write(fd,buf,strlen(buf)); }
}
static void sendIdent(PCStr(ident),PCStr(sb),PCStr(is)){
	const char *env;
	int fd;
	FILE *fp;
	if( env = getenv("CFI_IDENT") ){
		if( '0' <= env[0] && env[0] < '9' ){
			fd = atoi(env);
			if( fp = fdopen(dup(fd),"w") ){
				fprintf(fp,"Ident: %s\r\n",ident);
				fprintf(fp,"Subject: %s\r\n",sb);
				fprintf(fp,"Issuer: %s\r\n",is);
				fclose(fp);
			}
		}
	}
}
static void ssl_prcert(SSL *ssl,int show,SSL *outssl,int outfd,PCStr(what))
{	X509 *peer;
	CStr(subjb,256);
	const char *sb;
	CStr(issrb,256);
	const char *is;
	const char *dp;
	CStr(ident,256);

	ident[0] = 0;
	if( peer = SSL_get_peer_certificate(ssl) ){
		sb = X509_NAME_oneline(X509_get_subject_name(peer),subjb,sizeof(subjb));
		is = X509_NAME_oneline(X509_get_issuer_name(peer),issrb,sizeof(issrb));
		if( show ){
			ssl_printf(outssl,outfd,
				"##[SSLway: %s's certificate]\r\n",what);
			ssl_printf(outssl,outfd,"## Subject: %s\r\n",sb);
			ssl_printf(outssl,outfd,"## Issuer: %s\r\n",is);
		}
		ERROR("%s's cert. = **subject<<%s>> **issuer<<%s>>",what,sb,is);
		if( dp = (char*)strcasestr(sb,"/emailAddress=") )
			wordscanY(dp+14,AVStr(ident),sizeof(ident),"^/");
		else
		if( dp = (char*)strcasestr(sb,"/email=") )
			wordscanY(dp+7,AVStr(ident),sizeof(ident),"^/");
		else	strcpy(ident,"someone");
		X509_free(peer);
	}else{
		TRACE("%s's cert. = NONE",what);
		strcpy(ident,"anonymous");
		sb = "";
		is = "";
	}
	sendIdent(ident,sb,is);
	if( stdctl ){
		fprintf(stdctl,"CFI/1.0 200- Ident:%s\r\n",ident);
		fprintf(stdctl,"CFI/1.0 200 Certificate:%s//%s\r\n",sb,is);
		fflush(stdctl);
	}
}
static void eRR_print_errors_fp(FILE *fp)
{	int code;
	const char *strp;
	CStr(str,1024);
	const char *file;
	const char *line;
	const char *opttxt;

	if( isWindows() ){
		/* OpenSSL-0.9.7c on Win32 aborts in ERR_print_errors_fp() */
		while( code = ERR_get_error() ){
			strp = ERR_error_string_n(code,str,sizeof(str));
			file = "";
			line = "";
			opttxt = "";
			ERROR("SSL-ERRCODE: %X\r\n%d:%s:%s:%s:%s",code,getpid(),
				str,file,line,opttxt);
		}
	}else{
		ERR_print_errors_fp(fp);
	}
}
#undef	ERR_print_errors_fp
#define	ERR_print_errors_fp	eRR_print_errors_fp

/* Show current cipher */
static int showCurrentCipher(SSL *ssl){
	void *sc;
	IStr(desc,256);
	const char *descp;

	if( sc = SSL_get_current_cipher(ssl) ){
		if( descp = SSL_CIPHER_description(sc,desc,sizeof(desc)) ){
			DEBUG("-- CIPHER: %s",desc);
			return 0;
		}
	}
	DEBUG("ERROR: Failed getting CIPHER_ description");
	ERR_print_errors_fp(stderr);
	return -1;
}

static void clearCache(SSL_CTX *ctx,SSL *ssl,int what);
static void set_vhost(SSL *conSSL,SslEnv *env);
static SSL *ssl_conn(SSL_CTX *ctx,int confd,SslEnv *env)
{	SSL *conSSL;

	Lap("ssl_conn() start");
	conSSL = SSL_new(ctx);
	set_vhost(conSSL,env);
	loadSessions(ctx,conSSL,XCON);

	SSL_set_connect_state(conSSL);
	SSL_set_fd(conSSL,SocketOf(confd));
	Lap("before connect");
	if( SSL_connect(conSSL) < 0 ){
		ERROR("connect failed");
		ERR_print_errors_fp(stderr);
		if( SSL_fatalCB ){
			(*SSL_fatalCB)("ssl_conn() failed\n");
		}
		clearCache(ctx,conSSL,XCON);
		return NULL;
	}else{
		Lap("after connect");
		saveSessions(ctx,conSSL,XCON);
		TRACE("connected");
		showCurrentCipher(conSSL);
		return conSSL;
	}
}

static SSL *ssl_acc(SSL_CTX *ctx,int accfd)
{	SSL *accSSL;

	Lap("ssl_acc() start");
	loadSessions(ctx,NULL,XACC);
	accSSL = SSL_new(ctx);
	SSL_set_accept_state(accSSL);
	SSL_set_fd(accSSL,SocketOf(accfd));
	SSL_set_fd(accSSL,SocketOf(accfd));
	Lap("before accept");
	if( SSL_accept(accSSL) < 0 ){
		ERROR("accept failed");
		ERR_print_errors_fp(stderr);
		if( SSL_fatalCB ){
			(*SSL_fatalCB)("ssl_acc() failed\n");
		}
		return NULL;
	}else{
		Lap("after accept");
		saveSessions(ctx,accSSL,XACC);
		TRACE("accepted");
		showCurrentCipher(accSSL);
		return accSSL;
	}
}
static int nodefaultCA(PCStr(file)){
	IStr(xpath,1024);
	refQStr(dp,xpath);
	if( file ){
		strcpy(xpath,file);
		if( dp = strtailstr(xpath,".pem") ){
			strcpy(dp,".nodefault");
			if( File_is(xpath) ) return 1;
		}
		strcat(xpath,"/nodefault");
		if( File_is(xpath) ) return 2;
	}
	return 0;
}
static void ssl_setCAs(SSL_CTX *ctx,PCStr(file),PCStr(dir))
{	CStr(xfile,1024);
	CStr(xdir,1024);

	if( LIBFILE_IS(file,AVStr(xfile)) ) file = xfile;
	if( findcert(dir,AVStr(xdir),ISDIR) ) dir = xdir;

	if( file ){
		if( SSL_CTX_load_verify_locations(ctx,file,0) ){
			TRACE("CAs = OK CAfile[%s]",file);
		}else{
			ERROR("CAs not found or wrong: CAfile[%s]",file);
			ERR_print_errors_fp(stderr);
		}
	}
	if( dir ){
		if( SSL_CTX_load_verify_locations(ctx,0,dir) ){
			TRACE("CAs = OK CApath[%s]",dir);
		}else{
			ERROR("CAs not found or wrong: CApath[%s]",dir);
			ERR_print_errors_fp(stderr);
		}
	}
	if( nodefaultCA(file) || nodefaultCA(dir) ){
		TRACE("CAs = no DEFAULT");
	}else{
		if( SSL_CTX_set_default_verify_paths(ctx) ){
			TRACE("CAs = OK, set the DEFAULT");
		}else{
			ERROR("CAs wrong DEFAULT");
			ERR_print_errors_fp(stderr);
		}
	}
	return;
}

typedef struct {
  const char	*c_cert;	/* cetificate file */
  const char	*c_key;		/* private key */
} CertKey1;
typedef struct {
	CertKey1 v_ck[8]; /**/
	int	 v_Ncert;
	int	 v_Nkey;
} CertKeyV;
typedef struct {
	CertKeyV x_certkey;
  const char	*x_pass;	/* to decrypt the cert */
  const char	*x_CApath;	/* CA's certificates */
  const char	*x_CAfile;	/* A CA's certificate */
	int	 x_do_SSL;	/* use SSL */
	int	 x_do_STLS;	/* enable STARTTLS */
	int	 x_nego_FTPDATA;
	int	 x_verify;
	int	 x_peeraddr;
	int	 x_sslver;
	int	 x_sslnover;
	double   x_Start;
	int	 x_Ready;
} SSLContext;

static const char sv_cert_default[] = "server-cert.pem";
static const char sv_key_default[] = "server-key.pem";
static const char sv_certkey_default[] = "server.pem";
static const char cl_cert_default[] = "client-cert.pem";
static const char cl_key_default[] = "client-key.pem";
static const char cl_certkey_default[] = "client.pem";
static const char *stls_proto;

static SSLContext sslctx[2] = {
	{ { {sv_cert_default, sv_key_default} } },
	{ { {cl_cert_default, cl_key_default} } },
};
static int   acc_bareHTTP = 0;
static int   verify_depth = -1;
static int   do_showCERT = 0;
static const char *cipher_list = NULL;
static const char *ciphersuites = NULL; /* TLS 1.3 ciphersuites */

#define sv_Start	sslctx[XACC].x_Start
#define sv_Ready	sslctx[XACC].x_Ready
#define cl_Start	sslctx[XCON].x_Start
#define cl_Ready	sslctx[XCON].x_Ready

#define sv_Cert		sslctx[XACC].x_certkey
#define sv_Ncert	sslctx[XACC].x_certkey.v_Ncert
#define sv_Nkey		sslctx[XACC].x_certkey.v_Nkey
#define sv_cert		sslctx[XACC].x_certkey.v_ck[sv_Ncert].c_cert
#define sv_key		sslctx[XACC].x_certkey.v_ck[sv_Nkey].c_key
#define sv_pass		sslctx[XACC].x_pass
#define cl_CApath	sslctx[XACC].x_CApath
#define cl_CAfile	sslctx[XACC].x_CAfile
#define do_accSSL	sslctx[XACC].x_do_SSL
#define do_accSTLS	sslctx[XACC].x_do_STLS
#define cl_vrfy		sslctx[XACC].x_verify
#define cl_nego_FTPDATA	sslctx[XACC].x_nego_FTPDATA
#define cl_addr		sslctx[XACC].x_peeraddr
#define cl_sslver	sslctx[XACC].x_sslver
#define cl_sslnover	sslctx[XACC].x_sslnover

#define cl_Cert		sslctx[XCON].x_certkey
#define cl_Ncert	sslctx[XCON].x_certkey.v_Ncert
#define cl_Nkey		sslctx[XCON].x_certkey.v_Nkey
#define cl_cert		sslctx[XCON].x_certkey.v_ck[cl_Ncert].c_cert
#define cl_key		sslctx[XCON].x_certkey.v_ck[cl_Nkey].c_key
#define cl_pass		sslctx[XCON].x_pass
#define sv_CApath	sslctx[XCON].x_CApath
#define sv_CAfile	sslctx[XCON].x_CAfile
#define do_conSSL	sslctx[XCON].x_do_SSL
#define do_conSTLS	sslctx[XCON].x_do_STLS
#define sv_vrfy		sslctx[XCON].x_verify
#define sv_nego_FTPDATA	sslctx[XCON].x_nego_FTPDATA
#define sv_addr		sslctx[XCON].x_peeraddr
#define sv_sslver	sslctx[XCON].x_sslver
#define sv_sslnover	sslctx[XCON].x_sslnover

#define ST_OPT		1
#define ST_FORCE	2
#define ST_AUTO		4 /* auto-detection of SSL by Client_Hello */
#define ST_SSL		8 /* AUTH SSL for FTP */

/* TLS version selection:
 * 1 = TLS 1.2 only
 * 2 = TLS 1.3 only
 * 3 = TLS 1.2 and 1.3 (default)
 */
#define TLSVER_12_ONLY	1
#define TLSVER_13_ONLY	2
#define TLSVER_12_13	3

static SSL_CTX *ssl_new(int serv)
{	SSL_CTX *ctx;
	SSL_METHOD *meth;
	int sslver;
	int sslnover;

	ERR_clear_error();
	/* OpenSSL 3.x initialization */
	OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS | OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL);

	/* Use flexible TLS method - version will be set via min/max */
	if( serv )
		meth = TLS_server_method();
	else
		meth = TLS_client_method();

	if( meth == 0 ){
		ERROR("no TLS method available");
		return NULL;
	}

	ctx = SSL_CTX_new(meth);
	if( ctx == NULL ){
		ERROR("SSL_CTX_new failed");
		return NULL;
	}

	/* Set minimum and maximum TLS versions based on configuration */
	sslver = serv ? cl_sslver : sv_sslver;
	sslnover = serv ? cl_sslnover : sv_sslnover;

	/* Default: TLS 1.2 and 1.3 */
	int min_ver = TLS1_2_VERSION;
	int max_ver = TLS1_3_VERSION;

	switch( sslver ){
		case TLSVER_12_ONLY:
			min_ver = TLS1_2_VERSION;
			max_ver = TLS1_2_VERSION;
			break;
		case TLSVER_13_ONLY:
			min_ver = TLS1_3_VERSION;
			max_ver = TLS1_3_VERSION;
			break;
		case TLSVER_12_13:
		default:
			min_ver = TLS1_2_VERSION;
			max_ver = TLS1_3_VERSION;
			break;
	}

	/* Apply version restrictions from sslnover if set */
	if( sslnover ){
		/* sslnover is used to disable certain versions */
		/* We only support TLS 1.2 and 1.3, so this is simpler */
		if( sslnover == 1 ){
			/* Disable TLS 1.2, use 1.3 only */
			min_ver = TLS1_3_VERSION;
		}else if( sslnover == 2 ){
			/* Disable TLS 1.3, use 1.2 only */
			max_ver = TLS1_2_VERSION;
		}
	}

	SSL_CTX_set_min_proto_version(ctx, min_ver);
	SSL_CTX_set_max_proto_version(ctx, max_ver);

	/* Enable automatic ECDH curve selection for TLS 1.2 */
	SSL_CTX_set_ecdh_auto(ctx, 1);

	/* Set preferred ECDH groups for TLS 1.3 */
	SSL_CTX_set1_groups_list(ctx, "X25519:P-256:P-384");

	return ctx;
}

static void passfilename(PCStr(keyfile),PVStr(passfile))
{	refQStr(dp,passfile); /**/

	strcpy(passfile,keyfile);
	dp = strrchr(passfile,'.');
	strcpy(dp,".pas");
	if( !File_is(passfile) ){
		if( dp = strrpbrk(passfile,"/\\") )
			dp++;
		else	dp = passfile;
		strcpy(dp,CERTF_PASS);
	}
}
static int Freadline(PCStr(path),PVStr(line),int size)
{	FILE *fp;
	int rcc;
	const char *dp;

	fp = fopen(path,"r");
	if( fp == NULL )
		return -1;

	if( 0 < (rcc = fread((char*)line,1,QVSSize(line,size),fp)) )
		setVStrEnd(line,rcc);
	else	setVStrEnd(line,0);
	fclose(fp);
	if( dp = strpbrk(line,"\r\n") )
		truncVStr(dp);
	return strlen(line);
}
static void scanpass(PCStr(arg))
{	const char *file;
	CStr(path,1024);
	const char *pass;
	CStr(passb,128);

	if( strncmp(arg,"file:",5) == 0 ){
		file = arg+5;
		if( LIBFILE_IS(file,AVStr(path)) )
			file = path;
		passb[0] = 0;
		Freadline(file,AVStr(passb),sizeof(passb));
		pass = passb;
	}else
	if( strncmp(arg,"pass:",5) == 0 ){
		pass = arg + 5;
	}else{
		ERROR("Usage: -pass { file:path | pass:string }");
		return;
	}
	if( pass[0] ){
		sv_pass = cl_pass = strdup(pass);
	}
}

unsigned int _inet_addrV4(PCStr(cp));
static void setaddrs(){
	const char *env;
	cl_addr = 0;
	sv_addr = 0;
	if( env = getenv("REMOTE_ADDR") ){
		cl_addr = _inet_addrV4(env);
	}
	if( env = getenv("SERVER_ADDR") ){
		sv_addr = _inet_addrV4(env);
	}
}

void msleep(int);
static int CFI_Lock(PCStr(wh),int rw){
	int rcode;
	int ri;
	double St = Time();

	if( CFI_exclusiveLock() == 0 ){
		return 0;
	}
	for( ri = 0; ri < 20; ri++ ){
		msleep(1);
		if( CFI_exclusiveLock() == 0 ){
			DEBUG("%s cache lock OK %d (%.3f)",wh,ri+1,Time()-St);
			return 0;
		}
	}
	ERROR("%s cache lock NG %d (%.3f)",wh,ri+1,Time()-St);
	return -1;
}

static int saveContext(SSL_CTX *ctx,SSL *ssl,int ac,char *av[]){
	X509 *cert;
	EVP_PKEY *ekey;
	unsigned char tmp[8*1024];
	unsigned char *pp;
	int len;
	FILE *fp;

	if( do_cache == 0 )
		return -1;
	if( (do_cache & (1 << XCTX)) == 0 )
		return -1;

	if( cert = SSL_get_certificate(ssl) ){
		if( (ekey = SSL_get_privatekey(ssl)) ){
			if( (cert = SSL_get_certificate(ssl)) ){
				if( CFI_Lock("saveContext",1) != 0 ){
					ERROR("ERROR: can't lock saveContext");
					return -1;
				}
				if( (fp = CFI_fopenShared("r+")) ){
					fprintf(fp,"%s\n",CFI_FILTER_ID());

					len = i2d_X509(cert,NULL);
					if( sizeof(tmp) <= len ){
						ERROR("CERT too large %d/%d\n",
							len,sizeof(tmp));
						goto CEXIT;
					}
					pp = tmp;
					len = i2d_X509(cert,&pp);
					fwrite(&len,1,sizeof(len),fp);
					fwrite(tmp,1,len,fp);

					len = i2d_PrivateKey(ekey,NULL);
					if( sizeof(tmp) <= len ){
						ERROR("PKEY too large %d/%d\n",
							len,sizeof(tmp));
						goto CEXIT;
					}
					pp = tmp;
					len = i2d_PrivateKey(ekey,&pp);
					fwrite(&len,1,sizeof(len),fp);
					fwrite(tmp,1,len,fp);

					fclose(fp);
					CFI_unLock();
					Lap("saveContext OK");
					return 0;
				}
			CEXIT:
				fclose(fp);
				CFI_unLock();
				return -1;
			}
		}
	}
	return -1;
}

static int loadContext(SSL_CTX *ctx,int ac,char *av[]){
	FILE *fp;
	CStr(fid,64);
	const char *dp;
	X509 *cert;
	EVP_PKEY *pkey;
	unsigned CStr(buf,4096);
	unsigned char *pp;
	int len;
	double start = Time();

	if( do_cache == 0 )
		return -1;
	if( (do_cache & (1 << XCTX)) == 0 )
		return -1;
	if( CFI_Lock("loadContext",0) != 0 ){
		ERROR("ERROR: locking cache to load context failed");
		return -1;
	}

	fp = CFI_fopenShared("r");
	if( fp == NULL ){
		CFI_unLock();
		return -1;
	}

	fgets(fid,sizeof(fid),fp);
	if( dp = strchr(fid,'\n') )
		truncVStr(dp);
	if( strcmp(fid,CFI_FILTER_ID()) != 0 ){
		goto CEXIT;
	}
	len = -1;
	IGNRETP fread(&len,1,sizeof(len),fp);
	if( len <= 0 || sizeof(buf) < len ){
		ERROR("loadContext len=%d",len);
		goto CEXIT;
	}
	IGNRETP fread(buf,1,len,fp);
	pp = (unsigned char*)buf;
	cert = d2i_X509(NULL,&pp,len);

	len = -1;
	IGNRETP fread(&len,1,sizeof(len),fp);
	if( len <= 0 || sizeof(buf) < len ){
		goto CEXIT;
	}
	IGNRETP fread(buf,1,len,fp);
	pp = (unsigned char*)buf;
	/* Try to load as EC key first, fall back to generic */
	pkey = d2i_PrivateKey(EVP_PKEY_EC,NULL,&pp,len);
	if( pkey == NULL ){
		pp = (unsigned char*)buf;
		pkey = d2i_PrivateKey(EVP_PKEY_RSA,NULL,&pp,len);
	}

	fclose(fp);
	CFI_unLock();

	if( SSL_CTX_use_certificate(ctx,cert) ){
		if( SSL_CTX_use_PrivateKey(ctx,pkey) ){
			if( SSL_CTX_check_private_key(ctx) ){
				if( tlsdebug & DBG_SCACHE ){
					fprintf(stderr,"[%d] %s loaded\n",
						getpid(),"CTX");
				}
				Lap("loadContext OK");
				return 0;
			}
		}
	}
	return -1;
CEXIT:
	fclose(fp);
	CFI_unLock();
	return -1;
}

typedef struct {
	int	c_size;
	int	c_nent;
	int	c_pid;
} SessionCache;

typedef struct {
 unsigned char	s_what;
 unsigned char  s_flags;
 unsigned short	s_leng;
 unsigned int	s_date;
 unsigned int	s_svaddr;	/* IPv4 addr. of the server */
 unsigned int	s_claddr;	/* IPv4 addr. of the client */
 int s_ver;
 MStr(s_sid,32);
} Session;

#define SC_MAX		32
#define SC_ESIZE	2048
#define SC_BSIZE	(SC_ESIZE-sizeof(Session))
#define SC_BASE		0x04000
#define SC_XBASE	0x10000

typedef struct {
	Session	x_sess;
 unsigned MStr(x_buff,SC_BSIZE);
} SessionCtx;

static SessionCache scache;
static Session sess_cache[SC_MAX];
static int sess_cached;
static int sess_hits;

static int loadScache(FILE *fp,int what){
	int rcc;

	scache.c_nent = -1;
	scache.c_size = -1;
	scache.c_pid = 0;

	fseek(fp,SC_BASE,0);
	rcc = fread(&scache,1,sizeof(scache),fp);

	if( rcc != sizeof(scache)
	 || scache.c_size <= 0
	 || sizeof(sess_cache) < scache.c_size
	){
		if( rcc != 0 ){
		ERROR("ERROR[%s] bad session cache size:%X/%X[%X] %X/%d/%X",
			what==XACC?"FCL":"FSV",
			scache.c_nent,scache.c_size,scache.c_pid,
			SC_BASE,rcc,ftell(fp));
		}
		return -1;
	}
	if( scache.c_pid == getpid() ){
		/* needless to reload ... */
	}
	rcc = fread(sess_cache,1,scache.c_size,fp);
	if( rcc < sizeof(Session) ){
		return -1;
	}
	if( (rcc/sizeof(Session))*sizeof(Session) != rcc ){
		return -1;
	}
	sess_cached = rcc / sizeof(Session);
	return sess_cached;
}

static void loadSessions(SSL_CTX *ctx,SSL *ssl,int what){
	FILE *fp;
	double start = Time();
	int nsess;
	int si;
	int ncon;
	int nacc;
	double Start;

	if( do_cache == 0 )
		return;
	if( (do_cache & (1 << what)) == 0 )
		return;
	if( CFI_Lock("loadSession",0) != 0 ){
		ERROR("ERROR[%s] locking cache to load session failed",
			what==XACC?"FCL":"FSV");
		return;
	}

	Start = Time();
	fp = CFI_fopenShared("r");
	if( fp == NULL ){
		return;
	}

	nacc = 0;
	ncon = 0;
	nsess = loadScache(fp,what);
	if( nsess <= 0 )
	{
		goto CEXIT;
	}

	for( si = 0; si < nsess; si++ ){
		Session *Sp;
		int cwhat;
		int len;
		int xlen;
		int rcc;
		SessionCtx scx;
		SSL_SESSION *sess;
		unsigned char *sp;
		SSL_SESSION *s;

		Sp = &sess_cache[si];
		cwhat = Sp->s_what;
		len = Sp->s_leng;
		xlen = sizeof(Session) + len;
		if( len <= 0 || sizeof(SessionCtx) < xlen ){
			ERROR("loadSession[%d] FATAL len=%X<%X %X/%X",si,
				sizeof(SessionCtx),xlen,
				Sp->s_what,Sp->s_ver);
			continue;
		}
		fseek(fp,SC_XBASE+si*SC_ESIZE,0);
		rcc = fread(&scx,1,xlen,fp);

		if( rcc != xlen ){
			continue;
		}
		if( len != scx.x_sess.s_leng ){
			continue;
		}
		if( bcmp(scx.x_sess.s_sid,Sp->s_sid,sizeof(Sp->s_sid)) != 0 ){
			continue;
		}
		sp = (unsigned char*)scx.x_buff;

		s = SSL_SESSION_new();
		sess = d2i_SSL_SESSION(&s,&sp,len);
		if( sess == 0 ){
			continue;
		}
		if( what == XCON && cwhat == XCON ){
			if( Sp->s_svaddr == sv_addr )
			if( Sp->s_claddr == cl_addr ){
				SSL_set_session(ssl,sess);
				ncon++;
				break;
			}
		}else
		if( what == XACC && cwhat == XACC ){
			if( Sp->s_svaddr == 0 || Sp->s_svaddr == sv_addr )
			if( Sp->s_claddr == cl_addr ){
				nacc++;
				SSL_CTX_add_session(ctx,sess);
			}
		}
	}

CEXIT:
	fclose(fp);
	CFI_unLock();
	if( ncon || nacc ){
		Lap("loadSession OK");
	}else{
		Lap("loadSession NONE");
	}
	ERROR("%X loadSession %.6f (%d %d) / %d",getthreadid(),
		Time()-Start,ncon,nacc,nsess);
}

int strtoHex(PCStr(str),int len,PVStr(out),int siz);
#define toHex(bi,sz,xb) strtoHex((char*)bi,sz,AVStr(xb),sizeof(xb))

static void saveSessionsA(SSL_CTX *ctx,SSL *ssl,int what);
FILE *CFI_LockFp();
static void saveSessions(SSL_CTX *ctx,SSL *ssl,int what){
	FILE *lkfp;
	if( (do_cache & (1 << what)) == 0 )
		return;
	if( lkfp = CFI_LockFp() ){
		flockfile(lkfp);
		saveSessionsA(ctx,ssl,what);
		funlockfile(lkfp);
	}else{
		saveSessionsA(ctx,ssl,what);
	}
}
static void saveSessionsA(SSL_CTX *ctx,SSL *ssl,int what){
	FILE *fp;
	SSL_SESSION *sess;
	unsigned char *sp;
	unsigned char sbuf[SC_BSIZE];
	int len;
	double start;
	int si;
	int wcc;
	int nsess;
	int nsi;
	Session *Sp;
	SessionCtx scx;
	unsigned int oldest;
	int oi;
	SessionHead *shp;
	CStr(sib,128);
	int sc = sess_cached;
	int off1;

	if( do_cache == 0 )
		return;
	if( (do_cache & (1 << what)) == 0 ){
		return;
	}

	if( CFI_Lock("saveSession",1) != 0 ){
		ERROR("ERROR[%s] locking cache to save session failed",
			what==XACC?"FCL":"FSV");
		return;
	}
	start = Time();
	fp = CFI_fopenShared("r+");
	if( fp == NULL ){
		return;
	}

	loadScache(fp,what);
	sess = SSL_get_session(ssl);
	shp = (SessionHead*)sess;
	if( sess == NULL ){
		ERROR("## no session to be saved");
		goto CEXIT;
	}
	/* Skip version 2 sessions - only TLS 1.2+ supported */
	if( shp->ssl_version == 2 ){
		DEBUG("## don't cache the session of SSL2");
		goto CEXIT;
	}

	len = i2d_SSL_SESSION(sess,NULL);
	if( len == 0 ){
		ERROR("## no session content to be saved");
		goto CEXIT;
	}
	if( sizeof(sbuf) <= len ){
		ERROR("## SESSION not saved (%d > %d)",len,
			sizeof(sbuf));
		goto CEXIT;
	}
	sp = sbuf;
	len = i2d_SSL_SESSION(sess,&sp);

	if( SC_BSIZE < len ){
		ERROR("Session not saved (DER Length: %d > %d)",len,SC_BSIZE);
		goto CEXIT;
	}

	oi = 0;
	oldest = 0xFFFFFFFF;

	if( sess_cached ){
	    for( si = 0; si < sess_cached; si++ ){
		Sp = &sess_cache[si];
		if( bcmp(shp->session_id,Sp->s_sid,shp->session_id_length)==0 ){
			if( tlsdebug & DBG_SCACHE ){
				toHex(Sp->s_sid,32,sib);
				Xstrcpy(DVStr(sib,40),"...");
				fprintf(stderr,"[%d] %s scHIT %s\n",
					getpid(),what==XACC?"ACC":"CON",sib);
			}
			DEBUG("session HIT %X/%d/%d %X/%d",
				shp->ssl_version,shp->session_id_length,len,
				Sp->s_ver,Sp->s_leng);
			sess_hits++;
			goto CEXIT;
		}
		if( sess_cache[si].s_date < oldest ){
			oldest = sess_cache[si].s_date;
			oi = si;
		}
	    }
	}

	nsess = sess_cached;
	if( nsess == elnumof(sess_cache) ){
		nsi = oi;
	}else{
		nsi = nsess++;
	}
	Sp = &sess_cache[nsi];
	Sp->s_leng = len;
	Sp->s_what = what;
	Sp->s_date = time(NULL);
	Sp->s_svaddr = sv_addr;
	Sp->s_claddr = cl_addr;
	Sp->s_ver = shp->ssl_version;
	Bcopy(shp->session_id,Sp->s_sid,shp->session_id_length);

	fseek(fp,SC_BASE,0);

off1 = SC_BASE;
if( ftell(fp) != off1 )
ERROR("saveSession[%d] FATAL-A %d %d",nsi,off1,ftell(fp));

	scache.c_nent = nsess;
	scache.c_size = nsess * sizeof(Session);
	scache.c_pid = getpid();
	fwrite(&scache,1,sizeof(scache),fp);
	fflush(fp);

off1 = SC_BASE + sizeof(scache);
if( ftell(fp) != off1 )
ERROR("saveSession[%d] FATAL-B %d %d",nsi,off1,ftell(fp));

	wcc = fwrite(sess_cache,1,scache.c_size,fp);
	fflush(fp);
off1 += scache.c_size;
if( ftell(fp) != off1 )
ERROR("saveSession[%d] FATAL-C %d %d",nsi,off1,ftell(fp));

	fseek(fp,SC_XBASE+nsi*SC_ESIZE,0);
	scx.x_sess = *Sp;
	Bcopy(sbuf,scx.x_buff,len);
	wcc = fwrite(&scx,1,sizeof(Session)+len,fp);
	fflush(fp);
off1 = SC_XBASE+nsi*SC_ESIZE + sizeof(Session)+len;
if( ftell(fp) != off1 )
ERROR("saveSession[%d] FATAL-D %d %d",nsi,off1,ftell(fp));

	fclose(fp);
	CFI_unLock();

	if( tlsdebug & DBG_SCACHE ){
		toHex((char*)shp->session_id,shp->session_id_length,sib);
		Xstrcpy(DVStr(sib,40),"...");
		fprintf(stderr,"[%d] %s scPUT %s %d/%d\n",
			getpid(),what==XACC?"ACC":"CON",sib,wcc,nsess);
	}
	Lap("saveSession OK");
	return;

CEXIT:
	fclose(fp);
	CFI_unLock();
}
int Ftruncate(FILE *fp,FileSize offset,int whence);
int file_size(int fd);
static void clearCache(SSL_CTX *ctx,SSL *ssl,int what){
	FILE *lkfp;
	FILE *fp;
	IStr(msg,1024);
	int osize ;

	if( lkfp = CFI_LockFp() ){
	    flockfile(lkfp);
	    if( CFI_Lock("clearCache",1) == 0 ){
		if( fp = CFI_fopenShared("r+") ){
			osize = file_size(fileno(fp));
			Ftruncate(fp,0,0);
			sprintf(msg,"## cleared the cache(%d) on %s error",
				osize,what==XCON?"CON":"ACC");
			ERROR("%s",msg);
			fprintf(stderr,"[%d] SSLway %s\n",getpid(),msg);
		}else{
		}
		CFI_unLock();
	    }
	    funlockfile(lkfp);
	}else{
	}
}

static int use_cert_chain(SSL_CTX *ctx,PCStr(certfile),int clnt){
	if( SSL_CTX_use_certificate_chain_file(ctx,certfile) ){
	}else{
		if( LTRACE <= loglevel )
		ERR_print_errors_fp(stderr);
		return 0;
	}
	return 1;
}
static int setcert1(SSL_CTX *ctx,PCStr(certfile),PCStr(keyfile),int clnt)
{	int code = 0;
	CStr(cwd,1024);
	CStr(xkeyfile,1024);
	CStr(xcertfile,1024);
	const char *dp;
	CStr(ykeyfile,1024);
	refQStr(yp,ykeyfile);
	CStr(passfile,1024);
	CStr(pass,128);
	int allin1 = 0;

	allin1 = streq(certfile,keyfile);
	if( LIBFILE_IS(keyfile,AVStr(xkeyfile)) )
		keyfile = xkeyfile;
	if( LIBFILE_IS(certfile,AVStr(xcertfile)) )
		certfile = xcertfile;
	if( clnt & GOTCERT ){
		if( !File_is(keyfile) && !File_is(certfile) )
			return -1;
		clnt &= GOTCERT;
	}

	pass[0] = 0;
	if( allin1 ){
		strcpy(ykeyfile,keyfile);
		if( yp = strrchr(ykeyfile,'.') ){
			strcpy(yp,"-key.pem");
			if( File_is(ykeyfile) ){
				keyfile = ykeyfile;
			}
		}
	}
	if( dp = strrchr(keyfile,'.') ){
		passfilename(keyfile,AVStr(passfile));
		if( 0 <= Freadline(passfile,AVStr(pass),sizeof(pass)) ){
			if( clnt )
				cl_pass = strdup(pass);
			else	sv_pass = strdup(pass);
		}
	}

	IGNRETS getcwd(cwd,sizeof(cwd));
	if( use_cert_chain(ctx,certfile,clnt) ){
		DEBUG("certchain loaded: %s",certfile);
	}else
	if( SSL_CTX_use_certificate_file(ctx,certfile,SSL_FILETYPE_PEM) ){
		DEBUG("certfile loaded: %s",certfile);
	}else{
		ERROR("certfile not found or wrong: %s [at %s]",certfile,cwd);
		code = -1;
	}
	/* Use generic PrivateKey loader - works for both RSA and EC keys */
	if( SSL_CTX_use_PrivateKey_file(ctx,keyfile,SSL_FILETYPE_PEM) ){
		DEBUG("keyfile loaded: %s",keyfile);
	}else{
		ERROR("keyfile not found or wrong: %s [at %s]",keyfile,cwd);
		code = -1;
	}
	if( !SSL_CTX_check_private_key(ctx) ){
		ERROR("key does not match cert: %s %s",keyfile,certfile);
		code = -1;
	}
	return code;
}

typedef struct {
	SSL_CTX *cc_ctx;
	MStr(cc_domain,128);
} CTXC;
static CTXC ctxc[1];
#define ctx2		ctxc[0].cc_ctx
#define ctx2_domain	ctxc[0].cc_domain
static SSL_CTX *ssl_newsv();
#define SSL_TLSEXT_ERR_ALERT_WARNING 1
#define SSL_TLSEXT_ERR_OK 0
#define SSL_TLSEXT_ERR_ALERT_FATAL 2
#define SSL_TLSEXT_ERR_NOACK 3
static struct {
	MStr(s_name,128);
} TlsSni;
const char *tlssni(){
	return TlsSni.s_name;
}
static int get_vhost(SSL *ssl,int *ad,void *arg){
	const char *vhost;
	IStr(certd,256);
	IStr(certf,256);
	IStr(certv,256);
	IStr(xcert,1024);

	vhost = SSL_get_servername(ssl,TLSEXT_NAMETYPE_host_name);
	TRACE("-- TLSxSNI: recv %s",vhost?vhost:"NULL");
	strcpy(TlsSni.s_name,vhost?vhost:"__none");
	if( vhost == 0 ){
		return SSL_TLSEXT_ERR_NOACK;
	}
	if( ctx2 == 0 ){
		ctx2 = ssl_newsv();
	}else
	if( ctx2_domain[0] && streq(ctx2_domain,vhost) ){
		ERROR("TLSxSNI: %s (reusing)",vhost);
		return SSL_TLSEXT_ERR_OK;
	}
	sprintf(certd,"cert/%s.pem",vhost);
	sprintf(certf,"cert_%s.pem",vhost);
	sprintf(certv,CERTF_SNI,vhost);
	if( findcert(certv,AVStr(xcert),0)
	 || LIBFILE_IS(certd,AVStr(xcert))
	 || LIBFILE_IS(certf,AVStr(xcert))
	){
		TRACE("-- TLSxSNI: %s [%s]",vhost,xcert);
		if( setcert1(ctx2,xcert,xcert,0) == 0){
			do_cache = 0;
			strcpy(ctx2_domain,vhost);
			ERROR("TLSxSNI: %s %s",vhost,xcert);
			SSL_set_SSL_CTX(ssl,ctx2);
			return SSL_TLSEXT_ERR_OK;
		}else{
		}
	}
	TRACE("-- TLSxSNI: %s NOT-FOUND",vhost);

	if( SNIopts & SNI_MANDATORY ){
		TRACE("-- TLSxSNI: %s NOT-FOUND: FATAL",vhost);
		return SSL_TLSEXT_ERR_ALERT_FATAL;
	}
	if( SNIopts & SNI_WARN ){
		TRACE("-- TLSxSNI: %s NOT-FOUND: WARN",vhost);
	return SSL_TLSEXT_ERR_ALERT_WARNING;
	}
	TRACE("-- TLSxSNI: %s NOT-FOUND: DONT-CARED",vhost);
	return SSL_TLSEXT_ERR_NOACK;
}
static int got_vhost(SSL *ssl,int *ad,void *arg){
	const char *vhost;
	int type;
	int reu;
	vhost = SSL_get_servername(ssl,TLSEXT_NAMETYPE_host_name);
	type = SSL_get_servername_type(ssl);
	reu = SSL_session_reused(ssl);
	if( type != -1 ){
		ERROR("-- TLSxSNI: sent ru=%d ty=%d nm=%s",reu,
			type,vhost?vhost:"");
		do_cache = 0;
	}
	return SSL_TLSEXT_ERR_OK;
}
static void set_vhost(SSL *conSSL,SslEnv *env){
	const char *vhost;
	if( (vhost = getv(env->se_av,"SNIHOST"))
	 || (vhost = getenv("SERVER_HOST"))
	 || (vhost = getenv("SERVER_NAME"))
	){
		TRACE("-- TLSxSNI: send %s",vhost);
		SSL_set_tlsext_host_name(conSSL,vhost);
	}
}
int VSA_gethostname(int sock,PVStr(addr));
static void set_ifcert(SSL_CTX *ctx,int sock,int clnt){
	IStr(addr,128);
	IStr(nif,256);
	IStr(sva,256);
	IStr(path,256);

	if( 0 <= VSA_gethostname(sock,AVStr(addr)) ){
		sprintf(nif,CERTF_NIF,addr);
		if( clnt )
			sprintf(sva,CERTF_CLA,addr);
		else	sprintf(sva,CERTF_SVA,addr);
		DEBUG("-- net-if cert [%s] or [%s]",sva,nif);
		if( findcert(sva,AVStr(path),0)
		 || findcert(nif,AVStr(path),0)
		){
			DEBUG("-- net-if cert found [%s]",path);
			setcert1(ctx,path,path,clnt);
		}
	}
}
static int ssl_dfltCAs(SSL_CTX *ctx,int clnt){
	IStr(file,1024);
	IStr(cdir,1024);
	const char *pem;
	const char *dir;
	int vflags = 1;
	const char *ppem = 0;
	const char *pdir = 0;

	if( clnt ){
		dir = CERTD_CLCA;
		pem = CERTF_CLCA;
	}else{
		dir = CERTD_SVCA;
		pem = CERTF_SVCA;
	}

	if( findcert(pem,AVStr(file),0    ) ) ppem = file;
	if( findcert(dir,AVStr(cdir),ISDIR) ) pdir = cdir;
	if( ppem == 0 && pdir == 0 ){
		return 0;
	}
	ssl_setCAs(ctx,ppem,pdir);

	vflags = SSL_VERIFY_PEER
	       | SSL_VERIFY_CLIENT_ONCE
	       | SSL_VERIFY_FAIL_IF_NO_PEER_CERT;
	if( clnt )
		cl_vrfy = vflags;
	else	sv_vrfy = vflags;
	verify_depth = -1;
	return 1;
}

static int cert_opts;
static const char *dflt_cert;
static const char *dflt_vkey;
void sslway_dflt_certkey(PCStr(cert),PCStr(vkey)){
	dflt_cert = cert;
	dflt_vkey = vkey;
}
int set_dfltcerts(SSL_CTX *ctx){
	X509 *cert;
	EVP_PKEY *pkey;
	CStr(file,128);
	int ok;
	BIO *Bp;

	if( dflt_cert == 0 || dflt_vkey == 0 )
		return -1;

	Bp = BIO_new(BIO_s_mem());
	BIO_puts(Bp,(char*)dflt_vkey);
	pkey = NULL;
	PEM_read_bio_PrivateKey(Bp,&pkey,NULL,NULL);
	ok = SSL_CTX_use_PrivateKey(ctx,pkey);
	if( !ok ){
		ERROR("-- pkey=%X %d",pkey,ok);
	}

	BIO_puts(Bp,(char*)dflt_cert);
	cert = NULL;
	PEM_read_bio_X509(Bp,&cert,NULL,NULL);
	ok = SSL_CTX_use_certificate(ctx,cert);
	if( !ok ){
		ERROR("-- cert=%X %d",cert,ok);
	}

	if( SSL_CTX_check_private_key(ctx) ){
		ERROR("-- Using Default Certificate");
		if( tlsdebug & DBG_XCACHE ){
			fprintf(stderr,"[%d] %s using default\n",
				getpid(),"CTX");
		}
		return 0;
	}else{
		return -1;
	}
}

static int setcerts(SSL_CTX *ctx,CertKeyV *certv,int clnt)
{	int certx;
	int code;
	CertKey1 *cert1;

	IStr(path,1024);
	if( findcert("dhparam.pem",AVStr(path),0)
	 || findcert("dhparam.der",AVStr(path),0)
	){
		BIO *Bp;
		DH *dh;
		DEBUG("-- loading DH PARAMS: %s",path);
		if( Bp = BIO_new_file(path,"r") ){
			if( dh = PEM_read_bio_DHparams(Bp,NULL,NULL,NULL) ){
				SSL_CTX_set_tmp_dh(ctx,dh);
				DH_free(dh);
				TRACE("-- loaded DH PARAMS: %s",path);
			}
			BIO_free(Bp);
		}
	}

	if( getcertdflt(ctx,clnt) ){
		clnt |= GOTCERT;
		VDEBUG("--CERTS setcerts clnt=%d ...",clnt);
	}

	for( certx = 0; certx <= certv->v_Ncert; certx++ ){
		cert1 = &certv->v_ck[certx];
		code = setcert1(ctx,cert1->c_cert,cert1->c_key,clnt);
		if( code != 0 )
		{
			if( clnt & GOTCERT ){
				return 0;
			}
			if( cert_opts == 0 ){
				return set_dfltcerts(ctx);
			}
			if( SSL_fatalCB ){
				(*SSL_fatalCB)("bad cert/key: [%s][%s]\n",
					cert1->c_cert,cert1->c_key);
			}
			return code;
		}
	}
	return 0;
}

/* No tmp RSA callback needed for TLS 1.2+/ECDHE - removed tmprsa_callback */

static int verify_callback(int ok,X509_STORE_CTX *ctx)
{	int err,depth;
	const char *errsym;
	X509 *cert;
	CStr(subjb,256);

	cert =   X509_STORE_CTX_get_current_cert(ctx);
	err =    X509_STORE_CTX_get_error(ctx);
	depth =  X509_STORE_CTX_get_error_depth(ctx);
	X509_NAME_oneline(X509_get_subject_name(cert),subjb,sizeof(subjb));
	errsym = X509_verify_cert_error_string(err);
	ERROR("depth=%d/%d ok=%d %d:\"%s\" %s",
		depth,verify_depth,ok,err,errsym,subjb);

	if( !ok ){
		if( depth <= verify_depth )
			ok = 1;
	}
	return ok;
}

#define SSL_ERROR_WANT_READ        2
#define SSL_ERROR_WANT_WRITE       3
#define SSL_ERROR_WANT_X509_LOOKUP 4

static int SSL_rdwr(int wr,SSL *ssl,void *buf,int siz)
{	int wcc;
	int err;
	int xi;

	wcc = wr ? SSL_write(ssl,buf,siz) : SSL_read(ssl,buf,siz);
	if( 0 < wcc ){
		return wcc;
	}
	err = SSL_get_error(ssl,wcc);
	if( err == SSL_ERROR_WANT_READ || err == SSL_ERROR_WANT_WRITE ){
		int fds[2];
		int nready;
		fds[0] = -1;
		fds[1] = -1;
		/*
		nready = PollIn(100,2,fds);
		*/
	}

	wcc = wr ? SSL_write(ssl,buf,siz) : SSL_read(ssl,buf,siz);
	if( 0 < wcc ){
		return wcc;
	}
	return wcc;
}
static int SSL_Wwrite(SSL *ssl,void *buf,int siz){
	return SSL_rdwr(1,ssl,buf,siz);
}
static int SSL_Wread(SSL *ssl,void *buf,int siz){
	return SSL_rdwr(0,ssl,buf,siz);
}

/* Dynamic loading implementation for Debian Bookworm/Trixie */
#ifdef ISDLIB /*{*/
int dl_library(const char *libname,DLMap *dlmap,const char *mode);
int dl_isstab(void *func);
static int with_dl;
int sslway_dl_reset(){
	int owd = with_dl;
	with_dl = 0;
	return owd;
}

static int sslway_dl0(){
	if( with_dl ){
		if( 0 < with_dl )
			return 1;
		else	return 0;
	}
	if( SSLLIBS ){
		CStr(lib1,1024);
		const char *dp;
		char del = '+';
		for( dp = SSLLIBS; *dp; ){
			dp = scan_ListElem1(dp,del,AVStr(lib1));
			if( *lib1 == 0 )
				break;
			if( lDYLIB() )
				syslog_ERROR("TLSCONF=libs:%s\n",lib1);
			if( streq(lib1,"NOMORE") ){
				with_dl = -1;
				return 0;
			}
			if( dl_library(lib1,dlmap_ssl,"") == 0 ){
				with_dl = 1;
				return 1;
			}
		}
	}
	if( !isWindows() ){
		/* Debian Bookworm/Trixie: OpenSSL 3.x
		 * Try specific version first, then generic names
		 * libcrypto should be loaded prior to libssl
		 */
		/* Try OpenSSL 3.x first (Debian Bookworm/Trixie) */
		if( dl_library("crypto.so.3",dlmap_ssl,"") == 0
		 || dl_library("ssl.so.3",dlmap_ssl,"") == 0
		){
			with_dl = 1;
			return 1;
		}
		/* Try common paths for Debian */
		if( dl_library("/usr/lib/x86_64-linux-gnu/libcrypto.so.3",dlmap_ssl,"") == 0
		 || dl_library("/usr/lib/x86_64-linux-gnu/libssl.so.3",dlmap_ssl,"") == 0
		){
			with_dl = 1;
			return 1;
		}
		/* Try generic names as fallback */
		if( dl_library("crypto",dlmap_ssl,"") == 0
		 || dl_library("ssl",dlmap_ssl,"") == 0
		){
			with_dl = 1;
			return 1;
		}
	}
	{
		with_dl = -1;
		if( !lISCHILD() ){
			putDylibError();
		}
		return 0;
	}
}
int sslway_dl(){
	int ok;
	if( with_dl ){
		return sslway_dl0();
	}else
	if( ok = sslway_dl0() ){
		InitLog("+++ loaded %s\n",OpenSSL_version(OPENSSL_VERSION));
		if( lDYLIB() )
		printf("+++ loaded %s\n",OpenSSL_version(OPENSSL_VERSION));
		return ok;
	}else{
		return 0;
	}
}
const char *SSLVersion(){
	if( with_dl == 0 )
		return "Not Yet";
	if( with_dl < 0 )
		return "None";
	return OpenSSL_version(OPENSSL_VERSION);
}
int putSSLverX(FILE *fp,PCStr(fmt)){
	if( with_dl <= 0 )
		return 0;
	fprintf(fp,"%s",OpenSSL_version(OPENSSL_VERSION));
	return 1;
}
void putSSLver(FILE *fp){
	if( 0 < with_dl )
		fprintf(fp,"Loaded: %s\r\n",OpenSSL_version(OPENSSL_VERSION));
}

int sslway_main(int ac,const char *av[])
{
	SSLwayCTX ScBuf,*Sc = &ScBuf;
	initSSLwayCTX(Sc);

	if( sslway_dl() == 0 ){
		fprintf(stderr,"Can't link the SSL library.\n");
		return -1;
	}
	Builtin = 1;
	return sslway_mainX(Sc,ac,(char**)av,0,1,0);
}
int sslwayFilter(SSLwayCTX *Sc,int ac,char *av[],FILE *in,FILE *out,int internal){
	if( sslway_dl() == 0 ){
		return 0;
	}
	Builtin = 1;
	if( in == NULL )
		sslway_mainX(Sc,ac,av,-1,-1,1);
	else	sslway_mainX(Sc,ac,av,fileno(in),fileno(out),1);
	return 1;
}
int sslwayFilterX(SSLwayCTX *Sc,int ac,char *av[],int clnt,int serv,int internal){
	if( sslway_dl() == 0 ){
		return 0;
	}
	Builtin = 1;
	if( clnt < 0 )
		sslway_mainX(Sc,ac,av,-1,-1,1);
	else	sslway_mainX(Sc,ac,av,clnt,serv,1);
	return 1;
}


static const char *RINFO  = "////ECDSA -.- ////";
static const char *ROK    = "////ECDSA ^_^ //// OK";
static const char *RERROR = "////ECDSA -\"- //// ERROR";

int getpass1(FILE *in,FILE *out,PVStr(pass),PCStr(xpass),PCStr(echoch));
static int getpass2(FILE *in,FILE *out,PVStr(pass1),PVStr(pass2),PCStr(echoch)){
	fprintf(out,"%s enter PEM pass phrase> ",RINFO);
	getpass1(in,out,BVStr(pass1),0,echoch);
	fprintf(out,"\r\n");
	if( pass2 == 0 ){
		return 0;
	}
	fprintf(out,"%s enter again to verify> ",RINFO);
	getpass1(in,out,BVStr(pass2),pass1,echoch);
	fprintf(out,"\r\n");
	if( streq(pass1,pass2) ){
		return 0;
	}
	fprintf(stderr,"%s not match\r\n",RERROR);
	return -1;
}

enum _ECF {
	EC_VERBOSE   = 0x0001,
	EC_PRINTPUB  = 0x0002,
	EC_PRINTPRI  = 0x0004,
	EC_NOPASS    = 0x0010,
	EC_NEWKEY    = 0x0100,
	EC_CHPASS    = 0x0200,
	EC_SIGN      = 0x0400,
	EC_VRFY      = 0x0800,
	EC_ENC       = 0x1000,
	EC_DEC       = 0x2000,
	EC_PRV_KEY   = 0x4000,
} ECF;
typedef struct _ECCtx {
	int	ec_flags;
	EVP_PKEY *ec_pkey;
	MStr(	ec_curve,64);      /* curve name, e.g., "prime256v1" */
	MStr(	ec_passb,64);
	char   *ec_pass;
	int	ec_plen;
	MStr(	ec_file,256);
	int	ec_intype;
	MStr(	ec_indata,512);
	FILE   *ec_pem;
    EVP_CIPHER *ec_cipher;
} ECCtx;
#define ExFlags	Ec->ec_flags

int _EC_init(ECCtx *Ec){
	if( sslway_dl() == 0 ){
		fprintf(stderr,"%s no SSL library\r\n",RERROR);
		return -1;
	}
	ERR_load_crypto_strings();
	OPENSSL_add_all_algorithms_conf();

	bzero(Ec,sizeof(ECCtx));
	strcpy(Ec->ec_curve,"prime256v1");  /* P-256, good default */
	sprintf(Ec->ec_file,"/tmp/ec.pem");
	return 0;
}
ECCtx *_EC_new(){
	ECCtx *Ec;
	Ec = (ECCtx*)malloc(sizeof(ECCtx));
	bzero(Ec,sizeof(ECCtx));
	_EC_init(Ec);
	return Ec;
}
int _EC_free(ECCtx *Ec){
	if( Ec->ec_pkey ){
		EVP_PKEY_free(Ec->ec_pkey);
	}
	free(Ec);
	return 0;
}
int _EC_setpass(ECCtx *Ec){
	IStr(pass1,64);
	IStr(pass2,64);

	getpass2(stdin,stderr,AVStr(pass1),AVStr(pass2),"*");
	if( !streq(pass1,pass2) ){
		fprintf(stderr,"%s pass mismatch\r\n",RERROR);
		return -1;
	}
	strcpy(Ec->ec_passb,pass1);
	Ec->ec_pass = Ec->ec_passb;
	if( pass1[0] == 0 ){
		Ec->ec_plen = 1;
	}else{
		Ec->ec_plen = strlen(pass1);
	}
	bzero(pass1,sizeof(pass1));
	bzero(pass2,sizeof(pass2));
	return 0;
}
static int ec_passwd_cb(char buf[],int size,int rwflag,void *vEc){
	ECCtx *Ec = (ECCtx*)vEc;

	fprintf(stderr,"%s enter PEM pass phrase> ",RINFO);
	buf[0] = 0;
	getpass1(stdin,stdout,ZVStr(buf,size),0,"*");
	fprintf(stdout,"\r\n");
	if( buf[0] == 0 ){
		return 1;
	}else{
		return strlen(buf);
	}
}

int _EC_perror(ECCtx *Ec,int rcode){
	int serr;
	IStr(reason,256);

	serr = ERR_get_error();
	if( serr ){
		ERR_error_string_n(serr,(char*)reason,sizeof(reason));
		ERR_print_errors_fp(stderr);
		fprintf(stderr,"%s rcode=%d err=%d {%s}\n",RINFO,rcode,serr,reason);
		return 1;
	}
	return 0;
}

int _EC_output(ECCtx *Ec,EVP_PKEY *pkey,FILE *pem){
	int rcode = 0;
	EVP_CIPHER *cipher = NULL;

	if( !(ExFlags & EC_NOPASS) ){
		if( Ec->ec_pass == 0 ){
			if( _EC_setpass(Ec) != 0 ){
				return -1;
			}
		}
		/* For encrypted output, would need to get cipher */
		/* cipher = EVP_aes_256_cbc(); -- but we'll skip encryption for simplicity */
	}

	rcode = PEM_write_PrivateKey(pem, pkey, cipher,
		(unsigned char*)Ec->ec_pass, Ec->ec_plen, NULL, 0);
	bzero(Ec->ec_passb,sizeof(Ec->ec_passb));
	fflush(pem);

	if( rcode ){
		rcode = PEM_write_PUBKEY(pem, pkey);
	}
	return rcode > 0 ? 0 : -1;
}

int _EC_showpem(ECCtx *Ec,FILE *pem){
	int off;

	off = ftell(pem);
	fseek(pem,0,0);
	copyfile1(pem,stdout);
	fseek(pem,off,0);
	return 0;
}

int _EC_newkey(ECCtx *Ec){
	EVP_PKEY *pkey;
	int rcode = 0;
	FILE *pem;
	IStr(path,256);
	int eout;

	strcpy(path,Ec->ec_file);
	if( File_is(path) ){
		strcat(path,"#");
	}
	pem = fopen(path,"w+");
	if( pem == 0 ){
		fprintf(stderr,"%s cannot open: %s\n",RERROR,path);
		return -1;
	}
	if( ExFlags & EC_VERBOSE ){
		fprintf(stderr,"generating ECDSA key (%s): ",Ec->ec_curve);
	}

	/* Generate EC key using OpenSSL 3.x EVP API */
	pkey = EVP_EC_gen(Ec->ec_curve);
	if( pkey == 0 ){
		fprintf(stderr," %s EVP_EC_gen() FAILED\r\n",RERROR);
		fclose(pem);
		return -1;
	}
	if( ExFlags & EC_VERBOSE ){
		fprintf(stderr," %s\r\n",ROK);
	}
	eout = _EC_output(Ec,pkey,pem) < 0;
	_EC_perror(Ec,rcode);

	EVP_PKEY_free(pkey);
	fflush(pem);
	Ftruncate(pem,0,1);
	_EC_showpem(Ec,pem);
	fclose(pem);

	if( !streq(path,Ec->ec_file) ){
		fprintf(stderr,"%s updated %s\r\n",ROK,Ec->ec_file);
		rename(path,Ec->ec_file);
	}
	return 0;
}

static int _EC_loadkey(ECCtx *Ec,int whkey){
	FILE *pem;
	EVP_PKEY *pkey = 0;

	if( Ec->ec_pkey != 0 ){
		return 1;
	}
	pem = fopen(Ec->ec_file,"r");
	if( pem == 0 ){
		fprintf(stderr,"%s cannot open %s\r\n",RERROR,Ec->ec_file);
		return -1;
	}
	pkey = PEM_read_PrivateKey(pem,&pkey,ec_passwd_cb,Ec);
	if( pkey != NULL ){
		Ec->ec_flags |= EC_PRV_KEY;
	}
	_EC_perror(Ec,0);
	fclose(pem);

	if( pkey == 0 ){
		return -1;
	}
	Ec->ec_pkey = pkey;
	return 0;
}

int _EC_sign(ECCtx *Ec,PCStr(data),int dlen,PVStr(sig),size_t *slen){
	int ok;

	if( _EC_loadkey(Ec,1) < 0 ){
		return -1;
	}
	ok = signECDSA(Ec->ec_pkey,data,dlen,BVStr(sig),slen);
	_EC_perror(Ec,0);
	if( ok ){
		return 0;
	}
	return -1;
}

int _EC_verify(ECCtx *Ec,PCStr(data),int dlen,PCStr(sig),size_t slen){
	int ok;

	if( _EC_loadkey(Ec,2) < 0 ){
		return -1;
	}
	ok = verifyECDSA(Ec->ec_pkey,data,dlen,sig,slen);
	_EC_perror(Ec,0);
	if( ok ){
		return 0;
	}
	return -1;
}

int _EC_avail(ECCtx *Ec){
	if( Ec->ec_curve[0] == 0 ){
		return 0;
	}
	if( _EC_loadkey(Ec,1) < 0 ){
		return 0;
	}
	return 1;
}

int ec_main(int ac,const char *av[]){
	int ai;
	const char *a1;
	ECCtx EcBuf,*Ec = &EcBuf;

	_EC_init(Ec);
	for( ai = 1; ai < ac; ai++ ){
		a1 = av[ai];
		if( *a1 == '-' ){
		  switch( a1[1] ){
		    case 'v': ExFlags |= EC_VERBOSE; break;
		    case 'n':
			if( streq(a1,"-nopass") ){
				ExFlags |= EC_NOPASS;
			}
		    default:
			break;
		    case 'f':
			if( ai+1 < ac ){
				strcpy(Ec->ec_file,av[++ai]);
			}
			break;
		    case 'c':
			if( ai+1 < ac ){
				strcpy(Ec->ec_curve,av[++ai]);
			}
			break;
		    case 'i':
			if( ai+1 < ac ){
				strcpy(Ec->ec_indata,av[++ai]);
			}
			break;
		  }
		}else{
			if( streq(a1,"new") ){
				ExFlags |= EC_NEWKEY;
			}else
			if( streq(a1,"chpass") ){
				ExFlags |= EC_CHPASS;
			}else
			if( streq(a1,"sign") ){
				ExFlags |= EC_SIGN;
			}else
			if( streq(a1,"verify") ){
				ExFlags |= EC_VRFY;
			}else{
				/* Set curve name if recognized */
				if( streq(a1,"prime256v1") || streq(a1,"P-256") ){
					strcpy(Ec->ec_curve,"prime256v1");
				}else if( streq(a1,"secp384r1") || streq(a1,"P-384") ){
					strcpy(Ec->ec_curve,"secp384r1");
				}else if( streq(a1,"secp521r1") || streq(a1,"P-521") ){
					strcpy(Ec->ec_curve,"secp521r1");
				}
			}
		}
	}
	if( ExFlags & EC_NEWKEY ){
		_EC_newkey(Ec);
	}

	if( ExFlags & EC_SIGN ){
		size_t slen;
		int rcode;
		IStr(sig,512);
		IStr(xsig,1024);

		slen = sizeof(sig);
		rcode = _EC_sign(Ec,"ABCD",4,AVStr(sig),&slen);
		if( rcode == 0 ){
			strtoHex(sig,slen,AVStr(xsig),sizeof(xsig));
			rcode = _EC_verify(Ec,"ABCD",4,sig,slen);
			fprintf(stdout,"ABCD -> %s -> %d\n",xsig,rcode);
		}
	}
	if( ExFlags & EC_VRFY ){
	}
	return 0;
}

#else /*}{*/
int (*DELEGATE_MAIN)(int ac,const char *av[]);
void (*DELEGATE_TERMINATE)();
extern int RANDSTACK_RANGE;
int main(int ac,char *av[])
{
	randtext(-1);
	RANDSTACK_RANGE = 256;
	av = move_envarg(ac,(const char**)av,NULL,NULL,NULL);
	return randstack_call(1,(iFUNCP)sslway_mainX,ac,av,0,1,0);
}
int sslway_dl(){
	return 1;
}
#endif /*}*/

/* Additional essential functions */

static int writes(PCStr(what),SSL *ssl,int confd,void *buf,int rcc)
{	int wcc = -9;
	int rem;

	rem = rcc;
	while( 0 < rem ){
		if( ssl )
			wcc = SSL_write(ssl,buf,rem);
		else	wcc = write(confd,buf,rem);
		if( wcc == rem )
			DEBUG("%s: %d/%d -> %d%s",what,rem,rcc,wcc,ssl?"/SSL":"");
		else	ERROR("%s? %d/%d -> %d%s",what,rem,rcc,wcc,ssl?"/SSL":"");
		if( wcc <= 0 )
			break;
		rem -= wcc;
	}
	return rem;
}

static void ssl_relay(SSLwayCTX *Sc,SSL *accSSL,int accfd,SSL *conSSL,int confd)
{	int fdv[2],rfdv[2],nready,rcc,wcc;
	CStr(buf,8*1024);
	int relays = 0;
	int rem;
	int acnt = 0,ccnt = 0;
	int alen = 0,clen = 0;
	const char *ecase = "";

	fdv[0] = accfd;
	fdv[1] = confd;

	for(;;){
		if( gotsigTERM("SSLway relayA") ){
			if( numthreads() && !ismainthread() ){
				thread_exit(0);
			}
			break;
		}
		relays++;
		nready = 0;
		rfdv[0] = rfdv[1] = 0;
		if( accSSL && SSL_pending(accSSL) ){
			rfdv[0] = 1;
			nready++;
		}
		if( conSSL && SSL_pending(conSSL) ){
			rfdv[1] = 1;
			nready++;
		}
		if( nready == 0 ){
			nready = PollIns(0,2,fdv,rfdv);
			if( gotsigTERM("SSLway relayB") ){
				if( numthreads() && !ismainthread() ){
					thread_exit(0);
				}
				break;
			}
			if( nready <= 0 )
			{
				ecase = "Non-Ready";
				break;
			}
		}

		rem = 0;
		if( rfdv[0] ){
			if( accSSL )
				rcc = SSL_read(accSSL,buf,sizeof(buf));
			else	rcc = read(accfd,buf,sizeof(buf));
			if( rcc <= 0 )
			{
				TRACE("C-S EOF from the client");
				ecase = "CS-EOS";
				break;
			}
			alen += rcc;
			acnt++;
			rem +=
			writes("C-S",conSSL,confd,buf,rcc);
		}
		if( rfdv[1] ){
			if( conSSL )
				rcc = SSL_read(conSSL,buf,sizeof(buf));
			else	rcc = read(confd,buf,sizeof(buf));
			if( rcc <= 0 )
			{
				TRACE("S-C EOF from the server");
				ecase = "SC-EOS";
				break;
			}
			clen += rcc;
			ccnt++;
			rem +=
			writes("S-C",accSSL,accfd,buf,rcc);
		}
		if( rem != 0 ){
			ecase = "Write-Error";
			break;
		}
	}
	ERROR("%s S-C:%d/%d C-S:%d/%d %s",
		accSSL?"FCL":"FSV",clen,ccnt,alen,acnt,ecase);
}

static SSL_CTX *ssl_newsv(){
	return ssl_new(1);
}

static void doShutdown(int what,SSL *ssl,int fd){
	int sd;
	int opts = SSLopts[what];
	int wms = SHUTwait[what];

	if( (opts & OPT_SHUT_SEND) == 0 ){
		return;
	}
	sd = SSL_get_shutdown(ssl);
	if( sd & SSL_RECEIVED_SHUTDOWN ){
		SSL_shutdown(ssl);
	}else{
		if( opts & OPT_SHUT_WAIT ){
			int rfdv[2] = {0,0};
			int fdv[2];
			fdv[0] = fd;
			fdv[1] = -1;
			SSL_shutdown(ssl);
			PollIns(wms,1,fdv,rfdv);
			if( rfdv[0] ){
				SSL_shutdown(ssl);
			}
		}else{
			SSL_shutdown(ssl);
		}
	}
}

/* Stub functions for compatibility */
static int nego_FTPDATAsv(SSL *accSSL,char buf[],int len){ return len; }
static void nego_FTPDATAcl(SSL *conSSL,const char sbuf[],int len){}
int numthreads(){ return 0; }
int ismainthread(){ return 1; }
void thread_exit(int code){ exit(code); }
int gotsigTERM(PCStr(wh)){ return 0; }
const char *getv(const char **av,PCStr(name)){ return getenv(name); }