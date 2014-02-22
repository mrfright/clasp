#include <stdio.h>
#include "token.h"


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
int main(void){
  char *s="(one (two)three four) ";
  char c;
  while(c=*s++)
  	tokenize(c);
  printToken(getHead()->next);
  printf("tail=%d\n", getTail());
  printf("head=%d\n", getHead());
  deleteNext(getHead());
  printToken(getHead()->next);
  printf("tail=%d\n", getTail());
  printf("head=%d\n", getHead());
  return 0;
}
