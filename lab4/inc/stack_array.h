#ifndef __STACK_ARRAY__H__
#define __STACK_ARRAY__H__

#include "general.h"
#include "structs.h"
#include "analysis.h"

int array_input_element(arr_stack_t *stack);
int array_push(arr_stack_t *stack, char element);

int array_delete_element(arr_stack_t *stack);
int array_pop(arr_stack_t *stack, char *element);

void array_copy(arr_stack_t *dst, arr_stack_t *src);

void array_print(arr_stack_t *stack);

int array_is_palindrome(arr_stack_t *word);

#endif