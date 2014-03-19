#include <stdio.h>
#include <string.h>/*for strcmp test, strlen, str copy?*/
#include <stdlib.h>/*for malloc()*/
#include "tree.h"

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

int main(void){
  /*5, 3, 7, 4, 8, 6*/
  char* tmpNode, *five, *tmpVal, *fiveVal;
  Tree* min;
  
  tmpNode="5";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  printf("%s\n", five);
  tmpVal="5val";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  printf("%s\n", fiveVal);
  insert(five, fiveVal);
  
  tmpNode="3";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  printf("%s\n", five);
  tmpVal="3val";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  printf("%s\n", fiveVal);
  insert(five, fiveVal);
  
  tmpNode="7";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  printf("%s\n", five);
  tmpVal="7val";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  printf("%s\n", fiveVal);
  insert(five, fiveVal);
  
  tmpNode="4";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  printf("%s\n", five);
  tmpVal="4val";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  printf("%s\n", fiveVal);
  insert(five, fiveVal);
  
  tmpNode="8";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  printf("%s\n", five);
  tmpVal="8val";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  printf("%s\n", fiveVal);
  insert(five, fiveVal);
  
  tmpNode="6";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  printf("%s\n", five);
  tmpVal="6val";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  printf("%s\n", fiveVal);
  insert(five, fiveVal);
  printTree(getRoot());
  
  tmpNode = "8";
  five=(char*)malloc(strlen(tmpNode)+1);
  strcpy(five, tmpNode);
  printf("copy node %s\n", five);
  tmpVal = "another 8";
  fiveVal=(char*)malloc(strlen(tmpVal)+1);
  strcpy(fiveVal, tmpVal);
  printf("%s\n", fiveVal);
  insert(five, fiveVal);
  printTree(getRoot());
  
  printf("\n\nfind 6\n\n");
  printTree(find("6"));
  
  printf("\n\nfind 9 (not there)\n\n");
  printTree(find("9"));
  
  printf("\n\ndelete min (3)\n\n");
  printTree(deleteMin(getRoot(), &min));
  printTree(min);
  printf("\n\nremove 7\n\n");
  remove("7");
  printTree(getRoot());
  deleteTree(getRoot());
 
  return 0;
}
