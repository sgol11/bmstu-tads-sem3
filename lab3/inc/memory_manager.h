#ifndef __MEMORY__H__
#define __MEMORY__H__

#include "general.h"
#include "structs.h"

int** allocate_matrix(int n, int m);
void free_matrix(int **ptrs);
void free_std_matrix(matrix_std_t *matr);
void free_sparse_matrix(matrix_sparse_t *matr);
void init_std_matrix(matrix_std_t *matr);
void init_sprs_matrix(matrix_sparse_t *matr);

#endif