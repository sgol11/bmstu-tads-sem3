#include "general.h"
#include "menu.h"
#include "structs.h"
#include "io_file.h"
#include "change_cars_num.h"
#include "find.h"
#include "sort.h"
#include "analysis.h"

int main(void)
{
    setbuf(stdout, NULL);
    setlocale(LC_ALL, "");

    char file_name[100] = "";

    int err_code = OK;
    int choice = 1;

    car_t cars_table[MAX_CARS_NUM];
    key_t keys_table[MAX_CARS_NUM];
    int n = 0;

    show_info();

    err_code = download_table(file_name, cars_table, &n);

    while (choice != EXIT)
    {
        choice = choose_action();

        switch (choice)
        {
            case PRINT_TABLE:
                print_table(cars_table, n);
                break;
            case ADD:
                add_car(file_name, cars_table, &n);
                break;
            case DEL:
                delete_cars(file_name, cars_table, &n);
                break;
            case SORT_KEYS:
                sort_keys(cars_table, keys_table, n);
                print_sorted_keys(keys_table, n);
                break;
            case SORT_TABLE:
                print_sorted_table(cars_table, n);
                break;
            case SORT_TABLE_WITH_KEYS:
                sort_keys(cars_table, keys_table, n);
                print_sorted_keys(keys_table, n);
                print_sorted_table_with_keys(cars_table, keys_table, n);
                break;
            case ANALYSIS:
                analyse_table_sort(cars_table, n);
                break;
            case FIND:
                find_in_table(cars_table, n);
                break;
            case NEW_INIT_TABLE:
                err_code = download_table(file_name, cars_table, &n);
                break;
        }
    }

    printf("Выход\n");

    return err_code;
}