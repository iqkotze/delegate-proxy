#include <sys/types.h>
#if defined(STAT64)
#define __USE_FILE_OFFSET64
#endif
#include <dirent.h>
#include <stdio.h>
#include "yarg.h"

int scan_ino;
#define D_INO(de)	de->d_ino

int Scandir(const char *dirpath,int(*func)(const char*,...),...)
{	DIR *dirp;
	struct dirent *dir1;
	int rcode;

	VARGS(8,func);

	rcode = 0;
	if( dirp = opendir(dirpath) ){
		while( dir1 = readdir(dirp) ){
			scan_ino = D_INO(dir1);
			if( rcode = (*func)(dir1->d_name,VA8) )
				break;
		}
		closedir(dirp);
	}
	return rcode;
}

