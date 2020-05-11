#include <stdlib.h>
#include "tree.h"

EVIL_TREE my_tree_init_default(int length) {
  Evil_tree* pMy_tree = (Evil_tree*)malloc(sizeof(Evil_tree));
  if (pMy_tree == NULL) {
    return NULL;
  }
  pMy_tree->headNode = NULL;
  return pMy_tree;
}


GENERIC_VECTOR my_tree_get_largest_bin(EVIL_TREE hMy_tree, FILE* fp1, int toPrint) {
  Evil_tree* pMy_tree = (Evil_tree*)hMy_tree;
  GENERIC_VECTOR return_vector = NULL;
  GENERIC_VECTOR temp;
  int i;
  temp = find_max_bin(pMy_tree->headNode, fp1, toPrint);
  return_vector = generic_vector_init_default(my_string_assignment, my_string_destroy);
  for (i = 0; i < generic_vector_size(temp); i++) {
    generic_vector_push_back(return_vector, generic_vector_at(temp, i));
  }
  return return_vector;
}

GENERIC_VECTOR find_max_bin(Node* headNode, FILE* fp1, int toPrint) {
  Generic_vector* temp = NULL;
    int elements_in_currentNode;
    int something_changed = 0;
    if (headNode != NULL) {
      elements_in_currentNode = generic_vector_size(headNode->nodeWords);
      // assumed to be the root at first.
      if (headNode->leftChild != NULL) {
        temp = find_max_bin(headNode->leftChild, fp1, toPrint);
        if (temp == NULL || generic_vector_size(temp) < generic_vector_size(headNode->nodeWords)) {
          // fprintf(fp1,("First\n");
          temp = headNode->nodeWords;
        }
      }
      if (headNode->rightChild != NULL) {
        temp = find_max_bin(headNode->rightChild, fp1, toPrint);
        if (temp == NULL || generic_vector_size(temp) < generic_vector_size(headNode->nodeWords)) {
          // fprintf(fp1,("Second\n");
          temp = headNode->nodeWords;
        }
      }
      if (temp == NULL || generic_vector_size(temp) < generic_vector_size(headNode->nodeWords)) {
        // fprintf(fp1,("Third\n");
        temp = headNode->nodeWords;
      }
    }
  if (toPrint) {
    my_string_insertion(headNode->key, fp1);
    fprintf(fp1," %d\n", generic_vector_size(headNode->nodeWords));
  }
  return temp;
}

Status my_tree_add_item(EVIL_TREE hMy_tree, MY_STRING key, MY_STRING word) {
  Evil_tree* pMy_tree = (Evil_tree*)hMy_tree;
  if (pMy_tree->headNode == NULL) {
    pMy_tree->headNode = (Node*)malloc(sizeof(Node));
    if (pMy_tree->headNode == NULL) {
      return FAILURE;
    }
      pMy_tree->headNode->leftChild = NULL;
      pMy_tree->headNode->rightChild = NULL;
      pMy_tree->headNode->key = my_string_init_c_string(my_string_c_str(key));
      // if only C had overloaded functions, I totally would make another init that can take arguments.
      // (Yes I know I could just make a function, but this works too) An overloaded "constructor" would
      // just look a lot cleaner
      pMy_tree->headNode->nodeWords = generic_vector_init_default(my_string_assignment, my_string_destroy);
      generic_vector_push_back(pMy_tree->headNode->nodeWords, word);
  } else {
    switch (my_string_compare(pMy_tree->headNode->key, key)) {
    case 0:generic_vector_push_back(pMy_tree->headNode->nodeWords, word); break;
    case 1: my_tree_add_item(&(pMy_tree->headNode->rightChild), key, word); break;
    case -1: my_tree_add_item(&(pMy_tree->headNode->leftChild), key, word); break;
    default: return FAILURE; break;
    }
  }
  return SUCCESS;
}

void my_tree_destroy(EVIL_TREE* phMy_tree) {
  Evil_tree* pMy_tree = (Evil_tree*)*phMy_tree;
  if (pMy_tree->headNode != NULL) {
    if (pMy_tree->headNode->leftChild != NULL) {
      my_tree_destroy_individual_nodes(pMy_tree->headNode->leftChild);
    }
    if (pMy_tree->headNode->rightChild != NULL) {
      my_tree_destroy_individual_nodes(pMy_tree->headNode->rightChild);
    }
    my_string_destroy(&(pMy_tree->headNode->key));
    generic_vector_destroy(&(pMy_tree->headNode->nodeWords));
    free(pMy_tree->headNode);
  }
  free(pMy_tree); phMy_tree = NULL;
}

void my_tree_destroy_individual_nodes(Node* myNode) {
  if (myNode != NULL) {
  if (myNode->leftChild != NULL) {
      my_tree_destroy_individual_nodes(myNode->leftChild);
  }
    if (myNode->rightChild != NULL) {
      my_tree_destroy_individual_nodes(myNode->rightChild);
    }
    my_string_destroy(&myNode->key);
    generic_vector_destroy(&myNode->nodeWords);
    free(myNode);
  }
}
