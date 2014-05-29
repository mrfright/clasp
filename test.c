#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "readline.h"

#include <stdlib.h>
#include "token.h"
#include "parse.h"
#include "env.h"

#include "tree.h"

#include "eval.h"
#include "sexpr.h"

char test_read_buf[100];
void testReadFromFile(char c){
  static int test_read_buf_ind = 0;
  test_read_buf[test_read_buf_ind++] = c;
  test_read_buf[test_read_buf_ind] = 0;/*making sure it's null terminated*/
}

void testTokenize(char c){
  putchar(c);
}




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




void printTree(Tree* tree){
  if(tree == NULL){
    printf("NULL\n");
    return;
  }
  printf("%s = ", tree->node);
  printSexpr(tree->value);
  printf("\n");
  printf("%s left\n", tree->node);
  if(tree->left == NULL)
    printf("left is null\n");
  else
    printTree(tree->left);
  printf("%s right\n", tree->node);
  if(tree->right == NULL)
    printf("right is null\n");
  else
    printTree(tree->right);
  printf("%s done\n", tree->node);
}

Tree* testRoot = NULL;
void insertNode(char* node, Sexpr* value){
  testRoot =  insert(testRoot, node, value);
}

Tree* findNode(char* node){
  return find(testRoot, node);
}



int main(void){
  char test_read_val[] =  "test read line\r\nanother line\r\n\r\n";
  
  char *s="(one (two)three four) ";
  char c;
  Env *e, *outerEnv;
  
  
  /*5, 3, 7, 4, 8, 6*/
  char* tmpNode, *five, *tmpVal, *fiveVal;
  Tree* min;
  Tree* noMin;
  Token* tokHead;
  Sexpr* sexpr;
  Env* testEnv;
  
  
  readline(fopen("testreadline.txt", "r"), EOF, testReadFromFile);
  assert(strcmp(test_read_buf, test_read_val) == 0 && "test readline from file");
  printf("\ntesting reading stdin, type something and make sure it spits it back out\n");
  readline(stdin, '\n', testTokenize);
  
  tokHead = tokenizeStr(s);
  printf("\nprinted tokens should look like:\n(->one->(->two->)->three->four->)->NULL\n");
  printToken(tokHead->next);
  printf("\nprinted sexpr should look like:\n( one ->( two -> NIL )-> three -> four -> NIL )-> NIL\n"); 
  sexpr = parseStr(s);
  printSexpr(sexpr);
  deleteSexpr(sexpr);
             
  
  e = newEnv(NULL);
  assert(findEnv(e, "not there") == NULL && "finding node in an empty env with no inner (should  be null)");
  
  sexpr = parseStr("value1");
  insertEnv(e, "node1", sexpr);  
  assert(strcmp(findEnv(e, "node1")->atom, "value1") == 0 && "finding node in env after inserting one (should be 'node1','value1')");
  assert(findEnv(e, "still not there") == NULL && "finding non-existent node in env with one in it (should be null)");
  sexpr = parseStr("value2");
  insertEnv(e, "node2", sexpr);/*"value2");*/
  assert(strcmp(findEnv(e, "node2")->atom, "value2") == 0 && "finding another node in env after another insert (should be 'value2')");
  outerEnv = newEnv(e);
  assert(findEnv(outerEnv, "nope") == NULL && "finding node in outer env that isn't in either env (should be null)");
  assert(strcmp(findEnv(outerEnv, "node1")->atom, "value1") == 0 && "finding node in outer env that is actually in inner env (should be 'value1')");
  sexpr = parseStr("value3");
  insertEnv(outerEnv, "node3", sexpr);
  assert(findEnv(outerEnv, "nah") == NULL && "finding node in outer env that isn't in either (should be null)");
  assert(strcmp(findEnv(outerEnv, "node2")->atom, "value2") == 0 && "finding node in outer env that is actually in inner env (should be 'value2')");
  assert(strcmp(findEnv(outerEnv, "node3")->atom, "value3") == 0 && "findnig node in outer env that should be in outer (should be 'value3')");


  
  tmpNode="5";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  insertNode(five, parseStr("5val"));
  
  tmpNode="3";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  insertNode(five, parseStr("3val"));
  
  tmpNode="7";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  insertNode(five, parseStr("7val"));
  
  tmpNode="4";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  insertNode(five, parseStr("4val"));
  
  tmpNode="8";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  insertNode(five, parseStr("8val"));
  
  tmpNode="6";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  tmpVal="6val";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  insertNode(five, parseStr("6val"));
  
  assert(strcmp(findNode("8")->value->atom, "8val") == 0 && "node 8 is original value before overwrite");
  
  tmpNode = "8";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  insertNode(five, parseStr("another8"));
  assert(strcmp(findNode("8")->value->atom, "another8") == 0 && "node 8 is overwritten value");
  
  assert(strcmp(findNode("6")->value->atom, "6val") == 0 && "find 6, should be there");
  
  assert(findNode("9") == NULL && "find 9 (not there)");
  
  
  noMin = deleteMin(testRoot, &min);
  assert(find(noMin, "3") == NULL && "tree after deleting min (3) should not have it any more");
  assert(strcmp(find(noMin, "4")->value->atom, "4val") == 0 && "tree after deleting min (3) should still have a child of min (4)");
  assert(strcmp(find(min, "3")->value->atom, "3val") == 0 && "the removed min tree should have the removed min node (3)");
  assert(strcmp(findNode("7")->value->atom, "7val") == 0 && "the test tree should have node 7 before removal");
  assert(find(removeTreeNode(testRoot, "7"), "7") == NULL && "test tree should not have removed node");
  deleteTree(testRoot);
  printf("\n%f\n", atof("dang"));   
  

  assert(!is_int("") && "is_int should be false for empty string");
  assert(is_int("1") && "is_int should be true for '1'");
  assert(is_int("987") && "is_int should be true for '987'");
  assert(!is_int("a") && "is_int should be false for 'a'");
  assert(!is_int("a1") && "is_int should be false for 'a1'");
  assert(!is_int("1a") && "is_int should be false for '1a'");
  assert(is_int("-2") && "is_int should be true for '-2'");
  
  

  assert(!is_float(".0") && "is_float should be false for '.0'");
  assert(!is_float(".") && "is_float should be false for '.'");
  assert(!is_float("0.") && "is_float should be false for '0.'");
  assert(!is_float("") && "is_float should be false for empty string");
  assert(is_float("0.0") && "is_float should be true for '0.0'");
  assert(!is_float("a.0") && "is_float should be false for 'a.0'");
  assert(!is_float("a.") && "is_float should be false for 'a.'");
  assert(!is_float(".a") && "is_float should be false for '.a'");
  assert(!is_float("a.a") && "is_float should be false for 'a.a'");
  assert(!is_float("a") && "is_float should be false for 'a'");
  assert(!is_float("a1") && "is_float should be false for 'a1'");
  assert(!is_float("1a") && "is_float should be false for '1a'");
  assert(is_float("-1.0") && "is_float should be true for '-1.0'");
  
  
  
  
  /*head is null at this point, so can't do this*/
  /*printToken(tokenizeStr("")->next);*/
  
  
  printToken(tokenizeStr("1")->next);
  printToken( tokenizeStr("1.0")->next);

  printSexpr(parseStr("(+ 1 3)"));
  printf("\nshould be 6\n");
  e = newEnv(NULL);
  printSexpr(eval(parseStr("(+ (+ 1 2) 3)"), e));
  printf("\nshould be 9\n");
  printSexpr(eval(parseStr("(* (+ (- 2 1) 2) (/ 12 4))"), e));
  printf("\nshould be False\n");
  printSexpr(eval(parseStr("(> (+ (- 2 1) 2) (/ 12 4))"), e));
  printf("\nshould be False\n");
  printSexpr(eval(parseStr("(>  (/ 12 4) (+ (- 2 1) 2))"), e));
  printf("\nshould be False\n");
  printSexpr(eval(parseStr("(< (+ (- 2 1) 2) (/ 12 4))"), e));
  printf("\nshould be false\n");
  printSexpr(eval(parseStr("(<  (/ 12 4) (+ (- 2 1) 2))"), e));
  printf("\n should print out '(+ (- 2 1) 2)'\n");
  printSexpr(eval(parseStr("(quote (+ (- 2 1) 2))"), e));
  
  printSexpr(eval(parseStr("(* 0.5 1.0)"), e));
  
  printf("\nshould print '(lambda (a b) (+ a b))'\n");
  printSexpr(eval(parseStr("(lambda (a b) (+ a b))"), e));
  
  printSexpr(eval(parseStr("((lambda (a b) (+ a b)) 5 6)"), e));
  eval(parseStr("(define x 3)"), e);
  printf("\ndefined x as 3, should print 3\n");
  printSexpr(eval(parseStr("x"), e));
  eval(parseStr("(define add (lambda (a b) (+ a b)))"), e);
  printf("\ndefined add as +, should print result of 5+7\n");
  printSexpr(eval(parseStr("(add 5 7)"), e));
  eval(parseStr("(set! add (lambda (a b) (- a b)))"), e);
  printf("\n should set add to instead do -, trying (add 7 5)\n");
  printSexpr(eval(parseStr("(add 7 5)"), e));
  
  printf("\ntesting begin, should end in 5\n");
  printSexpr(eval(parseStr("(begin (- 3 2) (* 3 2) (+ 3 2))"), e));
  
  
  eval(parseStr("(define pi 3)"), e);
  printf("\nshould be outer pi=3\n");
  printSexpr(eval(parseStr("pi"), e)); 
  eval(parseStr("(define area (lambda (r) (begin (define pi 3.14) (* pi (* r r)))))"), e);
  printf("\nshould eval area 1 as 3.14\n");
  printSexpr(eval(parseStr("(area 1)"), e));
  printf("\nshould still have outer pi=3\n");
  printSexpr(eval(parseStr("pi"), e));
  
  eval(parseStr("(define abs (lambda (x) (if (> x 0) x (- 0 x))))"), e);
  printf("\ntaking abs of -2 and 2, both should be 2\n");
  printSexpr(eval(parseStr("(abs -2)"), e));
  printSexpr(eval(parseStr("(abs 2)"), e));
  
  printf("\ntrying Newton's method...\n");
  eval(parseStr("(define sqrt (lambda (x) (sqrt-iter 1.0 x)))"), e);
  eval(parseStr("(define sqrt-iter (lambda (guess x) (if (good-enough? guess x) guess (sqrt-iter (improve guess x) x))))"), e);
  eval(parseStr("(define good-enough? (lambda (guess x) (< (abs (- x (square guess))) 0.00001)))"), e);
  eval(parseStr("(define square (lambda (x) (* x x)))"), e);
  eval(parseStr("(define improve (lambda (guess x) (average guess (/ x guess))))"), e);
  eval(parseStr("(define average (lambda (x y) (* 0.5 (+ x y))))"), e);
  sexpr = eval(parseStr("(sqrt 2.0)"), e);
  printSexpr(sexpr);
  /*eval(parseStr(""), e);*/

  
  
  return  0;
}
