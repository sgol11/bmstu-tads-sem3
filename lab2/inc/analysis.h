#ifndef __ANALYSIS__H__
#define __ANALYSIS__H__

#include <time.h>
#include <stdint.h>
#include <inttypes.h>

#include "general.h"
#include "structs.h"
#include "sort.h"

#define GHZ 1500000000
#define ANALYSIS_10 "data/analysis_data/10.txt"
#define ANALYSIS_50 "data/analysis_data/50.txt"
#define ANALYSIS_100 "data/analysis_data/100.txt"
#define ANALYSIS_200 "data/analysis_data/200.txt"
#define ANALYSIS_500 "data/analysis_data/500.txt"

uint64_t tick(void);

int full_analysis(void);

int analyse_cur_table(car_t *cars, int n);

void copy_table(car_t *src, car_t *dst, int n);

#endif