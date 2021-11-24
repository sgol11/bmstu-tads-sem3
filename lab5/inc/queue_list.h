#ifndef __QUEUE_LIST__H__
#define __QUEUE_LIST__H__

#include "general.h"
#include "structs.h"
#include "time_analysis.h"

void list_init(list_queue_t *queue);

int list_input_element(list_queue_t *queue, free_areas_t *areas);
int list_push(list_queue_t *queue, int element);

int list_delete_element(list_queue_t *queue, free_areas_t *areas);
int list_pop(list_queue_t *queue, size_t *address);

void list_print(list_queue_t *queue, free_areas_t *areas);
void print_free_areas(free_areas_t *areas);
void exclude_addresses(free_areas_t *areas, size_t addr);

void free_list(list_queue_t *queue);

int list_size(list_queue_t *queue);
void list_queue_simulation(void);

#endif