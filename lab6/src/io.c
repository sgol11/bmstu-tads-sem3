#include "io.h"

void input_word_to_delete(char *word)
{
    printf("\nВведите слово, которое хотите удалить: ");
    scanf("%s", word);
}

int input_compares_num()
{
    int cnt = 0;
    printf("Введите максимально допустимое среднее количество сравнений в хеш-таблице: ");
    int rc = scanf("%d", &cnt);
    if (!rc || cnt < 1)
        printf("\nНеверное число сравнений\n");

    return cnt;
}

void print_tree(tree_node_t *cur_node, int place, int position)
{
    if (cur_node)
    {
        int space = 10;
        place += space;

        print_tree(cur_node->right, place, RIGHT);

        if (position == LEFT)
            print_direction(cur_node, place, space, LEFT);

        print_word(cur_node, place, space);

        if (position == RIGHT)
            print_direction(cur_node, place, space, RIGHT);

        print_tree(cur_node->left, place, LEFT);
    }
}

void print_word(tree_node_t *cur_node, int place, int space)
{
    printf("\n");
    for (int i = space; i < place; i++)
        printf(" ");

    printf("(%s)\n", cur_node->data);
}

void print_direction(tree_node_t *cur_node, int place, int space, int position)
{
    if (position == LEFT)
        printf("\n");
    for (int i = space; i < place - 1; i++)
        printf(" ");
    (position == RIGHT) ? printf("/") : printf("\\");
}

void print_list(int hash, hash_t *list)
{
    hash_t *cur_hash = list;

    while (cur_hash)
    {
        printf(" %5s -> ", cur_hash->data);
        cur_hash = cur_hash->next;
    }

    printf("│\n");
}

void print_table(hash_table_t *table, int words_num)
{
    if (words_num == 0)
        printf("\nХеш-таблица пуста\n\n");
    else
    {
        printf("\n");
        printf("HASH | VALUES\n");
        printf("     |\n");
        for (int i = 0; i < table->size; i++)
        {
            hash_t *tmp = table->list[i];

            if (tmp != NULL)
            {
                printf("%4d | ", i);

                while (tmp != NULL)
                {
                    printf("%s -> ", tmp->data);
                    tmp = tmp->next;
                }
                printf(" NULL\n");
            }
            else
                printf("%4d | NULL\n", i);
        }
        printf("\n");
    }
}

void print_time(uint64_t bst_time, uint64_t avl_time, uint64_t hash_time, uint64_t file_time)
{
    printf("\n");
    printf("                 | Бинарное дерево поиска | АВЛ-дерево             | Хеш-таблица            | Файл                   \n");
    printf("-----------------|------------------------|------------------------|------------------------|------------------------\n");
    printf("Время (такты)    |%24lld|%24lld|%24lld|%24lld\n", bst_time, avl_time, hash_time, file_time);
}

void print_memory(int bst_memory, int avl_memory, int hash_memory, int file_memory)
{
    printf("Память (байты)   |%24d|%24d|%24d|%24d\n", bst_memory, avl_memory, hash_memory, file_memory);
}

void print_cmprs_num(int bst_cnt, int avl_cnt, int hash_cnt, int file_cnt)
{
    printf("Кол-во сравнений |%24d|%24d|%24d|%24d\n\n", bst_cnt, avl_cnt, hash_cnt, file_cnt);
}