#include <sys/types.h>
#include <stdlib.h>
#include <regex.h>
#include <vector>

const char *RegexVer(){
	return "regex";
}
void *Regcomp(const char *pat,int flag){
	regex_t re;
	regex_t *rre;
	int rcode;

	rcode = regcomp(&re,pat,flag);
	if( rcode == 0 ){
		rre = (regex_t*)malloc(sizeof(re));
		*rre = re;
		return (void*)rre;
	}
	return 0;
}
int Regexec(void *re,const char *str,int nm,int so,int eo,int flag){
	std::vector<regmatch_t> rm(nm < 1 ? 1 : nm);

	rm[0].rm_so = so;
	rm[0].rm_eo = eo;
	return regexec((regex_t*)re,str,nm < 0 ? 0 : nm,rm.data(),flag);
}
void Regfree(void *re){
	if( re == 0 )
		return;
	regfree((regex_t*)re);
	free(re);
}
