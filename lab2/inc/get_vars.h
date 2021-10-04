#ifndef __GET_VARS__H__
#define __GET_VARS__H__

#include "../inc/general.h"
#include "../inc/structs.h"

int fget_str(FILE *f, char *str);
int fget_int(FILE *f, int *num);

void get_str(char *str);
void get_int(int *num);

void print_error_change_cars_num(int code);

#endif