#ifndef ERRORS_H
#define ERRORS_H

#include "main.h"

#define OK 0
#define ERR_DIVIDEND -1
#define ERR_DIVISOR -2
#define ERR_OVERFLOW_DIVIDEND -3
#define ERR_OVERFLOW_DIVISOR -4
#define ERR_OVERFLOW_EXP -5
#define ERR_DIVISION_BY_ZERO -6
#define ERR_OVERFLOW_RES_EXP -7

void print_error(int code);

#endif