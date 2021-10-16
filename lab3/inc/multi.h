#ifndef __MULTI__H__
#define __MULTI__H__

#include "general.h"
#include "structs.h"
#include "memory_manager.h"
#include "io.h"
#include "analysis.h"

int multi_std(matrix_std_t *matr, matrix_std_t *vector, matrix_std_t *res, double *time);
void multi_std_action(matrix_std_t *matr, matrix_std_t *vector, matrix_std_t *res);

int multi_sparse(matrix_sparse_t *matr, matrix_sparse_t *vector, matrix_sparse_t *res, double *time);
void multi_sparse_action(matrix_sparse_t *matr, matrix_sparse_t *vector, matrix_sparse_t *res);
void make_final_sparse_form(matrix_sparse_t *init, matrix_sparse_t *final);

#endif