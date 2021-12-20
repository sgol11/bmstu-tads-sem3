#ifndef __MENU__H__
#define __MENU__H__s

#include "general.h"

#define READ_FROM_FILE        1
#define PRINT_MATRIX          2
#define FIND_PATH             3
#define VIS_GRAPH             4
#define EXIT                  0

void show_info();
int choose_action(void);

#endif