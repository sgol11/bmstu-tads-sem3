#include "io_file.h"

int download_table(char *file_name, car_t *cars, int *n)
{
    int rc = OK;
    int use_init_table = 1;

    printf("Выбор исходной таблицы с информацией об автомобилях\n\n");

    printf("Введите один из вариантов:\n"
    "- название файла с исходной таблицей\n"
    "- 1, если хотите использовать таблицу по умолчанию %s\n"
    "- 2, если не хотите использовать исходную таблицу\n\n", DEFAULT_FILE_NAME);

    printf("Ваш ответ: ");
    get_str(file_name);
    printf("\n");

    if (strlen(file_name) == 1 && atoi(file_name) == 1)
    {
        use_init_table = 1;
        file_name = DEFAULT_FILE_NAME;
    }
    else if (strlen(file_name) == 1 && atoi(file_name) == 2)
    {
        *n = 0;
        use_init_table = 0;
    }

    if (use_init_table)
        rc = read_table(file_name, cars, n);

    if (rc == ERR_NO_FILE)
    {
        printf("Указанный файл не найден. Хотите ли вы использовать уже существующий\n"
        "файл с информацией об автомобилях \"%s\"?\n1 - Да\n2 - Нет\n\n", DEFAULT_FILE_NAME);
        printf("Ваш выбор: ");

        char choice[MAX_STR_LEN];
        char *tmp_p = fgets(choice, MAX_STR_LEN, stdin);

        while (tmp_p == NULL || (atoi(choice) != 1 && atoi(choice) != 2))
        {
            printf(" Ошибка ввода: необходимо ввести номер одного из предложенных вариантов\n\n");
            printf("Ваш выбор: ");
            tmp_p = fgets(choice, MAX_STR_LEN, stdin);
        }
        printf("\n");

        if (atoi(choice) == 1)
        {
            use_init_table = 1;
            file_name = DEFAULT_FILE_NAME;
            rc = read_table(file_name, cars, n);
        }
        else
        {
            use_init_table = 0;
            *n = 0;
        }
    }

    if (use_init_table)
        printf("Используется таблица из файла \"%s\"\n", file_name);
    else
        printf("Исходная таблица пуста\n");

    return rc;
}

int read_table(char *file_name, car_t *cars, int *n)
{
    int rc = OK;
    char str[MAX_STR_LEN];
    car_t car;
    int tmp1 = 0, tmp2 = 0;
    *n = 0;

    FILE *file = fopen(file_name, "r");

    if (!file)
        rc = ERR_NO_FILE;
    else
    {
        while (!feof(file) && !ferror(file) && rc == OK)
        {
            rc = fget_str(file, car.brand);
            if (rc == OK)
                rc = fget_str(file, car.country);
            if (rc == OK)
                rc = fget_int(file, &car.price);
            if (rc == OK)
                rc = fget_str(file, car.color);
            if (rc == OK)
                rc = fget_int(file, &tmp1);

            if (rc == OK && fget_int(file, &tmp2) == OK)
            {
                car.is_new = FALSE;
                car.condition.used_car.release_year = tmp1;
                car.condition.used_car.mileage = tmp2;
                if (rc == OK)
                    rc = fget_int(file, &car.condition.used_car.repairs_num);
                if (rc == OK)
                    rc = fget_int(file, &car.condition.used_car.owners_num);
                if (rc == OK)
                    fget_str(file, str);
            }
            else if (rc == OK)
            {
                car.is_new = TRUE;
                car.condition.new_car.warranty = tmp1;
            }
            
            if (rc == OK)
                cars[(*n)++] = car;
            else
            {
                print_error_io_file(rc);
                printf(" Не все записи из файла загружены\n\n");
            }
        }
        fclose(file);
    }

    return rc;
}

void print_table(car_t *cars, int n)
{
    printf("|-----|--------------|--------------|------------|----------|-----------"
           "|----------|-------------|--------|------------|---------------|\n");
    printf("| №   | Марка машины | Страна       | Цена       | Цвет     | Состояние "
           "| Гарантия | Год выпуска | Пробег | Количество | Количество    |\n");
    printf("|     |              |              |            |          |           "
           "|          |             |        | ремонтов   | собственников |\n");
    printf("|-----|--------------|--------------|------------|----------|-----------"
           "|----------|-------------|--------|------------|---------------|\n");
    for (int i = 0; i < n; i++)
    {
        printf("| %-3d | %-12s | %-12s | %-10d | %-8s ", i + 1, cars[i].brand, cars[i].country, 
        cars[i].price, cars[i].color);

        if (cars[i].is_new == TRUE)
            printf("| new       | %-8d | -           | -      | -          "
            "| -             |\n", cars[i].condition.new_car.warranty);
        else
            printf("| used      | -        | %-11d | %-6d | %-10d | %-13d | \n", 
            cars[i].condition.used_car.release_year, cars[i].condition.used_car.mileage, 
            cars[i].condition.used_car.repairs_num, cars[i].condition.used_car.owners_num);
    }
    printf("|-----|--------------|--------------|------------|----------|-----------"
           "|----------|-------------|--------|------------|---------------|\n");
}

void rewrite_table_to_file(char *file_name, car_t *cars, int n)
{
    FILE *f = fopen(file_name, "w");
    for (int i = 0; i < n; i++)
    {
        car_t car = cars[i];

        if (i != 0)
            fprintf(f, "\n");

        fprintf(f, "%s\n%s\n%d\n%s\n", car.brand, car.country, car.price, car.color);

        if (car.is_new)
            fprintf(f, "%d\n", car.condition.new_car.warranty);
        else
        {
            fprintf(f, "%d\n%d\n%d\n%d\n", car.condition.used_car.release_year, 
            car.condition.used_car.mileage, car.condition.used_car.repairs_num, 
            car.condition.used_car.owners_num);
        }
    }
    fclose(f);
}

void print_error_io_file(int code)
{
    switch (code)
    {
        case ERR_READ:
            printf(" Ошибка при чтении строки из файла\n");
            break;
        case ERR_EMPTY_STR:
            printf(" Ошибка: пустая строка на месте необходимой записи в файле\n");
            break;
        case ERR_NEG_NUM:
            printf(" Ошибка: отрицательное число в файле\n");
            break;
        default:
            break;
    }
}