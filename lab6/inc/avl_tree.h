#ifndef __AVL__H__
#define __AVL__H__

#include "general.h"
#include "structs.h"
#include "binary_search_tree.h"
#include "io.h"

unsigned int height(tree_node_t *cur_node);
int balance_factor(tree_node_t *cur_node);
void fix_height(tree_node_t* cur_node);
tree_node_t* rotate_right(tree_node_t *cur_node);
tree_node_t* rotate_left(tree_node_t *cur_node);
tree_node_t *balance(tree_node_t *cur_node);

tree_node_t *add_node_to_avl_tree(tree_node_t *cur_node, char *value);
int fill_avl_tree_from_file(FILE *file, tree_node_t **root);

void tree_traversal(tree_node_t *tree, int *cur_height, int *sum);

tree_node_t *remove_min(tree_node_t *cur_node);
tree_node_t *remove_avl_node(tree_node_t *cur_node, char *value, int *cnt, int *found);

#endif