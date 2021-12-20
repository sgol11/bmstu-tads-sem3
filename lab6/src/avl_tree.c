#include "avl_tree.h"

unsigned int height(tree_node_t *cur_node)
{
    return cur_node ? cur_node->height : 0;
}

int balance_factor(tree_node_t *cur_node)
{
    return height(cur_node->right) - height(cur_node->left);
}

void fix_height(tree_node_t *cur_node)
{
    unsigned int h_left = height(cur_node->left);
    unsigned int h_right = height(cur_node->right);

    cur_node->height = (h_left > h_right ? h_left : h_right) + 1;
}

tree_node_t *rotate_right(tree_node_t *cur_node)
{
    tree_node_t *new_node = cur_node->left;

    cur_node->left = new_node->right;
    new_node->right = cur_node;

    fix_height(cur_node);
    fix_height(new_node);

    return new_node;
}

tree_node_t *rotate_left(tree_node_t *cur_node)
{
    tree_node_t *new_node = cur_node->right;

    cur_node->right = new_node->left;
    new_node->left = cur_node;

    fix_height(cur_node);
    fix_height(new_node);

    return new_node;
}

tree_node_t *balance(tree_node_t *cur_node)
{
    tree_node_t *res_node = cur_node;

    fix_height(cur_node);

    if (balance_factor(cur_node) == 2)
    {
        if (balance_factor(cur_node->right) < 0)
            cur_node->right = rotate_right(cur_node->right);

        res_node = rotate_left(cur_node);
    }
    if (balance_factor(cur_node) == -2)
    {
        if (balance_factor(cur_node->left) > 0)
            cur_node->left = rotate_left(cur_node->left);

        res_node = rotate_right(cur_node);
    }

    return res_node;
}

tree_node_t *add_node_to_avl_tree(tree_node_t *cur_node, char *value)
{
    if (cur_node == NULL)
        cur_node = create_node(value);

    else if (strcmp(value, cur_node->data) < 0)
        cur_node->left = add_node_to_avl_tree(cur_node->left, value);

    else if (strcmp(value, cur_node->data) > 0)
        cur_node->right = add_node_to_avl_tree(cur_node->right, value);

    return balance(cur_node);
}

int fill_avl_tree_from_file(FILE *file, tree_node_t **root)
{
    int count = 0;
    char word[MAX_WORD_LEN];

    while (fscanf(file, "%s", word) != EOF)
    {
        char *cur_word = malloc(sizeof(strlen(word)));
        strcpy(cur_word, word);

        *root = add_node_to_avl_tree(*root, cur_word);
        count++;
    }

    return count;
}

tree_node_t *remove_min(tree_node_t *cur_node)
{
    if (cur_node->left == NULL)
        return cur_node->right;

    cur_node->left = remove_min(cur_node->left);

    return balance(cur_node);
}

tree_node_t *remove_avl_node(tree_node_t *cur_node, char *value, int *cnt, int *found)
{
    (*cnt)++;

    if (cur_node == NULL)
        return NULL;

    if (strcmp(value, cur_node->data) < 0)
        cur_node->left = remove_avl_node(cur_node->left, value, cnt, found);

    else if (strcmp(value, cur_node->data) > 0)
        cur_node->right = remove_avl_node(cur_node->right, value, cnt, found);

    else
    {
        *found = 1;

        tree_node_t *node_left = cur_node->left;
        tree_node_t *node_right = cur_node->right;

        // free_node(&cur_node);

        if (!node_right)
            return node_left;

        tree_node_t *min = get_min_node(node_right);
        min->right = remove_min(node_right);
        min->left = node_left;

        return balance(min);
    }

    return balance(cur_node);
}

void tree_traversal(tree_node_t *tree, int *cur_height, int *sum)
{
    if (tree)
    {
        (*cur_height)++;
        (*sum) += *cur_height;
        tree_traversal(tree->left, cur_height, sum);
        tree_traversal(tree->right, cur_height, sum);
        (*cur_height)--;
    }
}