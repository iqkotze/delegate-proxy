#include "ystring.h"

int unix_system(PCStr(com));
extern "C" {
int system(PCStr(com)){
	return unix_system(com);
}
}
