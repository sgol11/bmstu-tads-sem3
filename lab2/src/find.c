#include "../inc/find.h"

int find_in_table(car_t *cars, int n)
{
    char input_brand[MAX_STR_LEN];
    int lo, hi;
    int prices[MAX_CARS_NUM];
    int j = 0;

    printf("Вы хотите вывести цены не новых машин указанной марки\n" 
           "с одним предыдущим собственником и отсутствием ремонта,\n"
           "в указанном диапазоне цен\n\n");

    printf("Введите марку автомобиля: ");
    get_str(input_brand);

    printf("Введите нижнюю границу диапазона цен: ");
    get_int(&lo);

    printf("Введите верхнюю границу диапазона цен: ");
    get_int(&hi);
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        if (cars[i].is_new == FALSE && strcmp(cars[i].brand, input_brand) == 0)
        {
            if (cars[i].condition.used_car.repairs_num == 0 &&
                cars[i].condition.used_car.owners_num == 1)
            {
                if (cars[i].price >= lo && cars[i].price <= hi)
                    prices[j++] = cars[i].price;
            }
        }
    }

    print_prices(prices, j);

    return OK;
}

int print_prices(int *prices, int n)
{
    if (n == 0)
        printf("Не удалось найти машины, удовлетворяющие параметрам\n");
    else
    {
        printf("Цены машин, удовлетворяющих заданным параметрам:\n\n");
        for (int i = 0; i < n; i++)
            printf("%d\n", prices[i]);
    }

    return OK;
}