#include "../inc/get_vars.h"

int fget_str(FILE *f, char *str)
{
    int rc = OK;

    if (!fgets(str, MAX_STR_LEN, f))
		rc = ERR_READ;
    if (rc == OK)
    {
        if (str[strlen(str) - 1] != '\n')
		    rc = ERR_LONG_STR;
        str[strlen(str) - 1] = '\0';
        if (strlen(str) == 0)
	        rc = ERR_EMPTY_STR;
    }

    return rc;
}

int fget_int(FILE *f, int *num)
{
    int rc = OK;

    char str[MAX_STR_LEN];
    char ch;

    rc = fget_str(f, str);
    if (rc == OK)
    {
        if (sscanf(str, "%d%c", num, &ch) != 1 || *num < 0)
            rc = ERR_NEG_NUM;
    }

    return rc;
}

void get_str(char *str)
{
    int rc = OK;

    do
    {
        rc = OK;

        char *tmp_p = fgets(str, MAX_STR_LEN, stdin);

        if (tmp_p == NULL)
		    rc = ERR_READ;
	    else if (str[strlen(str) - 1] != '\n')
        {
		    rc = ERR_LONG_STR;
            while (str[strlen(str) - 1] != '\n')
                fgets(str, MAX_STR_LEN, stdin);
        }
	    else
		    str[strlen(str) - 1] = '\0';

	    if (strlen(str) == 0)
		    rc = ERR_EMPTY_STR;

        if (rc != OK)
        {
            print_error_change_cars_num(rc);
            printf(" Повторите ввод: ");
        }

    } while (rc != OK);
}

void get_int(int *num)
{
    int rc = OK;

    char str[MAX_STR_LEN];
    
    get_str(str);
    int check = sscanf(str, "%d", num);

	while (check != 1 || *num < 0)
	{
        rc = ERR_NEG_NUM;
        print_error_change_cars_num(rc);
        printf(" Повторите ввод: ");
        get_str(str);
		check = sscanf(str, "%d", num); 
	}
}

void print_error_change_cars_num(int code)
{
    switch (code)
    {
        case ERR_READ:
            printf(" Ошибка при чтении строки. Проверьте корректность ввода\n");
            break;
        case ERR_LONG_STR:
            printf(" Ошибка: превышена максимальная длина строки\n");
            break;
        case ERR_EMPTY_STR:
            printf(" Ошибка: пустая строка\n");
            break;
        case ERR_NEG_NUM:
            printf(" Ошибка: должно быть введено целое неотрицательное число\n");
            break;
        default:
            break;
    }
}