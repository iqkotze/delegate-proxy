const char *RegexVer(){
	return "none";
}
void *Regcomp(const char *pat,int flag){
	return 0;
}
int Regexec(void *re,const char *str,int nm,int so,int eo,int flag){
	return -1;
}
void Regfree(void *re){
}
