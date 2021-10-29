#ifndef __MENU__H__
#define __MENU__H__s

#include "general.h"
#include "structs.h"

#define ADD_ELEMENT           1
#define REMOVE_ELEMENT        2
#define SHOW_STACK_STATE      3
#define CHECK_PALINDROME      4
#define CHOOSE_MODE           5
#define ANALYSIS              6
#define EXIT                  0

void show_info();
int choose_action(void);
int choose_form(void);

#endif