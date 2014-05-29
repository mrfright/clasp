#include <stdlib.h> /*malloc, NULL*/
#include "env.h"

Env* newEnv(Env* inner){
  Env* e = (Env*)malloc(sizeof(Env));
  e->inner = inner;
  e->envTree = NULL;
  return e;
}

Sexpr* findEnv(Env* env, char* node){
  Sexpr* result = NULL;
  Tree* treeResult;
  treeResult = find(env->envTree, node);
  if(treeResult != NULL)
    result = treeResult->value;
  else if(result == NULL){
      result = env->inner == NULL ? NULL : findEnv(env->inner, node);
  }
  
  return result;
}

void insertEnv(Env* env, char* node, Sexpr* value){
  env->envTree = insert(env->envTree, node, value);
}

void setEnv(Env* env, char* node, Sexpr* value){
  if(find(env->envTree, node) != NULL)
    insert(env->envTree, node, value);
  else if(env->inner != NULL)
    setEnv(env->inner, node, value);
}