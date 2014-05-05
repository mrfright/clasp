#include <stdio.h>
#include "token.h"
#include "parse.h"


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
  return 0;
}
