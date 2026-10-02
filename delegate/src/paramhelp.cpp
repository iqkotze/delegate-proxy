// -Fparam: lists the parameters or shows the details of one parameter
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "dgparam.h"

static void printList(FILE *out)
{
	for( int i = 0; i < dg_params_count; i++ )
		fprintf(out,"%-14s %s\n",dg_params[i].name,dg_params[i].desc);
}

static void printDetails(FILE *out,const DgParam *p)
{
	fprintf(out,"%s\n",p->name);
	fprintf(out,"  Syntax:   %s\n",p->syntax);
	fprintf(out,"  Default:  %s\n",p->dflt);
	fprintf(out,"  Summary:  %s\n",p->desc);
	fprintf(out,"  Example:  %s\n",p->example);
	fprintf(out,"  Source:   %s:%d\n",p->file,p->line);
	if( p->nsubs == 0 )
		return;
	fprintf(out,"\n  Options\n");
	for( int i = 0; i < p->nsubs; i++ ){
		const DgParamSub *s = &p->subs[i];
		fprintf(out,"  %-16s %s\n",s->name,s->desc);
		fprintf(out,"  %-16s syntax %s, default %s, example %s\n","",s->syntax,s->dflt,s->example);
	}
}

int param_main(int ac,const char *av[])
{
	if( ac < 2 ){
		printList(stdout);
		return 0;
	}
	for( int i = 0; i < dg_params_count; i++ ){
		if( strcasecmp(dg_params[i].name,av[1]) == 0 ){
			printDetails(stdout,&dg_params[i]);
			return 0;
		}
	}
	fprintf(stderr,"unknown parameter: %s\n",av[1]);
	return 1;
}
