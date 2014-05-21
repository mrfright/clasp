#include <ctype.h>
#include <stdlib.h> /*NULL, atof, sprintf*/
#include <string.h>/*strcmp*/
#include "eval.h"
#include "parse.h"

int is_int(char* s){
  int result = 0;
  char c;
  while(isdigit(c=*s++))
    result = 1;
  return c ? 0 : result;
}

int is_float(char* s){
  int result = 0;
  char c;
  while(isdigit(c=*s++))
    result = 1;
  if(c == '.' && result){
    result = 0;
    while(isdigit(c=*s++))
      result = 1;
    if(c) result=0;
  }
  else result = 0;
  return result;
}

Sexpr* eval(Sexpr* s){
  Sexpr* op;
  Sexpr* operand;
  Sexpr* resultSexpr;
  float result;
  /*if atom*/
    /*if int return that : actually not, just return sexpr as is, same with float, a number will be used outer expression (and just convert to float then add)*/
    /*if float return that*/
    /*if neither of those, then something in environment*/
  
  /*else not atom*/
    /*
    +
    -
    *
    %
    quote
    car
    cdr
    else evaluate as a function from environment
    */
  
  if(s->atom != NULL){
    if(is_int(s->atom) || is_float(s->atom))
      return s;
  }
  /*else it's not an atom, get first item since that's the function to call (remember "first" is after head)*/
  /*TODO NULL checks!*/
  op = s->inner->next;
  if(!strcmp(op->atom, "+")){
    operand = eval(op->next);
    result = atof(operand->atom);
    operand = eval(op->next->next);
    result += atof(operand->atom);
    resultSexpr = newSexpr();
    resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    sprintf(resultSexpr->atom,"%f",result);
    return resultSexpr;
  }
  else if(!strcmp(op->atom, "-")){
    operand = eval(op->next);
    result = atof(operand->atom);
    operand = eval(op->next->next);
    result -= atof(operand->atom);
    resultSexpr = newSexpr();
    resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    sprintf(resultSexpr->atom,"%f",result);
    return resultSexpr;
  }
  else if(!strcmp(op->atom, "*")){
    operand = eval(op->next);
    result = atof(operand->atom);
    operand = eval(op->next->next);
    result *= atof(operand->atom);
    resultSexpr = newSexpr();
    resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    sprintf(resultSexpr->atom,"%f",result);
    return resultSexpr;
  }
  else if(!strcmp(op->atom, "/")){
    operand = eval(op->next);
    result = atof(operand->atom);
    operand = eval(op->next->next);
    result /= atof(operand->atom);
    resultSexpr = newSexpr();
    resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    sprintf(resultSexpr->atom,"%f",result);
    return resultSexpr;
  }
}