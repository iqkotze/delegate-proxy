#ifndef _DGPARAM_H
#define _DGPARAM_H

/// Declarations read by tools/gen-params.py. They expand to nothing.
#define DG_PARAM(...)
#define DG_PARAM_SUB(...)
#define DG_PARAM_INTERNAL(...)

typedef struct DgParamSub {
  const char *name;
  const char *syntax;
  const char *dflt;
  const char *desc;
  const char *example;
} DgParamSub;

typedef struct DgParam {
  const char *name;
  const char *syntax;
  const char *dflt;
  const char *desc;
  const char *example;
  const char *file;
  int line;
  const DgParamSub *subs;
  int nsubs;
} DgParam;

/// Parameter table generated at build time, sorted by name.
extern const DgParam dg_params[];
extern const int dg_params_count;

#endif
