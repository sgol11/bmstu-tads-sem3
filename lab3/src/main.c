#include "general.h"
#include "structs.h"
#include "io.h"
#include "memory_manager.h"
#include "multi.h"
#include "menu.h"
#include "generate_matrix.h"

int main(void)
{
    int rc = OK;

    setbuf(stdout, NULL);
    setlocale(LC_ALL, "");

    matrix_std_t std_matrix;
    matrix_sparse_t sparse_matrix;

    matrix_std_t std_vector;
    matrix_sparse_t sparse_vector;

    matrix_std_t std_multi_res;
    matrix_sparse_t sparse_multi_res;

    init_std_matrix(&std_matrix);
    init_std_matrix(&std_vector);
    init_std_matrix(&std_multi_res);

    init_sprs_matrix(&sparse_matrix);
    init_sprs_matrix(&sparse_vector);
    init_sprs_matrix(&sparse_multi_res);

    int choice = 1;
    double tmp;

    show_info();

    while (choice != EXIT)
    {
        choice = choose_action();

        switch (choice)
        {
            case GENERATE_MATRIX:
                input_generate_data(&std_matrix, &sparse_matrix, 0);
                break;
            case GENERATE_VECTOR:
                input_generate_data(&std_vector, &sparse_vector, 1);
                break;
            case INPUT_MATRIX:
                input_matrix(&std_matrix, &sparse_matrix, 0);
                break;
            case INPUT_VECTOR:
                input_matrix(&std_vector, &sparse_vector, 1);
                break;
            case OUTPUT_MATRIX:
                print_matrix(&std_matrix, &sparse_matrix, 0);
                break;
            case OUTPUT_VECTOR:
                print_matrix(&std_vector, &sparse_vector, 1);
                break;
            case MULTI_STD:
                rc = multi_std(&std_matrix, &std_vector, &std_multi_res, &tmp);
                if (rc == OK)
                {
                    printf("Результат умножения матрицы на вектор-столбец (стандартный алгоритм)\n");
                    print_std_matrix(&std_multi_res);
                }
                print_error(rc);
                break;
            case MULTI_SPARSE:
                rc = multi_sparse(&sparse_matrix, &sparse_vector, &sparse_multi_res, &tmp);
                if (rc == OK)
                {
                    printf("Результат умножения матрицы на вектор-столбец (3 объекта)\n");
                    print_sparse_matrix(&sparse_multi_res);
                }
                print_error(rc);
                break;
            case ANALYSIS:
                full_analysis(&std_matrix, &std_vector, &sparse_matrix, &sparse_vector);
                break;
        }
    }

    printf("Выход\n");
    
    if (std_matrix.data)
        free_std_matrix(&std_matrix);
    if (std_vector.data)
        free_std_matrix(&std_vector);
    if (std_multi_res.data)
        free_std_matrix(&std_multi_res);

    if (sparse_matrix.A)
        free_sparse_matrix(&sparse_matrix);
    if (sparse_vector.A)
        free_sparse_matrix(&sparse_vector);
    if (sparse_multi_res.A)
        free_sparse_matrix(&sparse_multi_res);

    return 0;
}