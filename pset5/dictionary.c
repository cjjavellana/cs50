/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 *
 * Stores the words in an AVL tree to improve search efficiency.
 * AVL tree implementation inspired by http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 ***************************************************************************/
#define _XOPEN_SOURCE 700

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "dictionary.h"
#include "avl.h"

node *wordlist;
int wordcount = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    return (avl_search(wordlist, word) == 1) ? true : false;
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
        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) -1] = '\0';
        }

        avl_insert(line, &wordlist); 
        wordcount++;
    }
   
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordcount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
