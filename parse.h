#ifndef PARSE
#define PARSE
#include "sexpr.h"
#include "token.h"

Sexpr* newSexpr(void);
Sexpr* parseStr(char* s);

#endif /*PARSE*/