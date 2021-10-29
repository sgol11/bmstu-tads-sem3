#ifndef __ANALYSIS__H__
#define __ANALYSIS__H__

#include <math.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

#include "general.h"
#include "structs.h"
#include "stack_array.h"
#include "stack_list.h"

#define GHZ 1500000000

uint64_t tick(void);
void analysis(void);

#endif