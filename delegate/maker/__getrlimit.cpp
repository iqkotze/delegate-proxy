#include "yselect.h" /* FD_SETSIZE */
#include <sys/time.h>
#include <sys/resource.h>

static int expand(const char *what,int op,int amax)
{	struct rlimit rl;
	int max = amax;
	int ocur;

	getrlimit(op,&rl);
	ocur = rl.rlim_cur;
	if( rl.rlim_cur < max ){
		if( rl.rlim_max < max )
			max = rl.rlim_max;
		rl.rlim_cur = max;
		rl.rlim_max = max;
		setrlimit(op,&rl);
		getrlimit(op,&rl);
	}
	/*
	porting_dbg("RLIMIT_%s = %d->%d/%d",what,ocur,rl.rlim_cur,rl.rlim_max);
	*/
	return rl.rlim_cur;
}

#ifdef RLIMIT_NOFILE
int nofile_limit();
/// Upper bound for descriptor tables, as the hard limit can be in the billions.
static const rlim_t kNofileCap = 65536;

/// Raises the soft RLIMIT_NOFILE to the hard limit (at most kNofileCap) and returns the new soft limit.
int raise_nofile_limit(int *before,int *hard)
{	struct rlimit rl;
	rlim_t want;

	if( getrlimit(RLIMIT_NOFILE,&rl) != 0 )
		return -1;
	if( before ) *before = rl.rlim_cur == RLIM_INFINITY ? (int)kNofileCap : (int)rl.rlim_cur;
	if( hard ) *hard = rl.rlim_max == RLIM_INFINITY ? -1 : (int)(rl.rlim_max < 0x7fffffff ? rl.rlim_max : 0x7fffffff);
	want = rl.rlim_max < kNofileCap ? rl.rlim_max : kNofileCap;
	if( rl.rlim_cur != RLIM_INFINITY && rl.rlim_cur < want ){
		rl.rlim_cur = want;
		setrlimit(RLIMIT_NOFILE,&rl);
	}
	return nofile_limit();
}

/// Current soft RLIMIT_NOFILE, between 64 and kNofileCap.
int nofile_limit()
{	struct rlimit rl;

	if( getrlimit(RLIMIT_NOFILE,&rl) != 0 )
		return FD_SETSIZE;
	if( rl.rlim_cur == RLIM_INFINITY || kNofileCap < rl.rlim_cur )
		return (int)kNofileCap;
	return rl.rlim_cur < 64 ? 64 : (int)rl.rlim_cur;
}

int expand_fdset(int amax)
{	struct rlimit rl;
	int max = amax;
	int ocur;

	getrlimit(RLIMIT_NOFILE,&rl);
	ocur = rl.rlim_cur;
	if( rl.rlim_cur < max ){
		if( rl.rlim_max < max )
			max = rl.rlim_max;
		rl.rlim_cur = max;
		rl.rlim_max = max;
		setrlimit(RLIMIT_NOFILE,&rl);
		getrlimit(RLIMIT_NOFILE,&rl);
	}
	return rl.rlim_cur;
}

#else

int raise_nofile_limit(int *before,int *hard)
{
	return FD_SETSIZE;
}
int nofile_limit()
{
	return FD_SETSIZE;
}
int expand_fdset(int amax)
{
	porting_dbg("FD_SETSIZE = %d",FD_SETSIZE);
	return FD_SETSIZE;
}
#endif

#ifdef RLIMIT_STACK
int expand_stack(int smax)
{
	return expand("STACK",RLIMIT_STACK,smax);
}
#else
int expand_stack(int smax)
{
	return -1;
}
#endif
