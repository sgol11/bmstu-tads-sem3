#include "multi.h"

int multi_std(matrix_std_t *matr, matrix_std_t *vector, matrix_std_t *res, double *time)
{
    int rc = OK;
    uint64_t start, end; 

    if (!matr->data)
        rc = ERR_NO_MATRIX;
    else if (!vector->data)
        rc = ERR_NO_VECTOR;
    else if (matr->columns != vector->rows)
        rc = ERR_MULTI;

    if (rc == OK)
    {
        start = tick();

        res->data = allocate_matrix(matr->rows, 1);

        if (!res->data)
            rc = ERR_MEMORY;
        else
        {
            res->rows = matr->rows;
            res->columns = 1;

            multi_std_action(matr, vector, res);
            end = tick();

            *time = (double)(end - start) / GHZ;
        }
    }

    return rc;
}

void multi_std_action(matrix_std_t *matr, matrix_std_t *vector, matrix_std_t *res)
{
    for (int i = 0; i < matr->rows; i++)
    {
        res->data[i][0] = 0;
        for (int j = 0; j < matr->columns; j++)
            res->data[i][0] += matr->data[i][j] * vector->data[j][0];
    }
}

int multi_sparse(matrix_sparse_t *matr, matrix_sparse_t *vector, matrix_sparse_t *res, double *time)
{
    int rc = OK;
    matrix_sparse_t tmp;
    uint64_t start, end;
    
    if (!matr->A)
        rc = ERR_NO_MATRIX;
    else if (!vector->A)
        rc = ERR_NO_VECTOR;
    else if (matr->columns != vector->rows)
        rc = ERR_MULTI;

    if (rc == OK)
    {
        start = tick();

        tmp.A = calloc(matr->rows, sizeof(int));
        tmp.IA = calloc(matr->rows, sizeof(int));

        if (!tmp.A || !tmp.IA)
            rc = ERR_MEMORY;
        else
        {
            for (int i = 0; i < matr->rows; i++)
                tmp.IA[i] = i;

            tmp.rows = matr->rows;
            tmp.columns = 1;

            multi_sparse_action(matr, vector, &tmp);

            make_final_sparse_form(&tmp, res);

            res->JA.index = 0;
            node_t *node = (node_t*)malloc(sizeof(node_t));
            res->JA.next = node;
            node->index = res->nn_cnt;
            node->next = NULL;

            end = tick();

            *time = (double)(end - start) / GHZ;
        }

        free(tmp.A);
        free(tmp.IA);
    }

    return rc;
}

void multi_sparse_action(matrix_sparse_t *matr, matrix_sparse_t *vector, matrix_sparse_t *res)
{
    node_t *cur_node;
    cur_node = &matr->JA;
    int col = 0, j = 0;

    for (int i = 0; i < matr->nn_cnt; i++)
    {
        while (cur_node->next && i == cur_node->next->index)
        {
            cur_node = cur_node->next;
            col++;
            while (col > vector->IA[j])
                j++;
        }

        if (col == vector->IA[j])
            res->A[matr->IA[i]] += matr->A[i] * vector->A[j];
    }
}

void make_final_sparse_form(matrix_sparse_t *init, matrix_sparse_t *final)
{
    int cnt_del = 0;
    
    for (int i = 0; i < init->rows; i++)
        if (init->A[i] == 0)
            cnt_del++;

    final->nn_cnt = init->rows - cnt_del;

    final->A = calloc(final->nn_cnt, sizeof(int));
    final->IA = calloc(final->nn_cnt, sizeof(int));
    
    int j = 0;
    for (int i = 0; i < init->rows; i++)
        if (init->A[i] != 0)
        {
            final->A[j] = init->A[i];
            final->IA[j] = init->IA[i];
            j++;
        }

    final->rows = init->rows;
    final->columns = 1;
}
