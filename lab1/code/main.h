#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPONENT_SIZE 5
#define MAX_MANTISSA_SIZE 30

typedef struct
{
    char sign;
    int number_len;
    char number[MAX_MANTISSA_SIZE];
} int_number;

typedef struct
{
    char sign;
    int mantissa_len;
    char mantissa[MAX_MANTISSA_SIZE + 3];
    int exponent;
} real_number;

void print_info();

#endif