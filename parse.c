#include "sexpr.h"
#include "token.h"
#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>/*for strcmp test, strlen, str copy?*/

/*
parse(token list)
  if no chars (strlen zero) then error - print and exit
  token = pop a token off passed in list
  if token is '('
    start a new sexpr
    while next token not ')'
      append to sexpr's list parse(rest of tokens)
    pop token (throw away that ')')
    return that sexpr list
  else if token is ')' then error unexpected
  else return sexpr atom
*/

static Sexpr *head = NULL;/*static, so only visible to this compilation unit*/
static Sexpr *tail = NULL;

Sexpr* newSexpr(void){
  Sexpr* sexpr = (Sexpr*)malloc(sizeof(Sexpr));
  sexpr->inner = NULL;
  sexpr->next = NULL;
  sexpr->atom = NULL;
  return sexpr;
}

Sexpr* makeSexprHead(void){
  head = newSexpr();
  head->atom = "HEAD";
  tail=head;
  return head;
}

void addSexpr(Sexpr* sexpr){
  tail->next = sexpr;
  tail = tail->next;
}

Sexpr* parse(Token** tokenList){
  Sexpr* sexpr = NULL;
  Sexpr* addNext = NULL;
  Sexpr* addTail = NULL;
  Token* popToken = NULL;
  if(*tokenList == NULL) printf("\nunexpected end of tokens\n");/*what about whole expression is an empty list? what if just "()"? */

  else if(strcmp(")", (*tokenList)->p) == 0) printf("\nunexpected ')'\n");
  
  else { 
    sexpr = newSexpr();
    if(strcmp("(", (*tokenList)->p) == 0){/*make a new non-atom s-expression*/
      sexpr->inner = newSexpr();
      sexpr->inner->atom = "HEAD";
      addTail = sexpr->inner;
	  popToken = *tokenList;
	  *tokenList = (*tokenList)->next;/*pop the '(' off*/
	  free(popToken->p);
	  free(popToken);
	  if(*tokenList == NULL) printf("\nunexpected end of tokens after '('\n");
	  else{
	    while(strcmp(")", (*tokenList)->p)!=0){
	      addTail->next = parse(tokenList);
	      addTail = addTail->next;
	    }
	    popToken = *tokenList;
	    *tokenList = (*tokenList)->next;/*pop the ')' off*/
	    free(popToken->p);
	    free(popToken);
	  }
    }
    else {/*make an atom*/
	  sexpr->atom=(char*)malloc(strlen((*tokenList)->p)+1);/*+1 for \0*/
	  strcpy(sexpr->atom, (*tokenList)->p);
	  *tokenList = (*tokenList)->next;
    }
  }
  return sexpr;
}


