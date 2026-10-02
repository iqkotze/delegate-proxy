#include <stdio.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <libutil.h>

int _ForkptyX(int *pty,char *name,void *mode,void *size){
	int pid;
	pid = forkpty(pty,name,(struct termios*)mode,(struct winsize*)size);
	return pid;
}
int _Forkpty(int *pty,char *name){
	return _ForkptyX(pty,name,NULL,NULL);
}
