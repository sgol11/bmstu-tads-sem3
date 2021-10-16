#ifndef __GENERATE__H__
#define __GENERATE__H__

#include "general.h"
#include "structs.h"
#include "memory_manager.h"
#include "io.h"

int generate_matrix(matrix_std_t *std, matrix_sparse_t *sprs, double percent, int n, int m);
int input_generate_data(matrix_std_t *std, matrix_sparse_t *sprs, int is_vector);

#endif