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
  printf("%s = %s\n", tree->node, tree->value);
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
void insertNode(char* node, char* value){
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
  
  
  
  readline(fopen("testreadline.txt", "r"), EOF, testReadFromFile);
  assert(strcmp(test_read_buf, test_read_val) == 0 && "test readline from file");
  printf("\ntesting reading stdin, type something and make sure it spits it back out\n");
  readline(stdin, '\n', testTokenize);
  
  tokenizeStr(s);
  printf("\nprinted tokens should look like:\n(->one->(->two->)->three->four->)->NULL\n");
  printToken(getHeadToken()->next);
  printf("\nprinted sexpr should look like:\n( one ->( two -> NIL )-> three -> four -> NIL )-> NIL\n"); 
  printSexpr(parse(&(getHeadToken()->next)));
  assert(getTailToken() != getHeadToken() && "head and tail should be different when list has tokens");
  deleteNextToken(getHeadToken());
  assert(getHeadToken()->next == NULL && "head token should be null after delete");
  assert(getTailToken() == getHeadToken() && "head and tail should be the same in empty list that you get after deleting tokens");
  
  e = newEnv(NULL);
  assert(findEnv(e, "not there") == NULL && "finding node in an empty env with no inner (should  be null)");
  insertEnv(e, "node1", "value1");
  assert(strcmp(findEnv(e, "node1"), "value1") == 0 && "finding node in env after inserting one (should be 'node1','value1')");
  assert(findEnv(e, "still not there") == NULL && "finding non-existent node in env with one in it (should be null)");
  insertEnv(e, "node2", "value2");
  assert(strcmp(findEnv(e, "node2"), "value2") == 0 && "finding another node in env after another insert (should be 'value2')");
  outerEnv = newEnv(e);
  assert(findEnv(outerEnv, "nope") == NULL && "finding node in outer env that isn't in either env (should be null)");
  assert(strcmp(findEnv(outerEnv, "node1"), "value1") == 0 && "finding node in outer env that is actually in inner env (should be 'value1')");
  insertEnv(outerEnv, "node3", "value3");
  assert(findEnv(outerEnv, "nah") == NULL && "finding node in outer env that isn't in either (should be null)");
  assert(strcmp(findEnv(outerEnv, "node2"), "value2") == 0 && "finding node in outer env that is actually in inner env (should be 'value2')");
  assert(strcmp(findEnv(outerEnv, "node3"), "value3") == 0 && "findnig node in outer env that should be in outer (should be 'value3')");


  
  tmpNode="5";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  tmpVal="5val";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  insertNode(five, fiveVal);
  
  tmpNode="3";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  tmpVal="3val";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  insertNode(five, fiveVal);
  
  tmpNode="7";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  tmpVal="7val";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  insertNode(five, fiveVal);
  
  tmpNode="4";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  tmpVal="4val";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  insertNode(five, fiveVal);
  
  tmpNode="8";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  tmpVal="8val";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  insertNode(five, fiveVal);
  
  tmpNode="6";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  tmpVal="6val";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  insertNode(five, fiveVal);
  
  assert(strcmp(findNode("8")->value, "8val") == 0 && "node 8 is original value before overwrite");
  
  tmpNode = "8";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  tmpVal = "another 8";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  insertNode(five, fiveVal);
  assert(strcmp(findNode("8")->value, "another 8") == 0 && "node 8 is overwritten value");
  
  assert(strcmp(findNode("6")->value, "6val") == 0 && "find 6, should be there");
  
  assert(findNode("9") == NULL && "find 9 (not there)");
  
  
  noMin = deleteMin(testRoot, &min);
  assert(find(noMin, "3") == NULL && "tree after deleting min (3) should not have it any more");
  assert(strcmp(find(noMin, "4")->value, "4val") == 0 && "tree after deleting min (3) should still have a child of min (4)");
  assert(strcmp(find(min, "3")->value, "3val") == 0 && "the removed min tree should have the removed min node (3)");
  assert(strcmp(findNode("7")->value, "7val") == 0 && "the test tree should have node 7 before removal");
  assert(find(removeTreeNode(testRoot, "7"), "7") == NULL && "test tree should not have removed node");
  deleteTree(testRoot);
  printf("\n%f\n", atof("dang"));  
  

  assert(!is_int("") && "is_int should be false for empty string");
  assert(is_int("1") && "is_int should be true for '1'");
  assert(is_int("987") && "is_int should be true for '987'");
  assert(!is_int("a") && "is_int should be false for 'a'");
  assert(!is_int("a1") && "is_int should be false for 'a1'");
  assert(!is_int("1a") && "is_int should be false for '1a'");
  
  

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
  
  
  tokenizeStr("");
  /*head is null at this point, so can't do this*/
  /*printToken(getHeadToken()->next);*/
  
  tokenizeStr("1");
  printToken(getHeadToken()->next);
  tokenizeStr("1.0");
  printToken(getHeadToken()->next);
  tokenizeStr("(+ 1 3)");
  printToken(getHeadToken()->next);
  printSexpr(parse(&getHeadToken()->next));
  tokenizeStr("(+ (+ 1 2) 3)");
  printToken(getHeadToken()->next);
  printSexpr(eval(parse(&getHeadToken()->next)));
  return  0;
}
