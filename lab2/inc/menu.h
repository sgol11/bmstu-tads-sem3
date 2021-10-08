#ifndef __MENU__H__
#define __MENU__H__

#include "general.h"

#define PRINT_TABLE           1
#define ADD                   2
#define DEL                   3
#define SORT_KEYS             4
#define SORT_TABLE            5
#define SORT_TABLE_WITH_KEYS  6
#define ANALYSIS_CUR_TABLE    7
#define FULL_ANALYSIS         8
#define FIND                  9
#define NEW_INIT_TABLE        10
#define EXIT                  0

void show_info();
void choose_action(int *choice);

#endif