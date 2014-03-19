#ifndef TREE
#define TREE

typedef struct tree Tree;

struct tree{
  char* node;
  char* value;
  Tree* left;/*left is less*/
  Tree* right;/*right is greater than*/
};

Tree* getRoot();
void insert(char* node, char* value);
Tree* find(char* node);
Tree* deleteMin(Tree* subroot, Tree** min);
void deleteTree(Tree* tree);

#endif /*TREE*/
