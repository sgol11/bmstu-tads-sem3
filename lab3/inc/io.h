#ifndef __IO__H__
#define __IO__H__

#include "general.h"
#include "structs.h"
#include "memory_manager.h"
#include "menu.h"

int input_std_matr(matrix_std_t *matr, int is_vector);
int input_not_null_elements(matrix_std_t *matr, int is_vector);

int sparse_to_std(matrix_sparse_t *from, matrix_std_t *to);
int std_to_sparse(matrix_std_t *from, matrix_sparse_t *to);

void print_std_matrix(matrix_std_t *matr);
void print_sparse_matrix(matrix_sparse_t *matr);

int cnt_nn_elements(matrix_std_t *matr);

void input_matrix(matrix_std_t *m_std, matrix_sparse_t *m_sprs, int vect);
void print_matrix(matrix_std_t *m_std, matrix_sparse_t *m_sprs, int vect);

void print_error(int code);

#endif