#include <stdio.h>

typedef struct node {
    char *word;
    int height;
    struct node *left;
    struct node *right;
} node;

/*
 * Adds a word into the avl tree
 */
int avl_insert(char* word, node **tree);

/**
 * Prints the contents of the avl tree
 */
void avl_preOrder(node *tree);

/**
 * Returns 1 if keyword can is found in the avl tree. Returns 0 if otherwise.
 */
int avl_search(node *tree, char* keyword);
