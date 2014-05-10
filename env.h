#ifndef ENV
#define ENV
#include "tree.h"

typedef struct env Env;

struct env{
	Tree *envTree;
	Env *inner;
};

Env* newEnv(Env* inner);
char* findEnv(Env* env, char* node);
void insertEnv(Env* env, char* node, char* value);
#endif /*ENV*/