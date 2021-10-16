#include "io.h"

int input_std_matr(matrix_std_t *matr, int is_vector)
{
    int rc = OK;

    int n, m = 1;

    if (is_vector)
        printf("\nВведите размер вектора-столбца: ");
    else
        printf("\nВведите количество строк матрицы: ");

    if (scanf("%d", &n) == 0 || n <= 0)
        rc = ERR_INPUT_MATR_SIZE;

    if (!is_vector && rc == OK)
    {
        printf("Введите количество столбцов матрицы: ");
        if (scanf("%d", &m) == 0 || m <= 0)
            rc = ERR_INPUT_MATR_SIZE;
    }

    if (rc == OK)
    {
        matr->rows = n;
        matr->columns = m;

        matr->data = allocate_matrix(n, m);

        if (!matr->data)
            rc = ERR_MEMORY;
    }

    if (!is_vector && rc == OK)
    {
        printf("Введите %d элементов матрицы (в качестве разделителя между элементами\n"
               "вы можете использовать пробел или символ переноса строки)\n", n*m);
        for (int i = 0; i < n && rc == OK; i++)
            for (int j = 0; j < m && rc == OK; j++)
                if (scanf("%d", &matr->data[i][j]) == 0 || abs(matr->data[i][j]) > MAX_ELEMENT)
                    rc = ERR_INPUT_ELEMENT; 
    }
    else if (is_vector && rc == OK)
    {
        printf("Введите %d элементов вектора (в качестве разделителя между элементами\n"
               "вы можете использовать пробел или символ переноса строки)\n", n);
        for (int i = 0; i < n && rc == OK; i++)
            if (scanf("%d", &matr->data[i][0]) == 0 || abs(matr->data[i][0]) > MAX_ELEMENT)
                rc = ERR_INPUT_ELEMENT; 
    }

    return rc;
}

int input_not_null_elements(matrix_std_t *matr, int is_vector)
{
    int rc = OK;

    int n, m = 1, nn;

    if (is_vector)
        printf("\nВведите размер вектора-столбца: ");
    else
        printf("\nВведите количество строк матрицы: ");

    if (scanf("%d", &n) == 0 || n <= 0)
        rc = ERR_INPUT_MATR_SIZE;

    if (!is_vector && rc == OK)
    {
        printf("Введите количество столбцов матрицы: ");
        if (scanf("%d", &m) == 0 || m <= 0)
            rc = ERR_INPUT_MATR_SIZE;
    }

    if (rc == OK)
    {
        matr->rows = n;
        matr->columns = m;

        matr->data = allocate_matrix(n, m);

        if (!matr->data)
            rc = ERR_MEMORY;
    }

    if (rc == OK)
    {
        printf("Введите количество ненулевых элементов: ");
        if (scanf("%d", &nn) == 0 || nn < 0 || nn > n * m)
            rc = ERR_INPUT_NN_CNT;
    }

    if (rc == OK && nn != 0)
    {
        printf("Введите %d ненулевых элементов и индексы их строк ", nn);
        if (!is_vector)
            printf("и столбцов ");
        printf("в формате\n\"элемент строка ");
        if (!is_vector)
            printf("столбец");
        printf("\"\n");

        for (int i = 0; i < nn && rc == OK; i++)
        {
            int cur_elem, row = 0, col = 0;

            int check = scanf("%d", &cur_elem);
            if (check == 0 || abs(cur_elem) > MAX_ELEMENT)
                rc = ERR_INPUT_ELEMENT;

            check = scanf("%d", &row);
            if (rc == OK && (check == 0 || row < 0 || row >= n))
                rc = ERR_INPUT_IDX;
            
            if (!is_vector)
            {
                check = scanf("%d", &col);
                if (rc == OK && (check == 0 || col < 0 || col >= n))
                    rc = ERR_INPUT_IDX;
            }

            if (rc == OK && matr->data[row][col] != 0)
                rc = ERR_REPEAT;
            
            if (rc == OK)
                matr->data[row][col] = cur_elem;
        }
    }

    return rc;
}

int sparse_to_std(matrix_sparse_t *from, matrix_std_t *to)
{
    int rc = OK;
    if (to->data)
        free_std_matrix(to);

    to->rows = from->rows;
    to->columns = from->columns;

    to->data = allocate_matrix(to->rows, to->columns);

    if (!to->data)
        rc = ERR_MEMORY;
    else
    {
        for (int i = 0; i < to->rows; i++)
            for (int j = 0; j < to->columns; j++)
                to->data[i][j] = 0;

        node_t node = from->JA;
        int col = 0;

        while(node.next)
        {
            for (int i = node.index; i < node.next->index; i++)
                to->data[from->IA[i]][col] = from->A[i];

            node = *node.next;
            col++;
        }
    }

    return rc;
}

int std_to_sparse(matrix_std_t *from, matrix_sparse_t *to)
{
    int rc = OK;
    if (to->A)
        free_sparse_matrix(to);

    int cnt = 0, col_cnt = 0;

    to->rows = from->rows;
    to->columns = from->columns;

    to->JA.index = 0;
    node_t *prev;
    prev = &to->JA;

    to->nn_cnt = cnt_nn_elements(from);

    to->A = malloc(to->nn_cnt * sizeof(int));
    to->IA = malloc(to->nn_cnt * sizeof(int));

    if (!to->A || !to->IA)
        rc = ERR_MEMORY;
    else
    {
        for (int j = 0; j < to->columns; j++)
        {
            col_cnt = 0;
            node_t *cur_node = (node_t*)malloc(sizeof(node_t));
            for (int i = 0; i < to->rows; i++)
            {
                if (from->data[i][j] != 0)
                {
                    to->A[cnt] = from->data[i][j];
                    to->IA[cnt] = i;
                    cnt++;
                    col_cnt++;
                }
            }
            prev->next = cur_node;
            cur_node->index = prev->index + col_cnt;
            prev = cur_node;
        }
        prev->next = NULL;
    }

    return rc;
}

int cnt_nn_elements(matrix_std_t *matr)
{
    int cnt = 0;
    for (int i = 0; i < matr->rows; i++)
        for (int j = 0; j < matr->columns; j++)
            if (matr->data[i][j] != 0)
                cnt++;
    return cnt;
}

void print_std_matrix(matrix_std_t *matr)
{
    printf("\nРазреженная матрица в стандартном виде\n\n");

    if (matr->rows > MAX_OUTPUT_SIZE || matr->columns > MAX_OUTPUT_SIZE)
        printf("Размеры матрицы слишком большие для вывода в стандартном виде\n");
    else
    {
        for (int i = 0; i < matr->rows; i++)
        {
            for (int j = 0; j < matr->columns; j++)
                printf("%4d ", matr->data[i][j]);
            printf("\n");
        }   
        printf("\n");
    }
}

void print_sparse_matrix(matrix_sparse_t *matr)
{
    printf("\nРазреженная матрица в виде 3 объектов\n\n");
    printf("A: ");
    for (int i = 0; i < matr->nn_cnt; i++)
        printf("%d ", matr->A[i]);

    printf("\n\nIA: ");
    for (int i = 0; i < matr->nn_cnt; i++)
        printf("%d ", matr->IA[i]);

    printf("\n\nJA: ");
    node_t node = matr->JA;
    while(node.next)
    {
        printf("%d ", node.index);
        node = *node.next;
    }
    printf("%d\n\n", node.index);
}

void input_matrix(matrix_std_t *m_std, matrix_sparse_t *m_sprs, int vect)
{
    int rc = OK;

    int small_choice = choose_form(1);

    if (small_choice == 1)
        rc = input_std_matr(m_std, vect);
    else
        rc = input_not_null_elements(m_std, vect);

    if (rc == OK)
        std_to_sparse(m_std, m_sprs);

    if (rc == OK && vect)
        printf("\nВектор-столбец успешно добавлен\n\n");
    else if (rc == OK)
        printf("\nМатрица успешно добавлена\n\n");
    
    print_error(rc);
}

void print_matrix(matrix_std_t *m_std, matrix_sparse_t *m_sprs, int vect)
{
    int rc = OK;

    if (!m_std->data && !m_sprs->A)
    {
        if (vect)
            rc = ERR_NO_VECTOR;
        else
            rc = ERR_NO_MATRIX;
    }
    else
    {
        int small_choice = choose_form(0);
        if (small_choice == 1)
        {
            if (!m_std->data)
                sparse_to_std(m_sprs, m_std);
            print_std_matrix(m_std);
        }
        else
        {
            if (!m_sprs->A)
                std_to_sparse(m_std, m_sprs);
            print_sparse_matrix(m_sprs);
        }
    }

    print_error(rc);
}

void print_error(int code)
{
    switch (code)
    {
        case ERR_MEMORY:
            printf("\nОшибка при выделении памяти\n\n");
            break;
        case ERR_INPUT_MATR_SIZE:
            printf("\nОшибка при вводе размеров\n\n");
            break;
        case ERR_INPUT_ELEMENT:
            printf("\nОшибка при вводе элемента\n\n");
            break;
        case ERR_INPUT_NN_CNT:
            printf("\nОшибка при вводе количества ненулевых элементов\n\n");
            break;
        case ERR_INPUT_IDX:
            printf("\nОшибка при вводе индекса ненулевого элемента\n\n");
            break;
        case ERR_REPEAT:
            printf("\nЭлемент с введенным индексом уже существует\n\n");
            break;
        case ERR_NO_MATRIX:
            printf("\nМатрица не существует. Введите ее вручную или сгенерируйте, выбрав соответствующий пункт меню\n\n");
            break;
        case ERR_NO_VECTOR:
            printf("\nВектор-столбец не существует. Введите его вручную или сгенерируйте, выбрав соответствующий пункт меню\n\n");
            break;
        case ERR_MULTI:
            printf("\nНесоответствие количества столбцов матрицы количеству элементов вектора-столбца\n\n");
            break;
        case ERR_PERCENT:
            printf("\nОшибка при вводе процента заполненности\n\n");
            break;
        default:
            break;
    }
}