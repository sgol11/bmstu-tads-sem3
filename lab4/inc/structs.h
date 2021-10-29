#ifndef __STRUCTS__H__
#define __STRUCTS__H__

#include "general.h"

#define MAX_STACK_SIZE 100

typedef struct
{
    char data[MAX_STACK_SIZE];
    int cur_size;
} arr_stack_t;

typedef struct list_stack
{
    int value;
    int index;
    struct list_stack *prev;
} list_stack_t;

typedef struct
{
    size_t *arr;
    int len;
} free_areas_t;

#endif