#include "analysis.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

int full_analysis(matrix_std_t *m_std, matrix_std_t *v_std, matrix_sparse_t *m_sprs, matrix_sparse_t *v_sprs)
{
    int rc = OK;
    double time1, time2;

    matrix_std_t res1;
    matrix_sparse_t res2;

    init_std_matrix(&res1);
    init_sprs_matrix(&res2);
    
    rc = multi_std(m_std, v_std, &res1, &time1);
    rc = multi_sparse(m_sprs, v_sprs, &res2, &time2);

    if (rc == OK)
    {
        size_t memory_std = 0, memory_sprs = 0;

        memory_std = sizeof(int) * m_std->rows * m_std->columns + sizeof(int) * v_std->rows;
        memory_sprs = (sizeof(int) * 2 * m_sprs->nn_cnt + sizeof(node_t) * cnt_nn_columns(m_sprs) +
                       sizeof(int) * 2 * v_sprs->nn_cnt + sizeof(node_t) * 2);

        printf("Сравнение времени выполнения операций и используемого объема памяти\n\n");
        printf("Размерность матрицы: %dx%d\n", m_std->rows, m_std->columns);
        printf("Процент заполненности матрицы: %.0lf%%\n", (double)m_sprs->nn_cnt / (m_sprs->rows * m_sprs->columns) * 100);
        printf("Процент заполненности вектора-столбца: %.0lf%%\n\n", (double)v_sprs->nn_cnt / (v_sprs->rows * v_sprs->columns) * 100);
        
        printf("|---------|----------------------|------------------------------------------|\n");
        printf("|         | Стандартный алгоритм | Алгоритм работы с разреженными матрицами |\n");
        printf("|---------|----------------------|------------------------------------------|\n");
        printf("|  Время  | %-20lf | %-40lf |\n", time1, time2);
        printf("|---------|----------------------|------------------------------------------|\n");
        printf("| Память  | %-20lld | %-40lld |\n", memory_std, memory_sprs);
        printf("|---------|----------------------|------------------------------------------|\n\n");
    }
    
    if (res1.data)
        free_std_matrix(&res1);
    if (res2.A)
        free_sparse_matrix(&res2);

    print_error(rc);

    return rc;
}

int cnt_nn_columns(matrix_sparse_t *matr)
{
    int cnt = 0;
    node_t *cur;
    cur = &matr->JA;

    while (cur)
    {
        cnt++;
        cur = cur->next;
    }

    return cnt;
}