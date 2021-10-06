#include "../inc/analysis.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ ( "rdtsc\n" : "=a" (low), "=d" (high) );

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

int cmp_table_and_keys(car_t *cars, int n)
{
    uint64_t start, end;
    double seconds_1, seconds_2;

    car_t tmp[MAX_CARS_NUM];
    copy_table(tmp, cars, n);

    key_t keys[MAX_CARS_NUM];

    printf("Сравнение эффективности работы программы при сортировке данных в исходной\n"
           "таблице и таблице ключей\n\n");
    
    printf("|--------------|------------------|------------------|\n");
    printf("|              | Исходная таблица | Таблица ключей   |\n");
    printf("|--------------|------------------|------------------|\n");
    
    start = tick();
    qsort_table(tmp, n); 
    end = tick();
    
    seconds_1 = (double)(end - start) / GHZ;
    
    start = tick();
    form_keys_table(cars, keys, n);
    qsort_keys(keys, n);
    end = tick();

    seconds_2 = (double)(end - start) / GHZ;

    printf("| Время(с)     | %-16lf | %-16lf |\n", seconds_1, seconds_2);
    printf("| Память(байт) | %-16lld | %-16lld |\n", sizeof(car_t) * n, sizeof(car_t) * n + sizeof(key_t) * n);
    printf("|--------------|------------------|------------------|\n");

    return OK;
}

int cmp_sorts(car_t *cars, int n)
{
    uint64_t start, end;
    double seconds_1, seconds_2;

    key_t keys[MAX_CARS_NUM];

    printf("Сравнение эффективности работы программы при использовании различных\n"
           "алгоритмов сортировки (в таблице ключей)\n\n");
    
    printf("|--------------|----------------------|--------------------|\n");
    printf("|              | Сортировка пузырьком | Быстрая сортировка |\n");
    printf("|--------------|----------------------|--------------------|\n");
    
    start = tick();
    form_keys_table(cars, keys, n);
    bubble_sort_keys(keys, n); 
    end = tick();
    
    seconds_1 = (double)(end - start) / GHZ;
    
    start = tick();
    form_keys_table(cars, keys, n);
    qsort_keys(keys, n);
    end = tick();

    seconds_2 = (double)(end - start) / GHZ;

    printf("| Время(с)     | %-20lf | %-18lf |\n", seconds_1, seconds_2);
    printf("|--------------|----------------------|--------------------|\n");

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