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

/*
void create_atom_from_int(Sexpr* s, int atom){
  if(s->atom != NULL)
    printf("\nSetting non-null atom to value %d\n", atom);
  s->atom=(char*)malloc(20);
  sprintf(s->atom,"%d",atom);
}

void create_atom_from_float(Sexpr* s, float atom){
  if(s->atom != NULL)
    printf("\nSetting non-null atom to value %f\n", atom);
  s->atom=(char*)malloc(20);
  sprintf(s->atom,"%f",atom);
}

void create_atom(Sexpr* s, char* atom){
  if(s->atom != NULL)
    printf("\nSetting non-null atom to value %s\n", atom);
  s->atom=(char*)malloc(strlen(atom) + 10);
  strcpy(s->atom,atom);
}

Sexpr* copy_sexpr(Sexpr* s){
  Sexpr* copys = NULL;
  if(s != NULL){
    /*copy atom if there
    /*copy inner if there
  }
  return copys;
}*/

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
  
  
  if(get_atom(s) != NULL){
    if(is_int(get_atom(s)) || is_float(get_atom(s)))
      return s;
    else{
      return eval(findEnv(env, get_atom(s)), env->inner) ;
    }
  }
  /*TODO NULL checks!*/
  op = s->inner->next;
  
  if(get_atom(op) != NULL && !strcmp(get_atom(op), "+")){
    operand = eval(op->next, env);
    result = atof(get_atom(operand));
    operand = eval(op->next->next, env);
    result += atof(get_atom(operand));
    resultSexpr = newSexpr();
    /*resultSexpr->atom=(char*)malloc(strlen(get_atom(operand)) + 10);
    sprintf(get_atom(resultSexpr),"%f",result);*/
    create_atom_from_float(resultSexpr, result);
    return resultSexpr;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "-")){
    operand = eval(op->next, env);
    result = atof(get_atom(operand));
    operand = eval(op->next->next, env);
    result -= atof(get_atom(operand));
    resultSexpr = newSexpr();
    /*resultSexpr->atom=(char*)malloc(strlen(get_atom(operand)) + 10);
    sprintf(get_atom(resultSexpr),"%f",result);*/
    create_atom_from_float(resultSexpr, result);
    return resultSexpr;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "*")){
    operand = eval(op->next, env);
    result = atof(get_atom(operand));
    operand = eval(op->next->next, env);
    result *= atof(get_atom(operand));
    resultSexpr = newSexpr();
    /*resultSexpr->atom=(char*)malloc(strlen(get_atom(operand)) + 10);
    sprintf(resultSexpr->atom,"%f",result);*/
    create_atom_from_float(resultSexpr, result);
    return resultSexpr;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "/")){
    operand = eval(op->next, env);
    result = atof(get_atom(operand));
    operand = eval(op->next->next, env);
    result /= atof(get_atom(operand));
    resultSexpr = newSexpr();
    /*resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    sprintf(resultSexpr->atom,"%f",result);*/
    create_atom_from_float(resultSexpr, result);
    return resultSexpr;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), ">")){
    printSexpr(op->next);
    operand = eval(op->next, env);
    result = atof(get_atom(operand));
    operand = eval(op->next->next, env);
    result2 = atof(get_atom(operand));
    bool = result > result2 ? "True" : "False";
    resultSexpr = newSexpr();
    /*resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    strcpy(resultSexpr->atom,bool);*/
    create_atom(resultSexpr, bool);
    return resultSexpr;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "<")){
    operand = eval(op->next, env);
    result = atof(get_atom(operand));
    operand = eval(op->next->next, env);
    result2 = atof(get_atom(operand));
    bool = result < result2 ? "True" : "False";
    resultSexpr = newSexpr();
    /*resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    strcpy(resultSexpr->atom,bool);*/
    create_atom(resultSexpr, bool);
    return resultSexpr;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "eq?")){
    operand = eval(op->next, env);
    /*shouldn't be comparing floats*/
    if(get_atom(operand) != NULL){
      result = atof(get_atom(operand));
      operand = eval(op->next->next, env);
      result2 = atof(get_atom(operand));
      bool = result == result2 ? "True" : "False";
    }
    else
      bool = operand->inner->next == NULL && op->next->next->inner->next == NULL ? "True" : "False";
    
    resultSexpr = newSexpr();
    /*resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    strcpy(resultSexpr->atom,bool);*/
    create_atom(resultSexpr, bool);
    return resultSexpr;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "atom?")){
    operand = eval(op->next, env);    
    bool = get_atom(operand) != NULL ? "True" : "False";
    resultSexpr = newSexpr();
    /*resultSexpr->atom=(char*)malloc(10);
    strcpy(resultSexpr->atom,bool);*/
    create_atom(resultSexpr, bool);
    return resultSexpr;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "null?")){
    operand = eval(op->next, env);    
    bool = operand == NULL ? "True" : "False";
    resultSexpr = newSexpr();
    /*resultSexpr->atom=(char*)malloc(10);
    strcpy(resultSexpr->atom,bool);*/
    create_atom(resultSexpr, bool);
    return resultSexpr;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "car")){
    operand = eval(op->next, env)->inner->next;    
    operand->next = NULL;
    return operand;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "cdr")){
    operand = eval(op->next, env)->inner->next->next;    
    return operand;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "cond")){
    operand = op->next;
    while(operand){
      if(!strcmp(get_atom(eval(operand->inner->next, env)), "True"))
        return eval(operand->inner->next->next, env);
      operand = operand->next;
    }
    return NULL;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "cons")){
    operand = eval(op->next, env); 
    setSexpr = eval(op->next->next, env)->inner->next;
    resultSexpr = newSexpr();
    resultSexpr->inner = newSexpr();
    resultSexpr->inner->atom=(char*)malloc(10);
    strcpy(resultSexpr->inner->atom, "HEAD");
    resultSexpr->inner->next = operand;
    resultSexpr->inner->next->next = setSexpr;
    return resultSexpr;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "quote")){
    return op->next;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "define")){/*only sets for current inner env, so could have another with a different value in outer env*/
    insertEnv(env, get_atom(op->next), op->next->next);
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "set!")){/*set value for any environment, so set with inner and will find in outer and update that*/
    setEnv(env, get_atom(op->next), op->next->next);
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "begin")){
    beginSexpr = op->next;
    beginSexprValue = NULL;
    while(beginSexpr){
      beginSexprValue = eval(beginSexpr, env);
      beginSexpr = beginSexpr->next;
    }
    return beginSexprValue;
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "if")){
    if_sexpr = eval(op->next, env);
    if(if_sexpr != NULL && get_atom(if_sexpr) != NULL && !strcmp(get_atom(if_sexpr), "True")){      
      return eval(op->next->next, env);
    }
    else{      
      return eval(op->next->next->next, env);
    }
  }
  else if(get_atom(op) != NULL && !strcmp(get_atom(op), "lambda")){
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
      insertEnv(innerEnv, get_atom(lambda_arg_name), lambda_arg_value);
      lambda_arg_name = lambda_arg_name->next;
      lambda_arg_value = lambda_arg_value->next;
    }
    return eval(lambda_sexpr->inner->next->next->next, innerEnv);
  }
  return NULL;
}