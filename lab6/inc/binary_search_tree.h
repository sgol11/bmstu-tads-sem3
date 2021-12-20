#ifndef __BST__H__
#define __BST__H__

#include "general.h"
#include "structs.h"

tree_node_t *create_node(char *value);
tree_node_t *add_node_to_tree(tree_node_t *cur_node, char *value);
int fill_tree_from_file(FILE *file, tree_node_t **root);

tree_node_t *remove_bst_node(tree_node_t *cur_node, char *target, int *cnt, int *found);
tree_node_t *get_min_node(tree_node_t *root);

void free_node(tree_node_t **cur_node);
void free_tree(tree_node_t **root);

#endif