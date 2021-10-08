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

int full_analysis(void)
{
    uint64_t start, end;
    double s_1[5], s_2[5], s_3[5], s_4[5];

    char files[5][30] = { ANALYSIS_10, ANALYSIS_50, ANALYSIS_100, ANALYSIS_200, ANALYSIS_500 };
    int num[5] = { 10, 50, 100, 200, 500 };

    printf("Полный анализ эффективности сортировок для заданных по умолчанию таблиц различных размеров\n\n");

    printf("Время сортировки (в секундах)\n\n");
    
    printf("|--------------------|-----------------------------------|-----------------------------------|\n");
    printf("| Количество записей |        Сортировка пузырьком       |         Быстрая сортировка        |\n");
    printf("|                    |-----------------------------------|-----------------------------------|\n");
    printf("|                    | Исходная таблица | Таблица ключей | Исходная таблица | Таблица ключей |\n");
    printf("|--------------------|-----------------------------------|-----------------------------------|\n");

    for (int i = 0; i < 5; i++)
    {
        car_t tmp_table[MAX_CARS_NUM];
        key_t keys[MAX_CARS_NUM];
        int n = 0;
        read_table(files[i], tmp_table, &n);
        form_keys_table(tmp_table, keys, n);

        start = tick();
        bubble_sort_table(tmp_table, n); 
        end = tick();
        s_1[i] = (double)(end - start) / GHZ;
        
        start = tick();
        bubble_sort_keys(keys, n); 
        end = tick();
        s_2[i] = (double)(end - start) / GHZ;

        start = tick();
        qsort_table(tmp_table, n); 
        end = tick();
        s_3[i] = (double)(end - start) / GHZ;

        start = tick();
        qsort_keys(keys, n); 
        end = tick();
        s_4[i] = (double)(end - start) / GHZ;

        printf("| %-18d | %-16lf | %-14lf | %-16lf | %-14lf |\n", num[i], s_1[i], s_2[i], s_3[i], s_4[i]);
    }

    printf("|--------------------|-----------------------------------|-----------------------------------|\n\n");

    printf("Объем занимаемой памяти (в байтах)\n\n");

    printf("|--------------------|-----------------------------------|-----------------------------------|\n");
    printf("| Количество записей |         Исходная таблица          |          Таблица ключей           |\n");
    printf("|--------------------|-----------------------------------|-----------------------------------|\n");

    long long int m_1[5], m_2[5];

    for (int i = 0; i < 5; i++)
    {
        m_1[i] = sizeof(car_t) * num[i];
        m_2[i] = sizeof(key_t) * num[i];
        printf("| %-18d | %-33lld | %-33lld |\n", num[i], m_1[i], m_2[i]);
    }

    printf("|--------------------|-----------------------------------|-----------------------------------|\n\n");

    printf("Эффективность по разным параметрам (в процентах)\n\n");

    printf("|--------------------|-----------------------------------|-------------------------------|-------------------------------|\n");
    printf("| Количество записей | Объем памяти, занимаемый таблицей | Скорость сортировки исходной  | Скорость сортировки исходной  |\n");
    printf("|                    | ключей относительно объема памяти | таблицы относительно скорости | таблицы относительно скорости |\n");
    printf("|                    | исходной таблицы                  | сортировки таблицы ключей     | сортировки таблицы ключей     |\n");
    printf("|                    |                                   | (пузырек)                     | (быстрая сортировка)          |\n");
    printf("|--------------------|-----------------------------------|-------------------------------|-------------------------------|\n");

    for (int i = 0; i < 5; i++)
    {
        printf("| %-18.2d | %-33.2lf | %-29.2lf | %-29.2lf |\n", num[i], (double)m_2[i] / m_1[i] * 100, 
        s_1[i] / s_2[i]  * 100, s_3[i]  / s_4[i]  * 100);
    }

    printf("|--------------------|-----------------------------------|-------------------------------|-------------------------------|\n");

    return OK;
}

int analyse_cur_table(car_t *cars, int n)
{
    uint64_t start, end;
    double s_1, s_2, s_3, s_4;

    car_t tmp[MAX_CARS_NUM];
    copy_table(tmp, cars, n);

    key_t keys[MAX_CARS_NUM];
    form_keys_table(tmp, keys, n);

    printf("Анализ эффективности сортировок для текущей таблицы\n\n");

    printf("Время сортировки (в секундах)\n\n");
    
    printf("|-----------------------------------|-----------------------------------|\n");
    printf("|        Сортировка пузырьком       |         Быстрая сортировка        |\n");
    printf("|-----------------------------------|-----------------------------------|\n");
    printf("| Исходная таблица | Таблица ключей | Исходная таблица | Таблица ключей |\n");
    printf("|-----------------------------------|-----------------------------------|\n");
    
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

    if (s_1 < 1e-6 || s_2 < 1e-6)
        printf(" Невозможно сравнить           |");
    else
        printf(" %-29.2lf |", s_1 / s_2  * 100);

    if (s_3 < 1e-6 || s_4 < 1e-6)
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