#ifndef __IO_FILE__H__
#define __IO_FILE__H__

#include "../inc/general.h"
#include "../inc/structs.h"
#include "../inc/get_vars.h"

int download_table(char *file_name, car_t *cars, int *n);
int read_table(char *file_name, car_t *cars, int *n);
void print_table(car_t *cars, int n);

void rewrite_table_to_file(char *file_name, car_t *cars, int n);

void print_error_io_file(int code);

#endif