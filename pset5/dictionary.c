/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#define _XOPEN_SOURCE 700

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "dictionary.h"

node *wordlist;

// internal functions

static int height(node *n);
static int getBalance(node *n);
static int max(int a, int b);


/**
 * Adds a word into the word list binary tree
 */
int insert(char* word, node **tree)
{
    if (*tree == NULL)
    {
        *tree = malloc(sizeof(node));
        if (*tree == NULL)
        {
            return 0;
        }
        
        (*tree)->word = malloc(sizeof(char) * strlen(word));
        strcpy((*tree)->word, word);
        (*tree)->left = NULL;
        (*tree)->right = NULL;
        (*tree)->height = 1;

        return 1;
    }
    else if (strcmp(word, (*tree)->word) < 0)
    {
        insert(word, &(*tree)->left);
    }
    else if (strcmp(word, (*tree)->word) > 0)
    {
        insert(word, &(*tree)->right);
    }

    (*tree)->height = max(height((*tree)->left), height((*tree)->right)) + 1;
    
    int balance = getBalance(*tree);
    
    if (balance > 1 && strcmp(word, (*tree)->left->word) < 0)
    {
        
    }

    if (balance < -1 && strcmp(word, (*tree)->right->word) >  0)
    {
        
    }

    return 1;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Unable to open file %s\n", dictionary);
        fclose(fp);
        return false;
    }

    char *line = NULL;
    size_t read = 0, len = 0;
    while((read = getline(&line, &len, fp)) != -1)
    {
        insert(line, &wordlist); 
    }
   
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
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

