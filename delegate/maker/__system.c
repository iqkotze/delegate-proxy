#include "ystring.h"

int unix_system(PCStr(com));
int std::system(PCStr(com)){
	return unix_system(com);
}
