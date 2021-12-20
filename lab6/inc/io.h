#ifndef __IO__H__
#define __IO__H__

#include "general.h"
#include "structs.h"

void input_word_to_delete(char *word);
int input_compares_num();

void print_tree(tree_node_t *cur_node, int place, int position);
void print_word(tree_node_t *cur_node, int place, int space);
void print_direction(tree_node_t *cur_node, int place, int space, int position);

void print_list(int hash, hash_t *list);
void print_table(hash_table_t *table, int words_num);

void print_time(uint64_t bst_time, uint64_t avl_time, uint64_t hash_time, uint64_t file_time);
void print_memory(int bst_memory, int avl_memory, int hash_memory, int file_memory);
void print_cmprs_num(int bst_cnt, int avl_cnt, int hash_cnt, int file_cnt);

#endif