#ifndef __ANALYSIS__H__
#define __ANALYSIS__H__

#include <time.h>
#include <stdint.h>
#include <inttypes.h>

#include "general.h"
#include "structs.h"
#include "queue_array.h"
#include "queue_list.h"

#define GHZ 1500000000

uint64_t tick(void);
float random_time(float low, float high);

void analysis(void);

#endif