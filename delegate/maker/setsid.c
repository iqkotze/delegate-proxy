int SUBST_setsid = 1;
#include <sys/ioctl.h>


int open(char*,int);
int close(int);
int getpid();

int setsid()
{       int fd;

#ifdef TIOCNOTTY
        if( 0 <= (fd = open("/dev/tty",0)) ){
                ioctl(fd,TIOCNOTTY,0);
                close(fd);
		return getpid();
        }
#endif
	return -1;
}
