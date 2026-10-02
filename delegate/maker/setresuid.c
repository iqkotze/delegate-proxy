int SUBST_setresuid = 1; /* */

int setuid(int);
int seteuid(int);
int setgid(int);
int setegid(int);

int setresuid(int ruid,int euid,int suid)
{
	if( ruid != -1 ) setuid(ruid);
	if( euid != -1 ) seteuid(euid);
	return 0;
}
int setresgid(int rgid,int egid,int sgid)
{
	if( rgid != -1 ) setgid(rgid);
	if( egid != -1 ) setegid(egid);
	return 0;
}
