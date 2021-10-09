#ifndef __MENU__H__
#define __MENU__H__

#include "general.h"

#define PRINT_TABLE           1
#define ADD                   2
#define DEL                   3
#define SORT_KEYS             4
#define SORT_TABLE            5
#define SORT_TABLE_WITH_KEYS  6
#define ANALYSIS              7
#define FIND                  8
#define NEW_INIT_TABLE        9
#define EXIT                  0

void show_info();
int choose_action(void);

#endif