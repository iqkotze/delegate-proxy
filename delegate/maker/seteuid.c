int SUBST_seteuid = 1;

int setresuid(int,int,int);

int seteuid(int uid)
{
	return setresuid(-1,uid,-1);
}
