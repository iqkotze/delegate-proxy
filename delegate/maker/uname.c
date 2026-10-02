#define UNAME "?"

#include "ystring.h"
int Uname(PVStr(name))
{
	strcpy(name,UNAME);
	return -1;
}
