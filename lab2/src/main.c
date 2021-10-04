#include "../inc/general.h"
#include "../inc/menu.h"
#include "../inc/structs.h"
#include "../inc/io_file.h"
#include "../inc/change_cars_num.h"
#include "../inc/find.h"

int main(void)
{
    setbuf(stdout, NULL);
    setlocale(LC_ALL, "");

    char file_name[MAX_STR_LEN] = "";

    int err_code = OK;
    int choice = 1;

    car_t cars_table[MAX_CARS_NUM];
    int n = 0;

    show_info();

    err_code = download_table(file_name, cars_table, &n);

    while (choice != EXIT)
    {
        choose_action(&choice);

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