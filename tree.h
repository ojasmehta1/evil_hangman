#ifndef TREE_H_
#define TREE_H_

#include "my_string.h"
#include "generic.h"

typedef void* TREE;

typedef struct node Node;

struct node {
  Node* leftChild;
  Node* rightChild;
  Node* parent;
  MY_STRING key;
  GENERIC_VECTOR nodeWords;
};

struct tree {
  Node* headNode;
};
typedef struct tree tree;

TREE my_tree_init_default();
Status my_tree_add_item(TREE hMy_tree, MY_STRING key, MY_STRING word);
void my_tree_destroy(TREE* phMy_tree);
void my_tree_destroy_individual_nodes(Node* myNode);
GENERIC_VECTOR my_tree_get_largest_bin(TREE hMy_tree, FILE* fp1, int toPrint);
GENERIC_VECTOR my_tree_get_largest_bin(TREE hMy_tree, FILE* fp1, int toPrint);
GENERIC_VECTOR find_max_bin(Node* headNode, FILE* fp1, int toPrint);

#endif  // TREE_H_
