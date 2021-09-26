#ifndef INPUT_H
#define INPUT_H

#include "main.h"
#include "error_processing.h"

int input_int(int_number *num);
void initialization_int(int_number *num);

int input_real(real_number *num);
void initialization_real(real_number *num);
int process_sign(real_number *num, int *idx, char ch, int *dot, int *e, int *comp);
int process_after_dot(real_number *num, int *idx, char ch, int *e, int *comp);
int process_after_e(char *num, int *idx, char ch, int *comp);
int process_digits(real_number *num, int *idx, char ch, int *dot, int *e, int *comp);

#endif