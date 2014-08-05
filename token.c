#include <ctype.h> /*for isspace()*/
#include <string.h>/*for strcpy(), strlen()*/
#include <stdlib.h>/*for malloc()*/
#include "token.h"
#define BUFMAX 100

static Token *head = NULL;/*static, so only visible to this compilation unit*/
static Token *tail = NULL;
static char buf[BUFMAX] = "\0";/*start with empty string*/
static int index = 0;/*point to where to put next character in array*/

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

void tokenize(char c){
	if(head == NULL){/*if first time, initialize*/
		head = newToken();
		head->p="HEAD";
		tail = head;
	}
	if(isspace(c)){/*if whitespace and had a word, then add new token for that word*/
	    if(buf[0] != '\0')
	    	putToken();
	    /*if space but no word, then doing nothing*/
	}
	else{/*not white space*/
	    if(c == '(' || c == ')'){
	    	if(buf[0] != '\0')
	    		putToken();
    		buf[0]=c;
    		++index;
    		putToken();
	    }
	    else{
	    	buf[index++]=c;
	    }
	}
}

Token* tokenizeStr(char *s){
  char c;
  head = NULL;
  tail = NULL;
  while((c=*s++))
    tokenize(c);
  if(*buf)
    putToken();
  return head;
}

Token *newToken(void){
	Token *token = (Token*)malloc(sizeof(Token));
	token->p=NULL;
	token->next=NULL;
	return token;
}

void putToken(void){
	buf[index]='\0';
	tail->next=newToken();
	tail=tail->next;
	tail->p=(char*)malloc(strlen(buf)+1);/*+1 for \0*/
	strcpy(tail->p, buf);
	buf[0]='\0';
	index=0;
}

void deleteNextToken(Token *tok){
  if(tok == NULL)
    return;
  if(tok->next!=NULL)
    deleteNextToken(tok->next);
  free(tok->next);
  tok->next=NULL;
  tail=tok;
}
