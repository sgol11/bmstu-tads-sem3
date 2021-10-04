#ifndef __CHANGE_CARS_NUM__H__
#define __CHANGE_CARS_NUM__H__

#include "general.h"
#include "structs.h"
#include "get_vars.h"
#include "io_file.h"

int add_car(char *file_name, car_t *cars, int *n);

int delete_cars(char *file_name, car_t *cars, int *n);
void delete_str_in_certain_column(car_t *cars, int *n, int col, char *val);
void delete_bool_in_certain_column(car_t *cars, int *n, int col, mybool val);
void delete_int_in_certain_column(car_t *cars, int *n, int col, int val);

#endif