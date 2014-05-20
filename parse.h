#ifndef PARSE
#define PARSE
#include "sexpr.h"
#include "token.h"

Sexpr* newSexpr(void);
Sexpr* parse(Token** token);

#endif /*PARSE*/

