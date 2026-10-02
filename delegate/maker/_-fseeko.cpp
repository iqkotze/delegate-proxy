
#include "ystring.h"

int Fseeko(FILE *fp,FileSize off,int whence){
	return fseeko(fp,off,whence);
}
FileSize Ftello(FILE *fp){
	return ftello(fp);
}
