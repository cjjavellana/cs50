#include <stdio.h>
#include <stdlib.h>

typedef struct HashTableNode {
    int hashCode;               /** Determines which bucket the node goes **/
    char *key;                  /** The node's key **/
    void *data;                 /** The node's data **/
    struct HashTableNode *children;    /** The node's children nodes **/
} HashTableNode;

typedef struct {
    HashTableNode *root;
} HashTable;

/**
 * Returns a pointer to a new HashTable
 */
HashTable *newHashTable();

/**
 * Returns a pointer to a new HashTableNode
 */
HashTableNode *newHashTableNode();

/**
 * Traverses the entire tree and effectively freeing each and every single node
 */
void destroyHashTable(HashTable *hashTable);

/**
 * Returns the data pointed to by key
 */
void *get(const HashTable *hashTable, const char *key);

/**
 * Stores the key-data pair into the HashTable
 */
void put(HashTable *hashTable, const char *key, void *data);

int main(int argc, char *argv[])
{
    return 0;
}

HashTable *newHashTable() {
    HashTable *hashTable = malloc(sizeof(HashTable));
    hashTable->root = NULL;

    return hashTable;
}
