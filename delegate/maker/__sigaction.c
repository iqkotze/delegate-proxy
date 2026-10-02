#include <signal.h>
#include <strings.h>


#if defined(SA_RESTART)
typedef void (*VFunc)(int);
VFunc signalRESTART(int sig,VFunc handler)
{	struct sigaction act,oact;

	bzero((char*)&act,sizeof(act));
	bzero((char*)&act.sa_mask,sizeof(act.sa_mask));
	act.sa_handler = handler;
	act.sa_flags = SA_RESTART; /* without SA_NOCLDSTOP */

	if( sigaction(sig,&act,&oact) == -1 )
		return (VFunc)-1;
	return oact.sa_handler;
}
#else
#include "sigaction.c"
#endif
