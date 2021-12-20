#ifndef __HASH__H__
#define __HASH__H__

#include "general.h"
#include "structs.h"

int hash_function(char *key, int size);
int new_hash_function(char *key, int size);
void hash_table_init(hash_table_t *table, int table_size);
void insert(hash_t **list, char *key);
void add_key_to_hash_table(hash_table_t *table, char *key, int restruct);
int fill_hash_table_from_file(FILE *file, hash_table_t *table, int restruct);

int remove_hash_table_value(hash_table_t *table, char *value, int *cnt, int restruct, int *words_num);

int avg_compares_hash_table(hash_table_t *table);

void free_list(hash_t **head);
void free_table(hash_table_t *table);

#endif