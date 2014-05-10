#include <stdlib.h> /*malloc*/
#include "env.h"

Env* newEnv(Env* inner){
  Env* e = (Env*)malloc(sizeof(Env));
  e->inner = inner;
  e->envTree = NULL;
  return e;
}

char* findEnv(Env* env, char* node){
  char* result = NULL;
  Tree* treeResult;
  treeResult = find(env->envTree, node);
  if(treeResult != NULL)
    result = treeResult->value;
  else if(result == NULL){
      result = env->inner == NULL ? NULL : findEnv(env->inner, node);
  }
  
  return result;
}

void insertEnv(Env* env, char* node, char* value){
  env->envTree = insert(env->envTree, node, value);
}