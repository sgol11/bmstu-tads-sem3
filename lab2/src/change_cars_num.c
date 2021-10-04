#include "../inc/change_cars_num.h"

int add_car(char *file_name, car_t *cars, int *n)
{
    int rc = OK;
    car_t car;

    if (*n >= MAX_CARS_NUM)
    {
        printf("Невозможно добавить запись: достигнут максимальный размер таблицы\n");
        rc = ERR_MANY_CARS;
    }
    else
    {
        printf("Ввод информации о машине №%d\n\n", *n + 1);

        printf("Введите марку автомобиля: ");
        get_str(car.brand);

        printf("Введите страну-производитель автомобиля: ");
        get_str(car.country);

        printf("Введите цену автомобиля: ");
        get_int(&car.price);

        printf("Введите цвет автомобиля: ");
	    get_str(car.color);

        printf("Эта машина новая?\n1)Да\n2)Нет\nВаш выбор: ");

        char choice[MAX_STR_LEN];

        while (fgets(choice, MAX_STR_LEN, stdin) == NULL || strlen(choice) > 2 || 
        (atoi(choice) != 1 && atoi(choice) != 2))
        {
            printf("Ошибка ввода: необходимо ввести номер одного из предложенных вариантов\n\n");
            printf("Ваш выбор: ");
        }

        car.is_new = (atoi(choice) == 1) ? TRUE : FALSE;

        if (car.is_new)
        {
            printf("Введите гарантию автомобиля(в годах): ");
            get_int(&car.condition.new_car.warranty);
        }
        else
        {
            printf("Введите год выпуска автомобиля: ");
            get_int(&car.condition.used_car.release_year);

            printf("Введите пробег автомобиля(в км): ");
            get_int(&car.condition.used_car.mileage);

            printf("Введите количество ремонтов автомобиля: ");
            get_int(&car.condition.used_car.repairs_num);

            printf("Введите количество собственников: ");
            get_int(&car.condition.used_car.owners_num);
        }

        cars[(*n)++] = car;
    
        FILE *f = fopen(file_name, "a+");

        fprintf(f, "\n%s\n%s\n%d\n%s\n", car.brand, car.country, car.price, car.color);

        if (car.is_new)
            fprintf(f, "%d\n", car.condition.new_car.warranty);
        else
        {
            fprintf(f, "%d\n%d\n%d\n%d\n", car.condition.used_car.release_year, 
            car.condition.used_car.mileage, car.condition.used_car.repairs_num, 
            car.condition.used_car.owners_num);
        }

        printf("\nИнформация о машине успешно добавлена. Количество записей в новой таблице: %d\n", *n);

        fclose(f);
    }

    return rc;
}

int delete_cars(char *file_name, car_t *cars, int *n)
{
    int rc = OK;
    int column, int_value;
    char str_value[MAX_STR_LEN];
    mybool bool_value;
    
    char tmp[MAX_STR_LEN];
    char *tmp_p;

    int init_n = *n;

    printf("Выберите поле, по которому вы хотите произвести удаление:\n\n"
           "1 - номер машины в таблице\n"
           "2 - марка\n"
           "3 - страна-производитель\n"
           "4 - цена\n"
           "5 - цвет\n"
           "6 - состояние\n"
           "7 - гарантия (для новых машин)\n"
           "8 - год выпуска (для не новых машин)\n"
           "9 - пробег (для не новых машин)\n"
           "10 - количество ремонтов (для не новых машин)\n"
           "11 - количество собственников (для не новых машин)\n\n");

    printf("Ваш выбор: ");

    tmp_p = fgets(tmp, MAX_STR_LEN, stdin);

    while (tmp_p == NULL || (atoi(tmp) < 1 || atoi(tmp) > 11))
    {
        printf(" Ошибка ввода: необходимо ввести номер одного из предложенных вариантов\n\n");
        printf("Ваш выбор: ");
        tmp_p = fgets(tmp, MAX_STR_LEN, stdin);
    }
    printf("\n");

    column = atoi(tmp);
    printf("Введите значение выбранного поля, записи с которым будут удалены\n");

    if (column == 2 || column == 3 || column == 5)
    {
        printf("(допустимые значения - корректные строки): ");
        get_str(str_value);
        delete_str_in_certain_column(cars, n, column, str_value);
    }
    else if (column == 6)
    {
        printf("(допустимые значения - \"new\" и \"used\"): ");
        get_str(tmp);

        while (strcmp(tmp, "new") != 0 && strcmp(tmp, "used") != 0)
        {
            printf("\n Ошибка: вам необходимо ввести \"new\" или \"used\"\n");
            printf("Ваш ввод: ");
            get_str(tmp);
        }

        if (strcmp(tmp, "new") == 0)
            bool_value = TRUE;
        else
            bool_value = FALSE;

        delete_bool_in_certain_column(cars, n, column, bool_value);
    }
    else
    {
        printf("(допустимые значения - целые положительные числа): ");
        get_int(&int_value);
        delete_int_in_certain_column(cars, n, column, int_value);
    }

    rewrite_table_to_file(file_name, cars, *n);

    printf("\nУдалено %d строк(-и)\n", init_n - *n);

    return rc;
}

void delete_str_in_certain_column(car_t *cars, int *n, int col, char *val)
{
    char cur_car[MAX_STR_LEN];

    for (int i = 0; i < *n; i++)
    {
        switch (col)
        {
            case 2:
                strcpy(cur_car, cars[i].brand);
                break;
            case 3:
                strcpy(cur_car, cars[i].country);
                break;
            case 5:
                strcpy(cur_car, cars[i].color);
                break;
            default:
                break;
        }

        if (strcmp(cur_car, val) == 0)
        {
            for (int j = i; j < *n; j++)
                cars[j] = cars[j + 1];
            i--;
            (*n)--;
        }
    }
}

void delete_bool_in_certain_column(car_t *cars, int *n, int col, mybool val)
{
    for (int i = 0; i < *n; i++)
    {
        if (cars[i].is_new == val)
        {
            for (int j = i; j < *n; j++)
                cars[j] = cars[j + 1];
            i--;
            (*n)--;
        }
    }
}

void delete_int_in_certain_column(car_t *cars, int *n, int col, int val)
{
    int cur_car;

    for (int i = 0; i < *n; i++)
    {
        switch (col)
        {
            case 1:
                cur_car = i + 1;
                break;
            case 4:
                cur_car = cars[i].price;
                break;
            case 7:
                cur_car = cars[i].condition.new_car.warranty;
                break;
            case 8:
                cur_car = cars[i].condition.used_car.release_year;
                break;
            case 9:
                cur_car = cars[i].condition.used_car.mileage;
                break;
            case 10:
                cur_car = cars[i].condition.used_car.repairs_num;
                break;
            case 11:
                cur_car = cars[i].condition.used_car.owners_num;
                break;
            default:
                break;
        }

        if (cur_car == val)
        {
            for (int j = i; j < *n; j++)
                cars[j] = cars[j + 1];
            i--;
            (*n)--;
        }
    }
}