#include "binary_search_tree.h"

tree_node_t *create_node(char *value)
{
    tree_node_t *new_node = malloc(sizeof(tree_node_t));

    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = value;

    return new_node;
}

tree_node_t *add_node_to_tree(tree_node_t *cur_node, char *value)
{
    if (cur_node == NULL)
        cur_node = create_node(value);

    else if (strcmp(value, cur_node->data) < 0)
        cur_node->left = add_node_to_tree(cur_node->left, value);

    else if (strcmp(value, cur_node->data) > 0)
        cur_node->right = add_node_to_tree(cur_node->right, value);
    
    return cur_node;
}

int fill_tree_from_file(FILE *file, tree_node_t **root)
{
    int count = 0;
    char str[MAX_WORD_LEN];

    while (fscanf(file, "%s", str) != EOF)
    {
        char *cur_str = malloc(sizeof(strlen(str)));
        strcpy(cur_str, str);

        *root = add_node_to_tree(*root, cur_str);
        count++;
    }

    return count;
}

tree_node_t *remove_bst_node(tree_node_t *cur_node, char *target, int *cnt, int *found)
{
    if (cur_node == NULL)
        return cur_node;

    (*cnt)++;

    if (strcmp(target, cur_node->data) < 0)
        cur_node->left = remove_bst_node(cur_node->left, target, cnt, found);

    else if (strcmp(target, cur_node->data) > 0)
        cur_node->right = remove_bst_node(cur_node->right, target, cnt, found);

    else if (cur_node->left != NULL && cur_node->right != NULL)
    {
        *found = 1;
        cur_node->data = get_min_node(cur_node->right)->data;
        cur_node->right = remove_bst_node(cur_node->right, cur_node->data, cnt, found);
    }

    else if (cur_node->left == NULL && cur_node->right == NULL)
    {
        *found = 1;
        free(cur_node);
        cur_node = NULL;
    }

    else if (cur_node->left != NULL)
    {
        *found = 1;
        tree_node_t *tmp = cur_node->left;
        free(cur_node);
        cur_node = tmp;
    }

    else if (cur_node->right != NULL)
    {
        *found = 1;
        tree_node_t *tmp = cur_node->right;
        free(cur_node);
        cur_node = tmp;
    }

    return cur_node;
}

tree_node_t *get_min_node(tree_node_t *root)
{
    return root->left ? get_min_node(root->left) : root;
}

void free_node(tree_node_t **cur_node)
{
    free((*cur_node)->data);
    free(*cur_node);
    *cur_node = NULL;
}

void free_tree(tree_node_t **root)
{
    if (*root)
    {
        free_tree(&((*root)->left));
        free_tree(&((*root)->right));

        free_node(root);
    }
}