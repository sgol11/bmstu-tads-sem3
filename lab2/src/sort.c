#include "../inc/sort.h"

void sort_keys(car_t *cars, key_t *keys, int n)
{
    form_keys_table(cars, keys, n);
    qsort_keys(keys, n);
}

void form_keys_table(car_t *cars, key_t *keys, int n)
{
    for (int i = 0; i < n; i++)
    {
        keys[i].index = i;
        keys[i].field = cars[i].price;
    }
}

int bubble_sort_keys(key_t *keys, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (keys[j].field > keys[j + 1].field)
                swap(&keys[j], &keys[j + 1]);
        }
    }

    return OK;
}

void swap(key_t *key1, key_t *key2)
{
    key_t tmp = *key1;
    *key1 = *key2;
    *key2 = tmp;
}

int qsort_keys(key_t *keys, int n)
{
    qsort(keys, n, sizeof(key_t), (int(*)(const void *, const void *)) compare_keys);

    return OK;
}

int compare_keys(const key_t *key1, const key_t *key2)
{
    return key1->field - key2->field;
}

int qsort_table(car_t *cars, int n)
{
    qsort(cars, n, sizeof(car_t), (int(*)(const void *, const void *)) compare_cars);
    
    return OK;
}

int print_sorted_table(car_t *cars, int n)
{
    qsort_table(cars, n);

    printf("Отсортированная (по ценам) исходная таблица\n\n");
    print_table(cars, n);

    return OK;
}

int compare_cars(const car_t *car1, const car_t *car2)
{
    return car1->price - car2->price;
}

void print_sorted_keys(key_t *keys, int n)
{
    printf("Отсортированная (по ценам) таблица ключей\n\n");
    printf("|-----|-------------------------|--------------|\n");
    printf("| №   | Индекс исходной таблицы | Цена         |\n");
    printf("|-----|-------------------------|--------------|\n");
    for (int i = 0; i < n; i++)
        printf("| %-3d | %-23d | %-12d |\n", i + 1, keys[i].index + 1, keys[i].field);
    printf("|-----|-------------------------|--------------|\n\n");
}

void print_sorted_table_with_keys(car_t *cars, key_t *keys, int n)
{
    printf("Отсортированная (по ценам) исходная таблица с использованием отсортированной таблицы ключей\n\n");
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
        car_t cur_car = cars[keys[i].index];

        printf("| %-3d | %-12s | %-12s | %-10d | %-8s ", i + 1, cur_car.brand, cur_car.country, 
        cur_car.price, cur_car.color);

        if (cur_car.is_new == TRUE)
            printf("| new       | %-8d | -           | -      | -          "
            "| -             |\n", cur_car.condition.new_car.warranty);
        else
            printf("| used      | -        | %-11d | %-6d | %-10d | %-13d | \n", 
            cur_car.condition.used_car.release_year, cur_car.condition.used_car.mileage, 
            cur_car.condition.used_car.repairs_num, cur_car.condition.used_car.owners_num);
    }
    printf("|-----|--------------|--------------|------------|----------|-----------"
           "|----------|-------------|--------|------------|---------------|\n");
}