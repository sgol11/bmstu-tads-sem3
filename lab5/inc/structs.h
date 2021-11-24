#ifndef __STRUCTS__H__
#define __STRUCTS__H__

#include "general.h"

#define MAX_QUEUE_SIZE 1000

typedef struct
{
    int data[MAX_QUEUE_SIZE];
    int head_idx;
    int tail_idx;
} array_queue_t;

typedef struct node
{
    int data;
    struct node *next;
} node_t;

typedef struct list_queue_t
{
    node_t *head;
    node_t *tail;
} list_queue_t;

typedef struct
{
    size_t address[MAX_QUEUE_SIZE];
    int size;
} free_areas_t;

#endif