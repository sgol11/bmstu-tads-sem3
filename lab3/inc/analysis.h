#ifndef __ANALYSIS__H__
#define __ANALYSIS__H__

#include <math.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

#include "general.h"
#include "structs.h"
#include "io.h"
#include "multi.h"
#include "memory_manager.h"

#define GHZ 1500000000

uint64_t tick(void);
int full_analysis(matrix_std_t *m_std, matrix_std_t *v_std, matrix_sparse_t *m_sprs, matrix_sparse_t *v_sprs);
int cnt_nn_columns(matrix_sparse_t *matr);

#endif