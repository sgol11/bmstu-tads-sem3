#ifndef __STRUCTS__H__
#define __STRUCTS__H__

#include "general.h"

typedef enum { FALSE, TRUE } mybool;

typedef struct
{
    int warranty;
} new_t;

typedef struct
{
    int release_year;
    int mileage;
    int repairs_num;
    int owners_num;
} used_t;

typedef union
{
    new_t new_car;
    used_t used_car;
} condition_t;

typedef struct
{
    char brand[MAX_STR_LEN];
    char country[MAX_STR_LEN];
    int price;
    char color[MAX_STR_LEN];
    mybool is_new;
    condition_t condition;
} car_t;

#endif