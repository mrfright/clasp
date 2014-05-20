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
  printf(">");
  while(gets(line)){
    printf(line);
    tokenizeStr(line);
    printToken(getHeadToken()->next);
    printSexpr(eval(parse(&getHeadToken()->next)));
    printf("\n>");
  }
  return 0;
}
