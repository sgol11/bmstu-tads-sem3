#include "error_processing.h"

void print_error(int code)
{
    printf("\n");
    switch (code)
    {
        case ERR_DIVIDEND:
            printf("Ошибка: некорректный ввод делимого\n");
            break;
        case ERR_DIVISOR:
            printf("Ошибка: некорректный ввод делителя\n");
            break;
        case ERR_OVERFLOW_DIVIDEND:
            printf("Ошибка: переполнение в делимом\n");
            break;
        case ERR_OVERFLOW_DIVISOR:
            printf("Ошибка: переполнение в мантиссе делителя\n");
            break;
        case ERR_OVERFLOW_EXP:
            printf("Ошибка: переполнение в порядке делителя\n");
            break;
        case ERR_DIVISION_BY_ZERO:
            printf("Ошибка: деление на ноль\n");
            break;
        case ERR_OVERFLOW_RES_EXP:
            printf("Ошибка: переполнение порядка в результате вычислений\n");
            break;
        default:
            break;
    }
}