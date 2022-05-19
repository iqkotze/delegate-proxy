const char *SIGN_spinach="{FILESIGN=spinach.c:20140713054334+0900:36ed00aa6c272f64:Author@DeleGate.ORG:lM1CDVMx6Ei6eix40rJoInV68jxIxPejgjqDx3gLscC8tYt8YmFfMN2s93E/sq9SAoN0wXbNEoz09/J+z8F645Kfk3FfsEj/9hL5lqeZfKkLEMlE6oK738ylZXEkC5m3xdnbhzUYqT70je7eUJeqDnDqGTID+BnQJI2H+gXNUe4=}";
/*////////////////////////////////////////////////////////////////////////
Copyright (c) 2009 National Institute of Advanced Industrial Science and Technology (AIST)
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
Program:	spinach.c
Author:		Yutaka Sato <y.sato@delegate.org>
Description:
	A candidate of the kernel of DeleGate/10.X :)
	to replace SockMux, THRUWAY, VSAP, Coupler, relaysx(),
	Udpalrey, Tcprelay, Shio, ..., and HTTP, SOCKS, ...

History:
	090204	created
//////////////////////////////////////////////////////////////////////#*/

#include <ctype.h>
#include "vsocket.h"
#include "vsignal.h"
#include "delegate.h"
#include "fpoll.h"

/* should use va_list */
#ifdef daVARGS
#undef VARGS         
#define VARGS daVARGS
#define LINESIZE 4*1024       
#endif

#define TY_HTTP_REQ	1
#define TY_HTTP_RESP	2
#define TY_SOCKS_REQ	3
#define TY_SOCKS_RESP	4
#define ST_ZOMB		0x00000001
#define ST_IN_ACCEPT	0x00000002 /* for each entrance -Pport */
#define ST_IN_RESOLV	0x00000004
#define ST_IN_CONNECT	0x00000008
#define ST_IN_BIND	0x00000010
#define ST_IN_ACCTL	0x00000020
#define ST_IN_INPUT	0x00000040
#define ST_IN_OUTPUT	0x00000080

int eccLOGX_appReq = 0;
int eccLOGX_tcpCon = 0;
int eccLOGX_tcpAcc = 0;
int eccTOTAL_SERVED = 0;
int eccActivity = 0;

#ifndef SHUT_WR
#define SHUT_WR		SD_SEND /* 0 or 1 ? */
#define SHUT_RDWR	SD_BOTH /* 2 */
#endif
int ShutdownSocketRDWR(int fd){
	return shutdown(fd,SHUT_RDWR);
}
int shutdownWR(int fd){
	send(fd,"",0,0); // try pushing EoS ?
	return shutdown(fd,SHUT_WR);
}

/* '"DIGEST-OFF"' */
