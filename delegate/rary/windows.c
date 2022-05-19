const char *SIGN_windows_c="{FILESIGN=windows.c:20140818123721+0900:c5a67b9e116098f1:Author@DeleGate.ORG:W7gltYSi8AprT3ukqd1XjGnze5Wc4NaP7ZEEUZ+NUOwtLvDt3sYO0M+yUBRmDbpNvrDL2cbJ5c039iVrOOFfkt7JyfGiuR/BziYU3r25H/ztThmFbrxpCfVj4Gg/P3pCH7htr2/lUksWQjdKbVOF3PZM/icq4jlew2myhBclERI=}";

/*////////////////////////////////////////////////////////////////////////
Copyright (c) 2007-2008 National Institute of Advanced Industrial Science and Technology (AIST)
AIST-Product-ID: H18PRO-443

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
Program:	windows.c
Author:		Yutaka Sato <y.sato@delegate.org>
Description:
	A collection of functions to make DeleGate work on Windows.
History:
	970202	created
TODO:
	to be LIBDGWIN.DLL
//////////////////////////////////////////////////////////////////////#*/
/* '"DIGEST-OFF"' */

int win_simple_send;
int RunningAsService;

