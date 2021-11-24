#ifndef __MENU__H__
#define __MENU__H__s

#include "general.h"
#include "structs.h"

#define CHOOSE_MODE           1
#define ADD_ELEMENT           2
#define REMOVE_ELEMENT        3
#define SHOW_QUEUE_STATE      4
#define SIMULATION            5 
#define ANALYSIS              6
#define EXIT                  0

void show_info();
int choose_action(void);
int choose_form(void);

#endif