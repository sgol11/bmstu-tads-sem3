#ifndef __STRUCTS__H__
#define __STRUCTS__H__

#include "general.h"

typedef struct
{
    int rows;
    int columns;
    int **data;
} matrix_std_t;

typedef struct node
{
    int index;
    struct node *next;
} node_t;

typedef struct
{
    int rows;
    int columns;
    int nn_cnt;
    int *A;     
    int *IA;
    node_t JA;
} matrix_sparse_t;

#endif