const char *SIGN_wince_c="{FILESIGN=wince.c:20140818123721+0900:c9836a29e5bbcc08:Author@DeleGate.ORG:vpa4ShC7oeVWyJF7z1vV1DSWCiSvDdVVKr3a01kaEdbwAScaBgNlk6NqfF0SDAXKmpnVfy+oyv6y4kaEQLpZFrAueWidleKeHD+5nN3wOJ1c3sQlJx9343veAO1aYN4Vpgsx8s0RGS5Yl6JM1nKHvAzgejJgt5BE8h6t0LJETiE=}";

/*////////////////////////////////////////////////////////////////////////
Copyright (c) 2007-2008 National Institute of Advanced Industrial Science and Technology (AIST)
AIST-Product-ID: 2000-ETL-198715-01, H14PRO-049, H15PRO-165, H18PRO-443

Permission to use this material for noncommercial and/or evaluation
purpose, copy this material for your own use,
without fee, is hereby granted
provided that the above copyright notice and this permission notice
appear in all copies.
AIST MAKES NO REPRESENTATIONS ABOUT THE ACCURACY OR SUITABILITY OF THIS
MATERIAL FOR ANY PURPOSE.  IT IS PROVIDED "AS IS", WITHOUT ANY EXPRESS
OR IMPLIED WARRANTIES.
//////////////////////////////////////////////////////////////////////////
Content-Type:	program/C; charset=US-ASCII
Program:	wince.c (for Windows CE)
Author:		Yutaka Sato <y.sato@delegate.org>
Description:
History:
	071117	created
//////////////////////////////////////////////////////////////////////#*/
/* '"DIGEST-OFF"' */

#if defined(_MSC_VER) && !defined(UNDER_CE) /*#################*/
#define _WINSOCKAPI_ /* Prevent inclusion of winsock.h in windows.h */
#define UNICODE
#include <WINDOWS.H>
#include <WINBASE.H>
#include "vsocket.h"
#include "config.h"
#include "ystring.h"
#include "file.h"
#include "log.h"
#endif

#ifndef UNDER_CE /*{*/
#include "ystring.h"

#ifndef _MSC_VER /*{*/
int FMT_putInitlog(const char *fmt,...){
	return -1;
}
int dumpScreen(FILE *fp){
	fprintf(fp,"Screen dump not supported\n");
	return -1;
}
const char *ControlPanelText(){
	return "";
}
#endif /*}*/

int unamef(PVStr(uname),PCStr(fmt)){
	return -1;
}
int setNonblockingFpTimeout(FILE *fp,int toms){
	return -1;
}
char *printnetif(PVStr(netif)){
	strcpy(netif,"127.0.0.1 192.168.1.2 192.168.0.2");
	return (char*)netif;
}
int setosf_FL(const char *wh,const char *path,int fd,FILE *fp,const char *F,int L){
	return -1;
}
#endif /*}*/

