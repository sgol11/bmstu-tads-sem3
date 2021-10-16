#include "generate_matrix.h"

int generate_matrix(matrix_std_t *std, matrix_sparse_t *sprs, double percent, int n, int m)
{
    int rc = OK;
    int nn = n * m * percent / 100;

    if (std->data)
        free_matrix(std->data);

    std->data = allocate_matrix(n, m);
    std->rows = n;
    std->columns = m;
    
    int i, j;
    for (int k = 0; k < nn; k++)
    {
        do
        {
            i = rand() % n;
            j = rand() % m;
        } while (std->data[i][j] != 0);

        std->data[i][j] = 1 + rand() % 50;
    }

    rc = std_to_sparse(std, sprs);

    return rc;
}

int input_generate_data(matrix_std_t *std, matrix_sparse_t *sprs, int is_vector)
{
    int rc = OK;

    int n, m = 1;
    double perc;

    if (is_vector)
        printf("\nВведите размер вектора-столбца: ");
    else
        printf("\nВведите количество строк: ");

    if (scanf("%d", &n) == 0 || n <= 0)
        rc = ERR_INPUT_MATR_SIZE;

    if (!is_vector && rc == OK)
    {
        printf("Введите количество столбцов: ");
        if (scanf("%d", &m) == 0 || m <= 0)
            rc = ERR_INPUT_MATR_SIZE;
    }

    if (rc == OK)
    {
        printf("Введите процент заполненности: ");
        if (scanf("%lf", &perc) == 0 || perc < 0 || perc > 100)
            rc = ERR_PERCENT;
    }

    if (rc == OK)
        rc = generate_matrix(std, sprs, perc, n, m);

    if (rc == OK && is_vector)
        printf("\nВектор-столбец успешно добавлен\n\n");
    else if (rc == OK)
        printf("\nМатрица успешно добавлена\n\n");

    print_error(rc);

    return rc;
}