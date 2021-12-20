#ifndef __STRUCTS__H__
#define __STRUCTS__H__

#include "general.h"

typedef struct tree_node 
{
    char *data;
    unsigned int height;
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

typedef struct hash
{
    char data[MAX_WORD_LEN];
    struct hash *next;
} hash_t;

typedef struct hash_table
{
    int size;
    hash_t **list;
} hash_table_t;

#endif