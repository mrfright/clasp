#include "sexpr.h"
#include "token.h"
#include "parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>/*for strcmp test, strlen, str copy?*/

Sexpr* parse(Token** tokenList){
  Sexpr* sexpr = NULL;
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

Sexpr* parseStr(char* s){
  Token* tokens;
  Token* originalTokens;
  Sexpr* sexpr;
  originalTokens = tokens = tokenizeStr(s);  
  sexpr = parse(&(tokens->next));
  deleteNextToken(originalTokens);
  free(originalTokens);
  return sexpr;
}
