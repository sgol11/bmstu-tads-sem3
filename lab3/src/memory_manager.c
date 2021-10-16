#include "memory_manager.h"

int** allocate_matrix(int n, int m)
{
    int rc = OK;
    int **ptrs, *data;

    ptrs = calloc(n, sizeof(int*));
    if (!ptrs)
        rc = ERR_MEMORY;
    
    if (rc == OK)
    {
        data = calloc(n * m, sizeof(int));
        if (!data)
        {
            free(ptrs);
            rc = ERR_MEMORY;
        }   
    }
    
    if (rc == OK)
    {
        for (int i = 0; i < n; i++)
            ptrs[i] = data + i * m;
    }

    return rc == OK ? ptrs : NULL;
}

void free_matrix(int **ptrs)
{
    free(ptrs[0]);
    free(ptrs);
}

void free_std_matrix(matrix_std_t *matr)
{
    free_matrix(matr->data);
    init_std_matrix(matr);
}

void free_sparse_matrix(matrix_sparse_t *matr)
{
    free(matr->A);
    free(matr->IA);
    
    node_t *tmp, *head;
    head = matr->JA.next;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    
    init_sprs_matrix(matr);
}

void init_std_matrix(matrix_std_t *matr)
{
    matr->data = NULL;
    matr->rows = 0;
    matr->columns = 0;
}

void init_sprs_matrix(matrix_sparse_t *matr)
{
    matr->A = NULL;
    matr->IA = NULL;
}