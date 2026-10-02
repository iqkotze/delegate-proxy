#ifndef _YALLOCA_H
#define _YALLOCA_H
#include "yarg.h"

typedef struct {
	char   *s_sp0;
  const	char   *s_what;
	iFUNCP s_func;
	char   *s_av[6];
	int	s_size;
	int	s_unit;
	int	s_count;
	int	s_trace;
	int	s_level;
	char   *s_top;
} AllocaArg;

int alloca_call(AllocaArg *ap);

#define STACK1	128

#endif /* _YALLOCA_H */
