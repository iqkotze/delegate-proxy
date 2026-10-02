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
Program:	nonwin.c
Author:		Yutaka Sato <y.sato@delegate.org>
Description:	Stubs for functions that are implemented only on Windows.
//////////////////////////////////////////////////////////////////////#*/

#include "ystring.h"
#include "fpoll.h"
#include "log.h"

int RunningAsService;

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
int NTHT_connect(int toproxy,int tosv,int fromsv,PCStr(reql),PCStr(head),PCStr(user),PCStr(pass),void *utoken,PCStr(chal)){
	return -1;
}
int NTHT_accept(int asproxy,int tocl,int fromcl,PCStr(reql),PCStr(head),PVStr(user),void **utoken){
	return -1;
}
