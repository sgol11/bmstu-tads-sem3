#ifndef __MENU__H__
#define __MENU__H__s

#include "general.h"
#include "structs.h"

#define GENERATE_MATRIX       1
#define GENERATE_VECTOR       2
#define INPUT_MATRIX          3
#define INPUT_VECTOR          4
#define OUTPUT_MATRIX         5
#define OUTPUT_VECTOR         6
#define MULTI_STD             7
#define MULTI_SPARSE          8
#define ANALYSIS              9
#define EXIT                  0

void show_info();
int choose_action(void);
int choose_form(int input);

#endif