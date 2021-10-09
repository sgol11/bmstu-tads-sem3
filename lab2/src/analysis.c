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

int analyse_table_sort(car_t *cars, int n)
{
    uint64_t start, end;
    double s_1, s_2, s_3, s_4;

    car_t tmp[MAX_CARS_NUM];
    copy_table(tmp, cars, n);

    key_t keys[MAX_CARS_NUM];
    form_keys_table(tmp, keys, n);

    printf("Анализ эффективности работы программы при сортировке данных в исходной\n"
           "таблице и таблице ключей\n\n");

    printf("Количество записей в таблице: %d\n\n", n);

    printf("Время сортировки (в секундах)\n\n");
    
    printf("|-----------------------------------|-----------------------------------|\n");
    printf("|        Сортировка пузырьком       |         Быстрая сортировка        |\n");
    printf("|-----------------------------------|-----------------------------------|\n");
    printf("| Исходная таблица | Таблица ключей | Исходная таблица | Таблица ключей |\n");
    printf("|-----------------------------------|-----------------------------------|\n");
    printf("|                  |                |                  |                |\n");
    
    start = tick();
    bubble_sort_table(tmp, n); 
    end = tick();
    s_1 = (double)(end - start) / GHZ;
    
    start = tick();
    bubble_sort_keys(keys, n);
    end = tick();
    s_2 = (double)(end - start) / GHZ;

    start = tick();
    qsort_table(tmp, n); 
    end = tick();
    s_3 = (double)(end - start) / GHZ;
    
    start = tick();
    qsort_keys(keys, n);
    end = tick();
    s_4 = (double)(end - start) / GHZ;

    printf("| %-16lf | %-14lf | %-16lf | %-14lf |\n", s_1, s_2, s_3, s_4);
    printf("|-----------------------------------|-----------------------------------|\n\n");

    printf("Объем занимаемой памяти (в байтах)\n\n");

    printf("|-----------------------------------|-----------------------------------|\n");
    printf("|         Исходная таблица          |          Таблица ключей           |\n");
    printf("|-----------------------------------|-----------------------------------|\n");
    printf("| %-33lld | %-33lld |\n", sizeof(car_t) * n, sizeof(key_t) * n);
    printf("|-----------------------------------|-----------------------------------|\n\n");

    printf("Эффективность по разным параметрам (в процентах)\n\n");

    printf("|-----------------------------------|-------------------------------|-------------------------------|\n");
    printf("| Объем памяти, занимаемый таблицей | Скорость сортировки исходной  | Скорость сортировки исходной  |\n");
    printf("| ключей относительно объема памяти | таблицы относительно скорости | таблицы относительно скорости |\n");
    printf("| исходной таблицы                  | сортировки таблицы ключей     | сортировки таблицы ключей     |\n");
    printf("|                                   | (пузырек)                     | (быстрая сортировка)          |\n");
    printf("|-----------------------------------|-------------------------------|-------------------------------|\n");

    if (n == 0)
        printf("| Невозможно сравнить               |");
    else
        printf("| %-33.2lf |", (double)(sizeof(key_t) * n) / (sizeof(car_t) * n) * 100);

    if (s_1 < 5e-7 || s_2 < 5e-7)
        printf(" Невозможно сравнить           |");
    else
        printf(" %-29.2lf |", s_1 / s_2  * 100);

    if (s_3 < 5e-7 || s_4 < 5e-7)
        printf(" Невозможно сравнить           |\n");
    else
        printf(" %-29.2lf |\n", s_3 / s_4  * 100);

    printf("|-----------------------------------|-------------------------------|-------------------------------|\n\n");

    return OK;
}

void copy_table(car_t *dst, car_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        strcpy(dst[i].brand, src[i].brand);
        strcpy(dst[i].country, src[i].country);
        dst[i].price = src[i].price;
        strcpy(dst[i].color, src[i].color);

        if (src[i].is_new == TRUE)
        {
            dst[i].condition.new_car.warranty = src[i].condition.new_car.warranty;
        }
        else
        {
            dst[i].condition.used_car.release_year = src[i].condition.used_car.release_year;  
            dst[i].condition.used_car.mileage = src[i].condition.used_car.mileage;  
            dst[i].condition.used_car.repairs_num = src[i].condition.used_car.repairs_num;   
            dst[i].condition.used_car.owners_num = src[i].condition.used_car.owners_num;              
        }
    }
}