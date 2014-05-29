#include <ctype.h>
#include <stdlib.h> /*NULL, atof*/
#include <stdio.h> /*?sprintf?*/
#include <string.h>/*strcmp*/
#include "eval.h"
#include "parse.h"

int is_int(char* s){
  int result = 0;
  char c;
  if(*s == '-')
    s++;
  while(isdigit(c=*s++))
    result = 1;
  return c ? 0 : result;
}

int is_float(char* s){
  int result = 0;
  char c;
  if(*s == '-')
    s++;
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

void printEvalSexpr(Sexpr* sexpr){
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

void printEvalTree(Tree* tree){
  if(tree == NULL){
    printf("NULL\n");
    return;
  }
  printf("%s = ", tree->node);
  printSexpr(tree->value);
  printf("\n");
  /*printf("%s left\n", tree->node);*/
  if(tree->left == NULL);
    /*printf("left is null\n");*/
  else
    printEvalTree(tree->left);
  /*printf("%s right\n", tree->node);*/
  if(tree->right == NULL);
    /*printf("right is null\n");*/
  else
    printEvalTree(tree->right);
  /*printf("%s done\n", tree->node);*/
}

Sexpr* eval(Sexpr* s, Env* env){
  Sexpr* op;
  Sexpr* operand;
  Sexpr* resultSexpr;
  Sexpr* lambda_arg_name;
  Sexpr* lambda_arg_value;
  Sexpr* lambda_sexpr;
  Sexpr* setSexpr;
  Sexpr* tempSetSexpr;
  Sexpr* beginSexpr;
  Sexpr* beginSexprValue;
  Sexpr* if_sexpr;
  float result;
  float result2;
  char* bool;
  Env* innerEnv;
  Env* printEnv;
  
  if(s->atom != NULL){
    if(is_int(s->atom) || is_float(s->atom))
      return s;
    else{
      return eval(findEnv(env, s->atom), env->inner) ;
    }
  }
  /*TODO NULL checks!*/
  op = s->inner->next;
  
  if(op->atom != NULL && !strcmp(op->atom, "+")){
    operand = eval(op->next, env);
    result = atof(operand->atom);
    operand = eval(op->next->next, env);
    result += atof(operand->atom);
    resultSexpr = newSexpr();
    resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    sprintf(resultSexpr->atom,"%f",result);
    return resultSexpr;
  }
  else if(op->atom != NULL && !strcmp(op->atom, "-")){
    operand = eval(op->next, env);
    result = atof(operand->atom);
    operand = eval(op->next->next, env);
    result -= atof(operand->atom);
    resultSexpr = newSexpr();
    resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    sprintf(resultSexpr->atom,"%f",result);
    return resultSexpr;
  }
  else if(op->atom != NULL && !strcmp(op->atom, "*")){
    operand = eval(op->next, env);
    result = atof(operand->atom);
    operand = eval(op->next->next, env);
    result *= atof(operand->atom);
    resultSexpr = newSexpr();
    resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    sprintf(resultSexpr->atom,"%f",result);
    return resultSexpr;
  }
  else if(op->atom != NULL && !strcmp(op->atom, "/")){
    operand = eval(op->next, env);
    result = atof(operand->atom);
    operand = eval(op->next->next, env);
    result /= atof(operand->atom);
    resultSexpr = newSexpr();
    resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    sprintf(resultSexpr->atom,"%f",result);
    return resultSexpr;
  }
  else if(op->atom != NULL && !strcmp(op->atom, ">")){
    printEvalSexpr(op->next);
    operand = eval(op->next, env);
    result = atof(operand->atom);
    operand = eval(op->next->next, env);
    result2 = atof(operand->atom);
    bool = result > result2 ? "True" : "False";
    resultSexpr = newSexpr();
    resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    strcpy(resultSexpr->atom,bool);
    return resultSexpr;
  }
  else if(op->atom != NULL && !strcmp(op->atom, "<")){
    operand = eval(op->next, env);
    result = atof(operand->atom);
    operand = eval(op->next->next, env);
    result2 = atof(operand->atom);
    bool = result < result2 ? "True" : "False";
    resultSexpr = newSexpr();
    resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    strcpy(resultSexpr->atom,bool);
    return resultSexpr;
  }
  else if(op->atom != NULL && !strcmp(op->atom, "quote")){
    return op->next;
  }
  else if(op->atom != NULL && !strcmp(op->atom, "define")){/*only sets for current inner env, so could have another with a different value in outer env*/
    insertEnv(env, op->next->atom, op->next->next);
  }
  else if(op->atom != NULL && !strcmp(op->atom, "set!")){/*set value for any environment, so set with inner and will find in outer and update that*/
    setEnv(env, op->next->atom, op->next->next);
  }
  else if(op->atom != NULL && !strcmp(op->atom, "begin")){
    beginSexpr = op->next;
    beginSexprValue = NULL;
    while(beginSexpr){
      beginSexprValue = eval(beginSexpr, env);
      beginSexpr = beginSexpr->next;
    }
    return beginSexprValue;
  }
  else if(op->atom != NULL && !strcmp(op->atom, "if")){
    if_sexpr = eval(op->next, env);
    if(if_sexpr != NULL && if_sexpr->atom != NULL && !strcmp(if_sexpr->atom, "True")){      
      return eval(op->next->next, env);
    }
    else{      
      return eval(op->next->next->next, env);
    }
  }
  else if(op->atom != NULL && !strcmp(op->atom, "lambda")){
    return s;
  }
  
  else{/*assume the first thing is a lambda expression*/    
    /*
    ((lambda (a b) (+ a b)) 5 6)
    
    s->inner
    sexpr with atom='HEAD'
    s->inner->atom = "HEAD"
    
    s->inner->next
    sexpr (lambda (a b) (+ a b))
    
    s->inner->next->inner
    sexpr with atom ="lambda"
    
    s->inner->next->inner->atom = "HEAD"
    
    s->inner->next->inner->next->atom = "lambda"
    
    s->inner->next->inner->next->next
    sexpr with arg names
    
    s->inner->next->inner->next->next->inner
    sexpr of arg names (a b)
    
     s->inner->next->inner->next->next->inner->atom
     "HEAD" of arg name sexpr
     
     s->inner->next->inner->next->next->inner->next->atom
     "a" arg name
     
     s->inner->next->inner->next->next->inner->next->next->atom
     "b" arg name
    
    
    
    s->inner->next->inner->next->next->next
    sexpr of thing to eval
    
     s->inner->next->inner->next->next->next->inner
    inner sexpr of thing to eval
    
    s->inner->next->inner->next->next->next->inner->atom
    "HEAD" of sexpr to eval
  
    s->inner->next->inner->next->next->next->inner->next->atom
    "+" operator
    
    s->inner->next->next->atom
    "5"
    */
  
    /*make a new inner env to eval*/
    lambda_sexpr = eval(s->inner->next, env);
    
    /*if(lambda_sexpr->inner->next->atom == NULL || strcmp(lambda_sexpr->inner->next->atom, "lambda"))
      printf("\nnot lambda as expected?\n");
    else
      printf("\nlambda as expected\n");*/
    innerEnv = newEnv(env);
    lambda_arg_name = lambda_sexpr->inner->next->next->inner->next;
    lambda_arg_value = s->inner->next->next;
    while(lambda_arg_name && lambda_arg_value){
      insertEnv(innerEnv, lambda_arg_name->atom, lambda_arg_value);
      lambda_arg_name = lambda_arg_name->next;
      lambda_arg_value = lambda_arg_value->next;
    }
    return eval(lambda_sexpr->inner->next->next->next, innerEnv);
  }
  return NULL;
}