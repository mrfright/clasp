#ifndef EVAL
#define EVAL
#include "sexpr.h"

int is_int(char* s);
int is_float(char* s);
Sexpr* eval(Sexpr* s);

#endif /*EVAL*/