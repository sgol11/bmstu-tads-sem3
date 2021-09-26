#ifndef DIVISION_H
#define DIVISION_H

#include "main.h"
#include "input.h"

int division(real_number *dividend, real_number *divisor, real_number *quotient);

void small_division(char *dividend, int len1, char *divisor, int len2, 
char *quotient, int *len3, char *remainder, int *len4);

int greater_or_equal(char *first_num, int first_len, char *second_num, int second_len);
int multiplication(char *num, int len, int count, char *new_num);
int difference(char *num1, int len1, char *num2, int len2, char *res);

void delete_init_zeros(char *num, int *len);
void swap(char *num, int i1, int i2);

#endif