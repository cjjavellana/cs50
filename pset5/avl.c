#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "avl.h"

static int height(node *n);
static int getBalance(node *n);
static int max(int a, int b);
static void rotateLeft(node **n);
static void rotateRight(node **n);

/**
 * Returns 1 if keyword can is found in the avl tree. Returns 0 if otherwise.
 */
int avl_search(node *tree, const char* keyword)
{
    if (tree == NULL)
    {
        return 0;
    }

    if (strcasecmp(tree->word, keyword) == 0) 
    {
        return 1;
    }
    else if (strcasecmp(keyword, tree->word) < 0)
    {
        return avl_search(tree->left, keyword);
    }
    else 
    {
        return avl_search(tree->right, keyword);
    }
}

/**
 * Adds a word into the word list binary tree
 */
int avl_insert(char* word, node **tree)
{
    if (*tree == NULL)
    {
        *tree = malloc(sizeof(node));
        if (*tree == NULL)
        {
            return 0;
        }
        
        (*tree)->word = malloc(sizeof(char) * strlen(word) + 1);
        strcpy((*tree)->word, word);
        (*tree)->left = NULL;
        (*tree)->right = NULL;
        (*tree)->height = 1;
    
        return 1;
    }
    
    if (strcmp(word, (*tree)->word) < 0)
    {
        avl_insert(word, &(*tree)->left);
    }
    else if (strcmp(word, (*tree)->word) > 0)
    {
        avl_insert(word, &(*tree)->right);
    }

    (*tree)->height = max(height((*tree)->left), height((*tree)->right)) + 1;
    
    int balance = getBalance(*tree);
    if (balance > 1 && strcmp(word, (*tree)->left->word) < 0)
    {
        rotateRight(tree);
    } else if (balance < -1 && strcmp(word, (*tree)->right->word) >  0)
    {
        rotateLeft(tree);
    } 
    else if (balance > 1 && strcmp(word, (*tree)->left->word) > 0)
    {
        rotateLeft(&(*tree)->left);
        rotateRight(tree);
    } 
    else if (balance < -1 && strcmp(word, (*tree)->right->word) < 0)
    {
        rotateRight(&(*tree)->right);
        rotateLeft(tree);
    }

    return 1;
}

int avl_unload(node *tree) 
{
    if (tree != NULL)
    {
        avl_unload(tree->left);
        avl_unload(tree->right);
        free(tree->word);
        free(tree);
        return 1;
    }

    return 0;
}

static void rotateLeft(node **n)
{
    node *n1 = (*n)->right;
    node *n2 = n1->left;

    n1->left = *n;
    (*n)->right = n2;

    (*n)->height = max(height((*n)->left), height((*n)->right)) + 1;
    n1->height = max(height(n1->left), height(n1->right)) + 1;
    
    // assign new root
    *n = n1;
}

static void rotateRight(node **n)
{
    node *n1 = (*n)->left;
    node *n2 = n1->right;

    n1->right = *n;
    (*n)->left = n2;

    (*n)->height = max(height((*n)->left), height((*n)->right)) + 1;
    n1->height = max(height(n1->left), height(n1->right)) + 1;

    // assign new root
    *n = n1;
}

static int height(node *n)
{
    if (n == NULL)
    {
        return 0;
    }

    return n->height;
}

static int getBalance(node* n)
{
    if (n == NULL)
    {
        return 0;
    }

    return height(n->left) - height(n->right);
}

static int max(int a, int b)
{
    return (a > b) ? a : b;
}
