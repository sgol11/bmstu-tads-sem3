#ifndef __MEASURE__H__
#define __MEASURE__H__

#include <time.h>

#include "general.h"
#include "structs.h"

int remove_file_value(FILE *f_in, FILE *f_out, char *value, int *cnt);
uint64_t get_time_ticks(void);
int find_hash_table_size(hash_table_t *table);

#endif