const char *SIGN_winssl_c="{FILESIGN=winsspi.c:20140807205139+0900:ba993d4f23c57a4b:Author@DeleGate.ORG:PXLDPNMUjymVcIjrCG2aGTq6GBeOHBzegcY2euwqUIJ9hYOlS+p0/INjQvmaIYqeWKZf8Fg+/nvLxudp5R5vyryUrYsUYstalMN1dUpMYUEY7FfWq+EzGV3G8r4PxBR2RWaIkCEn7dLZhFalY44Q3Ejc00FRc2qBSvWYtg+Shew=}";

/*////////////////////////////////////////////////////////////////////////
Copyright (c) 2008 National Institute of Advanced Industrial Science and Technology (AIST)
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
Program:	winsspi.c (Security Support Providers Interface on Windows)
Author:		Yutaka Sato <y.sato@delegate.org>
Description:
	- SSL gateway
	- {NTLM/Negotiate}/Baisc authentication gateway
          [MS-NTHT] http://msdn.microsoft.com/en-us/library/cc237488.aspx
	  [RFC4559] ftp://ftp.rfc-editor.org/in-notes/rfc4559.txt
History:
	080624	created
//////////////////////////////////////////////////////////////////////#*/
/* '"DIGEST-OFF"' */

#include "ystring.h"
#include "fpoll.h"
#include "log.h"
#if !defined(_MSC_VER) || _MSC_VER < 1400 || defined(UNDER_CE)
int NTHT_connect(int toproxy,int tosv,int fromsv,PCStr(reql),PCStr(head),PCStr(user),PCStr(pass),void *utoken,PCStr(chal)){
	return -1;
}
int NTHT_accept(int asproxy,int tocl,int fromcl,PCStr(reql),PCStr(head),PVStr(user),void **utoken){
	return -1;
}
#endif

