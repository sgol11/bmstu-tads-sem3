#ifndef __ANALYSIS__H__
#define __ANALYSIS__H__

#include <math.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

#include "general.h"
#include "structs.h"
#include "sort.h"

#define GHZ 1500000000

uint64_t tick(void);
int analyse_table_sort(car_t *cars, int n);
void copy_table(car_t *src, car_t *dst, int n);

#endif