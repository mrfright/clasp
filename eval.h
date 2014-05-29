#ifndef EVAL
#define EVAL
#include "sexpr.h"
#include "env.h"

int is_int(char* s);
int is_float(char* s);
Sexpr* eval(Sexpr* s, Env* env);

#endif /*EVAL*/