#include <stdio.h>
#include "token.h"
#include "parse.h"
#include "eval.h"

char line[100];

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
  Sexpr* parsedSexpr;
  Sexpr* evaledSexpr;
  Env* env = newEnv(NULL);
  printf(">");
  while(gets(line)){
    parsedSexpr = parseStr(line);
    evaledSexpr = eval(parsedSexpr, env);
    printSexpr(evaledSexpr);
    /*deleteSexpr(parsedSexpr);this fucks things up for now
    /*deleteSexpr(evaledSexpr);have tree insert copy node and value instead of just assign pointer of something that will be deleted by something else*/
    printf("\n>");
  }
  return 0;
}
