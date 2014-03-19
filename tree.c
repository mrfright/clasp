#include <stdlib.h>/*for NULL*/
#include <string.h>/*for strcmp*/
#include "tree.h"

static Tree* root=NULL;

Tree* getRoot(){
  return root;
}

Tree* insertHelp(Tree* subroot, char* node, char* value){
  if(subroot == NULL){/*insert here*/
    subroot = malloc(sizeof(Tree));
    subroot->node = node;
    subroot->value = value;
    return subroot;
  }
  if(strcmp(node, subroot->node)==0){/*found node, just update*/
    free(subroot->value);
    subroot->value=value;
    return subroot;
  }
  if(strcmp(node, subroot->node)<0)
    subroot->left = insertHelp(subroot->left, node, value);
  else
    subroot->right = insertHelp(subroot->right, node, value);

  return subroot;  
}
void insert(char* node, char* value){
  root = insertHelp(root, node, value);
}

static Tree* findHelp(Tree* subroot, char* node){ 
  if(subroot == NULL)/*not found, return null*/
    return NULL;
  if(strcmp(node, subroot->node)<0)
    return findHelp(subroot->left, node);
  if(strcmp(node, subroot->node)>0)
    return findHelp(subroot->right, node);
  /*else found, return this*/
  return subroot;
}

Tree* find(char* node){
  return findHelp(root, node);
}

static Tree* removeHelp(Tree* subroot, char* node){
  Tree* temp;
  if(subroot == NULL) return NULL;/*node not in tree*/
  else if(strcmp(node, subroot->node)<0)
    subroot->left = removeHelp(subroot->left, node);
  else if(strcmp(node, subroot->node)>0)
    subroot->right = removeHelp(subroot->right, node);
  else{/*found node to remove*/
    temp = subroot;
    if(subroot->left == NULL)/*no left, set to right*/
      subroot = subroot->right;
    else if(subroot->right == NULL)/*no right, set to left*/
      subroot = subroot->left;
    else{/*has a left and right, set to min of right*/
      subroot->right = deleteMin(subroot->right, &temp);
       free(subroot->node);
       subroot->node = temp->node;
       free(subroot->value);
       subroot->value = temp->value;
       free(temp);
    }
  }
  return subroot;
}

void remove(char* node){
  root = removeHelp(root, node);
}

void deleteNode(Tree* tree){
  if(tree != NULL){
    free(tree->node);
    free(tree->value);
    free(tree);
  }
}

void deleteTree(Tree* tree){
  if(tree != NULL){
    deleteTree(tree->left);
    deleteTree(tree->right);
    deleteNode(tree);
  }
}

Tree* deleteMin(Tree* subroot, Tree** min){
  if(subroot->left == NULL){/*found min*/
    *min=subroot;
    return subroot->right;
  }
  else{
    subroot->left = deleteMin(subroot->left, min);
    return subroot;
  }
}
