#ifndef __STACK_LIST__H__
#define __STACK_LIST__H__

#include "general.h"
#include "structs.h"
#include "analysis.h"

int list_input_element(list_stack_t **stack, free_areas_t *areas);
int list_push(list_stack_t **head, char element, int first_node);

int list_delete_element(list_stack_t **stack, free_areas_t *areas);
int list_pop(list_stack_t **stack, char *element, size_t *address);

void list_print(list_stack_t *stack, free_areas_t *areas);

int list_is_palindrome(list_stack_t **head, free_areas_t *areas);

void create_areas(free_areas_t *areas);
void print_free_areas(free_areas_t *areas);

void free_list(list_stack_t **head);

#endif