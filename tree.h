#ifndef TREE
#define TREE
#include "sexpr.h"

typedef struct tree Tree;

struct tree{
  char* node;
  Sexpr* value;
  Tree* left;/*left is less*/
  Tree* right;/*right is greater than*/
};


Tree* insert(Tree* subroot, char* node, Sexpr* value);
Tree* find(Tree* root, char* node);
Tree* deleteMin(Tree* subroot, Tree** min);
void deleteTree(Tree* tree);
Tree* removeTreeNode(Tree* subroot, char* node);

#endif /*TREE*/
