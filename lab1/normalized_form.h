#ifndef NORMAL_H
#define NORMAL_H

#include "main.h"
#include "input.h"

void normalize_int(int_number *init_int, real_number *normal_int);
int normalize_real(real_number *init_real, real_number *normal_real);
int zero_check(char *num, int len);

#endif