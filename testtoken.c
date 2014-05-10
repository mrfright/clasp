#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "parse.h"
#include "env.h"


void printToken(Token* token){
  if(token!=NULL){
	while(token!=NULL){
      printf("%s", token->p);
      token=token->next;
      if(token!=NULL)
        printf("->");
    }
    printf("->");
  }
  printf("NULL\n");
}

void printSexpr(Sexpr* sexpr){
  if(sexpr == NULL){
    printf(" NIL ");
    return;
  }
  if(sexpr->atom!=NULL)
    printf(" %s ", sexpr->atom);
  else{
    printf("(");
    printSexpr(sexpr->inner->next);/*next to skip linked list head*/
    printf(")");
  }
  printf("->");
  printSexpr(sexpr->next);
}
int main(void){
  char *s="(one (two)three four) ";
  char c;
  Env *e, *outerEnv;
  while(c=*s++)
  	tokenize(c);
  printToken(getHeadToken()->next);
  printSexpr(parse(&(getHeadToken()->next)));
  printf("tail=%d\n", getTailToken());
  printf("head=%d\n", getHeadToken());
  deleteNextToken(getHeadToken());
  printToken(getHeadToken()->next);
  printf("tail=%d\n", getTailToken());
  printf("head=%d\n", getHeadToken());
  
  e = newEnv(NULL);
  printf("finding node in an empty env with no inner (should  be null):%s\n", findEnv(e, "not there"));
  insertEnv(e, "node1", "value1");
  printf("finding node in env after inserting one (should be 'node1','value1'):%s\n", findEnv(e, "node1"));
  printf("finding non-existent node in env with one in it (should be null):%s\n", findEnv(e, "still not there"));
  insertEnv(e, "node2", "value2");
  printf("finding another node in env after another insert (should be 'value2'):%s\n", findEnv(e, "node2"));
  outerEnv = newEnv(e);
  printf("finding node in outer env that isn't in either env (should be null):%s\n", findEnv(outerEnv, "nope"));
  printf("finding node in outer env that is actually in inner env (should be 'value1'):%s\n", findEnv(outerEnv, "node1"));
  insertEnv(outerEnv, "node3", "value3");
  printf("finding node in outer env that isn't in either (should be null):%s\n", findEnv(outerEnv, "nah"));
  printf("finding node in outer env that is actually in inner env (should be 'value2'):%s\n", findEnv(outerEnv, "node2"));
  printf("findnig node in outer env that should be in outer (should be 'value3'):%s\n", findEnv(outerEnv, "node3"));
  return 0;
}
