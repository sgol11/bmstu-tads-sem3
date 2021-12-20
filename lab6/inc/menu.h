#ifndef __MENU__H__
#define __MENU__H__s

#include "general.h"
#include "structs.h"

#define READ_FROM_FILE        1
#define BINARY_SEARCH_TREE    2
#define AVL_TREE              3
#define HASH_TABLE            4
#define DELETE_WORD           5 
#define EXIT                  0

void show_info();
int choose_action(void);

#endif