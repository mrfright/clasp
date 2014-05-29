#ifndef ENV
#define ENV
#include "tree.h"
#include "sexpr.h"

typedef struct env Env;

struct env{
	Tree *envTree;
	Env *inner;/*I call inner, but really is outer?*/
};

Env* newEnv(Env* inner);
Sexpr* findEnv(Env* env, char* node);
void insertEnv(Env* env, char* node, Sexpr* value);
#endif /*ENV*/