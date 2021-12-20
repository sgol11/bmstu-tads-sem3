#include "measurements.h"

int remove_file_value(FILE *f_in, FILE *f_out, char *value, int *cnt)
{
    char buf[MAX_WORD_LEN];
    int found = 0;

    while(!feof(f_in))
    {
        fscanf(f_in, "%s", buf);

        if (strcmp(buf, value) != 0)
            fprintf(f_out, "%s\n", buf);
        else
            found = 1;

        if (!found)
            (*cnt)++;
    }
    (*cnt)++;

    return found;
}

uint64_t get_time_ticks(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

int find_hash_table_size(hash_table_t *table)
{
    int size = 0;

    size += sizeof(table->size);
    size += sizeof(table->list);

    for (int i = 0; i < table->size; i++)
    {
        hash_t *tmp = table->list[i];

        while (tmp)
        {
            size += sizeof(hash_t);
            size += sizeof(tmp->data);
            size += sizeof(tmp->next);

            tmp = tmp->next;
        }
    }

    return size;
}