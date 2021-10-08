#ifndef __SORT__H__
#define __SORT__H__

#include "general.h"
#include "structs.h"
#include "io_file.h"

void sort_keys(car_t *cars, key_t *keys, int n);

void form_keys_table(car_t *cars, key_t *keys, int n);

int bubble_sort_keys(key_t *keys, int n);
void swap_keys(key_t *key1, key_t *key2);

int qsort_keys(key_t *keys, int n);
int compare_keys(const key_t *key1, const key_t *key2);

int bubble_sort_table(car_t *cars, int n);
void swap_table(car_t *car1, car_t *car2);

int qsort_table(car_t *cars, int n);
int print_sorted_table(car_t *cars, int n);
int compare_cars(const car_t *car1, const car_t *car2);

void print_sorted_keys(key_t *keys, int n);
void print_sorted_table_with_keys(car_t *cars, key_t *keys, int n);

#endif