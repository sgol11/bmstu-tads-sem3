#ifndef __QUEUE_ARRAY__H__
#define __STACK_ARRAY__H__

#include "general.h"
#include "structs.h"
#include "time_analysis.h"

#define EPS 1e-7

void array_init(array_queue_t *queue);

int array_input_element(array_queue_t *queue);
int array_push(array_queue_t *queue, int element);

int array_delete_element(array_queue_t *queue);
int array_pop(array_queue_t *queue);

void array_print(array_queue_t *queue);

int array_size(array_queue_t *queue);

void array_queue_simulation(void);

#endif