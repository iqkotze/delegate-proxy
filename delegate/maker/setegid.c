int SUBST_setegid = 1;

int setresgid(int,int,int);

int setegid(int gid)
{
	return setresgid(-1,gid,-1);
}
