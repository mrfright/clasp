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

Sexpr* add(Sexpr* s, Env* env){
  Sexpr* operand_result;
  Sexpr* operand;
  float result;
  Sexpr* resultSexpr;
  
  /*printf("\nadd\n");
  printSexpr(s);*/
  
  if(s == NULL){
    printf("\nadd operation on null Sexpr\n");
    return NULL;
  }
  result = 0.0;
  
  operand = get_inner(s);/*first inner is the operation*/
  if(operand == NULL){
    printf("\nadd function call on null inner which should be '+'\n");
    return NULL;
  }
  operand = operand->next;/*set to first operand*/

  while(operand != NULL){
    operand_result = eval(operand, env);
    if(!is_float(get_atom(operand_result)) && !is_int(get_atom(operand_result))){
      printf("\ntrying to add non-number '%s'\n", get_atom(operand_result));
      deleteSexpr(operand_result);
      return NULL;
    }
    result += atof(get_atom(operand_result));
    deleteSexpr(operand_result);
    operand = operand->next;
  }
  
  resultSexpr = newSexpr();
  create_atom_from_float(resultSexpr, result);
  return resultSexpr;
}

Sexpr* multiply(Sexpr* s, Env* env){
  Sexpr* operand_result;
  Sexpr* operand;
  float result;
  Sexpr* resultSexpr;
  
  
  if(s == NULL){
    printf("\nmultiply operation on null Sexpr\n");
    return NULL;
  }
  result = 1.0;
  
  operand = get_inner(s);/*first inner is the operation*/
  if(operand == NULL){
    printf("\nmultiply function call on null inner which should be '*'\n");
    return NULL;
  }
  operand = operand->next;/*set to first operand*/

  while(operand != NULL){
    operand_result = eval(operand, env);
    if(!is_float(get_atom(operand_result)) && !is_int(get_atom(operand_result))){
      printf("\ntrying to multiply non-number '%s'\n", get_atom(operand_result));
      deleteSexpr(operand_result);
      return NULL;
    }
    result *= atof(get_atom(operand_result));
    deleteSexpr(operand_result);
    operand = operand->next;
  }
  
  resultSexpr = newSexpr();
  create_atom_from_float(resultSexpr, result);
  return resultSexpr;
}

Sexpr* subtract(Sexpr* s, Env* env){
  Sexpr* operand_result;
  Sexpr* operand;
  float result;
  Sexpr* resultSexpr;  
  
  if(s == NULL){
    printf("\nsub operation on null Sexpr\n");
    return NULL;
  }
  result = 1.0;
  
  operand = get_inner(s);/*first inner is the operation*/
  if(operand == NULL){
    printf("\nsubtact function call on null inner which should be '-'\n");
    return NULL;
  }
  operand = operand->next;/*set to first operand*/

  operand_result = eval(operand, env);
  if(!is_float(get_atom(operand_result)) && !is_int(get_atom(operand_result))){
    printf("\ntrying to subract non-number '%s'\n", get_atom(operand_result));
    deleteSexpr(operand_result);
    return NULL;
  }
  result = atof(get_atom(operand_result));
  deleteSexpr(operand_result);
  operand = operand->next;
  operand_result = eval(operand, env);
  if(!is_float(get_atom(operand_result)) && !is_int(get_atom(operand_result))){
    printf("\ntrying to subract non-number '%s'\n", get_atom(operand_result));
    deleteSexpr(operand_result);
    return NULL;
  }
  result -= atof(get_atom(operand_result));
  deleteSexpr(operand_result);
  resultSexpr = newSexpr();
  create_atom_from_float(resultSexpr, result);
  return resultSexpr;
}


Sexpr* division(Sexpr* s, Env* env){
  Sexpr* operand_result;
  Sexpr* operand;
  float result;
  Sexpr* resultSexpr;  
  
  if(s == NULL){
    printf("\ndiv operation on null Sexpr\n");
    return NULL;
  }
  result = 1.0;
  
  operand = get_inner(s);/*first inner is the operation*/
  if(operand == NULL){
    printf("\ndivision function call on null inner which should be '-'\n");
    return NULL;
  }
  operand = operand->next;/*set to first operand*/

  operand_result = eval(operand, env);
  if(!is_float(get_atom(operand_result)) && !is_int(get_atom(operand_result))){
    printf("\ntrying to divide non-number '%s'\n", get_atom(operand_result));
    deleteSexpr(operand_result);
    return NULL;
  }
  result = atof(get_atom(operand_result));
  deleteSexpr(operand_result);
  operand = operand->next;
  operand_result = eval(operand, env);
  if(!is_float(get_atom(operand_result)) && !is_int(get_atom(operand_result))){
    printf("\ntrying to divide non-number '%s'\n", get_atom(operand_result));
    deleteSexpr(operand_result);
    return NULL;
  }
  result /= atof(get_atom(operand_result));
  deleteSexpr(operand_result);
  resultSexpr = newSexpr();
  create_atom_from_float(resultSexpr, result);
  return resultSexpr;
}

Sexpr* greaterThan(Sexpr* s, Env* env){
  Sexpr* operand_result;
  Sexpr* operand;
  char* bool;
  float result;
  float result2;
  Sexpr* resultSexpr;  
  
  
  if(s == NULL){
    printf("\ngreater than operation on null Sexpr\n");
    return NULL;
  }
  
  /*eval first, eval second, compare and make result, delete those two evals, return result*/
  operand = get_inner(s);/*first inner is the operation*/
  if(operand == NULL){
    printf("\ngreater than function call on null inner which should be '>'\n");
    return NULL;
  }
  operand = operand->next;
  operand_result = eval(operand, env);
  if(!is_float(get_atom(operand_result)) && !is_int(get_atom(operand_result))){
    printf("\ntrying to greater-than compare non-number '%s'\n", get_atom(operand_result));
    deleteSexpr(operand_result);
    return NULL;
  }
  result = atof(get_atom(operand_result));
  deleteSexpr(operand_result);
  
  operand = operand->next;
  operand_result = eval(operand, env);
  if(!is_float(get_atom(operand_result)) && !is_int(get_atom(operand_result))){
    printf("\ntrying to greater-than compare non-number '%s'\n", get_atom(operand_result));
    deleteSexpr(operand_result);
    return NULL;
  }
  result2 = atof(get_atom(operand_result));
  deleteSexpr(operand_result);

    bool = result > result2 ? "True" : "False";
    resultSexpr = newSexpr();
    /*resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    strcpy(resultSexpr->atom,bool);*/
    create_atom(resultSexpr, bool);
    return resultSexpr;
}

Sexpr* lessThan(Sexpr* s, Env* env){
  Sexpr* operand_result;
  Sexpr* operand;
  char* bool;
  float result;
  float result2;
  Sexpr* resultSexpr;  
  
  
  if(s == NULL){
    printf("\nless than operation on null Sexpr\n");
    return NULL;
  }
  
  /*eval first, eval second, compare and make result, delete those two evals, return result*/
  operand = get_inner(s);/*first inner is the operation*/
  if(operand == NULL){
    printf("\nless than function call on null inner which should be '<'\n");
    return NULL;
  }
  operand = operand->next;
  operand_result = eval(operand, env);
  if(!is_float(get_atom(operand_result)) && !is_int(get_atom(operand_result))){
    printf("\ntrying to less-than compare non-number '%s'\n", get_atom(operand_result));
    deleteSexpr(operand_result);
    return NULL;
  }
  result = atof(get_atom(operand_result));
  deleteSexpr(operand_result);
  
  operand = operand->next;
  operand_result = eval(operand, env);
  if(!is_float(get_atom(operand_result)) && !is_int(get_atom(operand_result))){
    printf("\ntrying to greater-than compare non-number '%s'\n", get_atom(operand_result));
    deleteSexpr(operand_result);
    return NULL;
  }
  result2 = atof(get_atom(operand_result));
  deleteSexpr(operand_result);

    bool = result < result2 ? "True" : "False";
    resultSexpr = newSexpr();
    /*resultSexpr->atom=(char*)malloc(strlen(operand->atom) + 10);
    strcpy(resultSexpr->atom,bool);*/
    create_atom(resultSexpr, bool);
    return resultSexpr;
}

Sexpr* equal(Sexpr* s, Env* env){
  Sexpr* operand;
  Sexpr* result1;
  Sexpr* result2;
  Sexpr* resultSexpr;
  char* bool;
  /*!strcmp(get_atom(op), "+")*/
  
  
  if(s == NULL){
    printf("\nequal operation on null Sexpr\n");
    return NULL;
  }
  
  /*eval first, eval second, compare and make result, delete those two evals, return result*/
  operand = get_inner(s);/*first inner is the operation*/
  if(operand == NULL){
    printf("\nequal function call on null inner which should be 'eq?'\n");
    return NULL;
  }
  operand = operand->next;
  
  if(operand == NULL){
    printf("\nequal function with no arguments\n");
    return NULL;
  }
  
  result1 = eval(operand, env);
  operand = operand->next;
  
  if(operand == NULL){
    printf("\nequal function with only one argument\n");
    deleteSexpr(result1);
    return NULL;
  }
  result2 = eval(operand, env);
  
  if(result1 != NULL && result2 != NULL){
    if(get_atom(result1) != NULL && get_atom(result2) != NULL){
      bool = !strcmp(get_atom(result1), get_atom(result2)) ? "True" : "False";
    }
    else if(get_atom(result1) == NULL && get_atom(result2) == NULL){
      printf("\ncan only call equal on atoms for now\n");
      bool = "False";
    }
    else bool = "False";/*one is NULL and other is not*/
  }
  else if(result1 == NULL && result2 == NULL) bool = "True";
  else bool = "False";/*one is NULL while other is not*/
  
  deleteSexpr(result1);
  deleteSexpr(result2);
    
  resultSexpr = newSexpr();
  create_atom(resultSexpr, bool);
  return resultSexpr;
}

Sexpr* is_atom(Sexpr* s, Env* env){
  Sexpr* operand;
  Sexpr* atom;
  Sexpr* resultSexpr;
  char* bool;
  
  if(s == NULL){
    printf("\natom? operation on null Sexpr\n");
    return NULL;
  }
  
  /*eval first, eval second, compare and make result, delete those two evals, return result*/
  operand = get_inner(s);/*first inner is the operation*/
  if(operand == NULL){
    printf("\natom? function call on null inner which should be 'atom?'\n");
    return NULL;
  }
  operand = operand->next;
  if(operand == NULL){
    printf("\natom? called with NULL argument\n");
    return NULL;
  }
  atom = eval(operand, env);
  bool = get_atom(atom) != NULL ? "True" : "False";
  deleteSexpr(atom);
  
  resultSexpr = newSexpr();
  create_atom(resultSexpr, bool);
  return resultSexpr;
}


Sexpr* is_null(Sexpr* s, Env* env){
  Sexpr* operand;
  Sexpr* atom;
  Sexpr* resultSexpr;
  char* bool;
  
  if(s == NULL){
    printf("\nnull? operation on null Sexpr\n");
    return NULL;
  }
  
  /*eval first, eval second, compare and make result, delete those two evals, return result*/
  operand = get_inner(s);/*first inner is the operation*/
  if(operand == NULL){
    printf("\nnull? function call on null inner which should be 'null?'\n");
    return NULL;
  }
  operand = operand->next;
  if(operand == NULL){
    bool = "True";
  }
  
  atom = eval(operand, env);
  bool = atom == NULL ? "True" : "False";
  deleteSexpr(atom);
  
  resultSexpr = newSexpr();
  create_atom(resultSexpr, bool);
  return resultSexpr;
}

Sexpr* car(Sexpr* s, Env* env){
  /*
  eval the argument, set to var, copy the first member of that thing, delete that eval result, return that copied new member
  */
  Sexpr* operand;
  Sexpr* getCarFromHere;
  Sexpr* resultSexpr;
  
  if(s == NULL){
    printf("\ncar operation on null Sexpr\n");
    return NULL;
  }
  
  /*eval first, eval second, compare and make result, delete those two evals, return result*/
  operand = get_inner(s);/*first inner is the operation*/
  if(operand == NULL){
    printf("\ncar function call on null inner which should be 'car'\n");
    return NULL;
  }
  operand = operand->next;
  if(operand == NULL){
    printf("\ntried to car a null sexpr\n");
    return NULL;
  }
  
  getCarFromHere = eval(operand, env);
  
  
  resultSexpr = copy_sexpr(get_inner(getCarFromHere));
  deleteSexpr(getCarFromHere);
  return resultSexpr;
}

Sexpr* cdr(Sexpr* s, Env* env){
  /*
  eval the argument, set to var, set its inner first to its inner second, delete that first, return that new thing
  */
  Sexpr* operand;
  Sexpr* removedCdr;
  Sexpr* resultSexpr;
  
  if(s == NULL){
    printf("\ncdr operation on null Sexpr\n");
    return NULL;
  }
  
  /*eval first, eval second, compare and make result, delete those two evals, return result*/
  operand = get_inner(s);/*first inner is the operation*/  
  if(operand == NULL){
    printf("\ncdr function call on null inner which should be 'cdr'\n");
    return NULL;
  }
  operand = operand->next;
  if(operand == NULL){
    printf("\ntried to cdr a null sexpr\n");
    return NULL;
  }
  
  resultSexpr = eval(operand, env);
  printf("\nresultSexpr first time in cdr\n");
  printSexpr(resultSexpr);
  removedCdr = get_inner(resultSexpr);
  
  resultSexpr->inner->next = get_inner(resultSexpr)->next;
  removedCdr->next = NULL;
  deleteSexpr(removedCdr);
  
  return resultSexpr;
}

Sexpr* cond(Sexpr* s, Env* env){
  Sexpr* operand;
  Sexpr* clause;
  Sexpr* predicate;
  Sexpr* predicate_value;
  Sexpr* expression;
  Sexpr* expression_result;
  
  if(s == NULL){
    printf("\ncond operation on null Sexpr\n");
    return NULL;
  }
  
  operand = get_inner(s);/*first inner is the operation*/  
  if(operand == NULL){
    printf("\ncond function call on null inner which should be 'cond'\n");
    return NULL;
  }
  
  /*while next not null, check if that one predicate evals to true then eval it's value*/
  clause = operand->next;
  while(clause != NULL){
    predicate = get_inner(clause);
    if(predicate == NULL){
      printf("\nNULL predicate in cond operation\n");
      return NULL;
    }
    
    predicate_value = eval(predicate, env);
    
    /*if predval == true then return its evaled expression (no copy, just return that eval since that's new anyway)*/    
    if(get_atom(predicate_value) != NULL && (!strcmp(get_atom(predicate_value), "True") || !strcmp(get_atom(predicate_value), "else"))){
      deleteSexpr(predicate_value);
      
      expression = predicate->next;
      expression_result = NULL;
      while(expression != NULL){
        deleteSexpr(expression_result);
        expression_result = eval(expression, env);
        expression = expression->next;
      }        
      
      return expression_result;
    }
    deleteSexpr(predicate_value);
    clause = clause->next;
  }
  
  printf("\ncond operation with no predicates evaluating to true, returning NULL\n");
  return NULL;
}

Sexpr* cons(Sexpr* s, Env* env){
  Sexpr* operator;
  Sexpr* first_eval;
  Sexpr* second_eval;
  Sexpr* result_sexpr;
  
  if(s == NULL){
    printf("\ncons operation on null Sexpr\n");
    return NULL;
  }
  
  operator = get_inner(s);/*first inner is the operation*/  
  if(operator == NULL){
    printf("\ncons function call on null inner which should be 'cons'\n");
    return NULL;
  }
  
  first_eval = eval(operator->next, env);
  /*printf("\nfirst eval:");
  printSexpr(first_eval);*/
  second_eval = eval(operator->next->next, env);
  /*printf("\nsecond eval:");
  printSexpr(second_eval);
  */
  result_sexpr = newSexpr();
  create_inner(result_sexpr);
  result_sexpr->inner->next = first_eval;
  first_eval->next = get_inner(second_eval);
  second_eval->inner->next = NULL;
  deleteSexpr(second_eval);
  
  return result_sexpr;
  
  /*eval first, eval second.  
  make new sexpr, set first inner to first evaled, set first evaled's next to first inner of second evaled
  make second outer evaled's inner point away to null, delete second outer evaled
  */
}

/*each call to eval means a new sexpr, so delete after it gets used*/
/*if sexpr isn't one passed in or the one to be returned, make sure it's deleted*/
/*don't delete the sexpr passed into the eval func (responsibility of outer)*/
/*all return values from eval should be assigned to a variable, not passed directly into a func, so can be deleted*/
/*don't directly return an input, to outer it should be considered different (i.e. outer could delete sexpr from an eval while not touching its argument)*/
Sexpr* eval(Sexpr* s, Env* env){
  Sexpr* op;
  Sexpr* lambda_arg_name;
  Sexpr* lambda_arg_value;
  Sexpr* lambda_sexpr;

  Sexpr* beginSexpr;
  Sexpr* beginSexprValue;
  Sexpr* if_sexpr;
  Env* innerEnv;
  Sexpr* result_sexpr;
  if(s == NULL){
    printf("\neval on NULL\n");
    return NULL;
  }
  
  
  if(get_atom(s) != NULL){
    if(is_int(get_atom(s)) || is_float(get_atom(s)))
      return copy_sexpr(s);/*may have to make this a copy of s, since outer should be deleting it*/
    else if(!strcmp(get_atom(s), "True") || !strcmp(get_atom(s), "False") || !strcmp(get_atom(s), "else")){
      return copy_sexpr(s);
    }
    else{
      return eval(findEnv(env, get_atom(s)), env->inner) ;/*?findEnv returns a copy?*/
    }
  }
  
  /*TODO NULL checks!*/
  op = get_inner(s);
  
  if(get_atom(get_inner(s)) != NULL){
    if(!strcmp(get_atom(op), "+"))
      return add(s, env);  

    else if(!strcmp(get_atom(op), "-"))
      return subtract(s, env);

    else if(!strcmp(get_atom(op), "*"))
      return multiply(s, env);

    else if(!strcmp(get_atom(op), "/"))
      return division(s, env);

    else if(!strcmp(get_atom(op), ">"))
      return greaterThan(s, env);

    else if(!strcmp(get_atom(op), "<"))
      return lessThan(s, env);

    else if(!strcmp(get_atom(op), "eq?"))
      return equal(s, env);
    /*else if(get_atom(op) != NULL && !strcmp(get_atom(op), "="))
      return equal(s, env);*/
    else if(!strcmp(get_atom(op), "atom?"))
      return  is_atom(s, env);

    else if(!strcmp(get_atom(op), "null?"))
      return is_null(s, env);

    else if(!strcmp(get_atom(op), "car"))
      return car(s, env);

    else if(!strcmp(get_atom(op), "cdr"))
      return cdr(s, env);

    else if(!strcmp(get_atom(op), "cond"))
      return cond(s, env);

    else if(!strcmp(get_atom(op), "cons"))
      return cons(s, env);

    else if(!strcmp(get_atom(op), "quote"))
      return copy_sexpr(op->next);

    else if(!strcmp(get_atom(op), "define")){/*only sets for current inner env, so could have another with a different value in outer env*/
      insertEnv(env, get_atom(op->next), op->next->next);
    }
    else if(!strcmp(get_atom(op), "set!")){/*set value for any environment, so set with inner and will find in outer and update that*/
      setEnv(env, get_atom(op->next), op->next->next);
    }
    else if(!strcmp(get_atom(op), "begin")){
      beginSexpr = op->next;
      beginSexprValue = NULL;
      while(beginSexpr){
        deleteSexpr(beginSexprValue);
        beginSexprValue = eval(beginSexpr, env);
        beginSexpr = beginSexpr->next;
      }
      return beginSexprValue;
    }
    else if(!strcmp(get_atom(op), "if")){
      if_sexpr = eval(op->next, env);
      if(if_sexpr != NULL && get_atom(if_sexpr) != NULL && !strcmp(get_atom(if_sexpr), "True")){  
        deleteSexpr(if_sexpr);
        return eval(op->next->next, env);
      }
      else{     
        deleteSexpr(if_sexpr);
        return eval(op->next->next->next, env);
      }
    }
    else if(!strcmp(get_atom(op), "lambda")){
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
      /*deleteSexpr(lambda_sexpr);
      return result_sexpr;*/
    }
  }
  return NULL;
}