#if defined(BUGGY_USLEEP)

#include "usleep.cpp"

#else
#include "ystring.h"
#include <unistd.h>
void usleep_bypoll(int);

static int buggy_USLEEP;
void Usleep(int usec)
{	CStr(uname,128);

	if( buggy_USLEEP == 0 ){
		Uname(AVStr(uname));
		if( strncmp(uname,"HI-UX",5) == 0 )
			buggy_USLEEP = 1;
		else	buggy_USLEEP = -1;
	}
	if( 0 < buggy_USLEEP )
		usleep_bypoll(usec);
	else	usleep(usec);
}
#endif
