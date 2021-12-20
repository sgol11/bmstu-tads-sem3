#include "hash_table.h"

int hash_function(char *key, int size)
{
    int res_hash = 0;

    while (*key)
    {
        res_hash += *key;
        key++;
    }

    return res_hash % size;
}

int new_hash_function(char *key, int size)
{
    unsigned long pow = 1, code_pow = 0;
    int pow_multiplier = 10;

    while (*key)
    {
        code_pow += *key * pow;
        pow *= (pow_multiplier++);
        key++;
    }

    return code_pow % size;
}

void hash_table_init(hash_table_t *table, int table_size)
{
    table->size = table_size;
    table->list = malloc(sizeof(hash_t *) * table_size);

    for (int i = 0; i < table_size; i++)
        table->list[i] = NULL;
}

void insert(hash_t **list, char *key)
{
    hash_t *new_elem = malloc(sizeof(hash_t));

    hash_t *cur_hash = *list;
    int exit = 0, already_exists = 0;

    while (cur_hash && !exit)
    {
        if (strcmp(key, cur_hash->data) == 0)
        {
            free(new_elem);
            already_exists = 1;
        }
        if (cur_hash->next == NULL)
            exit = 1;
        else
            cur_hash = cur_hash->next;
    }

    if (!already_exists)
    {
        strcpy(new_elem->data, key);

        if (cur_hash)
        {
            new_elem->next = cur_hash->next;
            cur_hash->next = new_elem;
        }
        else
            new_elem->next = NULL;
    }

    if (!(*list))
        *list = new_elem;
}

void add_key_to_hash_table(hash_table_t *table, char *key, int restruct)
{
    int hash;

    if (!restruct)
        hash = hash_function(key, table->size);
    else
        hash = new_hash_function(key, table->size);

    insert(&(table->list[hash]), key);
}

int fill_hash_table_from_file(FILE *file, hash_table_t *table, int restruct)
{
    int count = 0;
    char word[MAX_WORD_LEN];

    for (int i = 0; i < table->size; i++)
    {
        fscanf(file, "%s", word);

        add_key_to_hash_table(table, word, restruct);
        count++;
    }

    return count;
}

int remove_hash_table_value(hash_table_t *table, char *value, int *cnt, int restruct, int *words_num)
{
    *cnt = 0;
    int found = 0;
    int hash;

    if (!restruct)
        hash = hash_function(value, table->size);
    else
        hash = new_hash_function(value, table->size);

    hash_t *prev_hash = table->list[hash];
    hash_t *cur_hash = prev_hash ? prev_hash->next : NULL;

    if (prev_hash && strcmp(prev_hash->data, value) == 0)
    {
        (*cnt)++;
        table->list[hash] = prev_hash->next;
        free(prev_hash);
        found = 1;
        (*words_num)--;
        return found;
    }

    while (cur_hash && !found)
    {
        (*cnt)++;

        if (strcmp(cur_hash->data, value) == 0)
        {
            prev_hash->next = cur_hash->next;
            free(cur_hash);
            found = 1;
            (*words_num)--;
        }
        else
        {
            prev_hash = prev_hash->next;
            cur_hash = cur_hash->next;
        }
    }
    (*cnt)++;

    return found;
}

int avg_compares_hash_table(hash_table_t *table)
{
    int sum_cmprs = 0, elem_cmprs = 1;

    for (int i = 0; i < table->size; i++)
    {
        elem_cmprs = 1;
        hash_t *cur = table->list[i];
        while (cur)
        {
            sum_cmprs += elem_cmprs++;
            cur = cur->next;
        }
    }

    return sum_cmprs / table->size;
}

void free_list(hash_t **head)
{
    if (head)
    {
        hash_t *cur = *head;
        while (cur)
        {
            hash_t *next = cur->next;
            free(cur);
            cur = next;
        }

        *head = NULL;
    }
}

void free_table(hash_table_t *table)
{
    for (int i = 0; i < table->size; i++)
        free_list(&table->list[i]);

    free(table->list);
}