#include "main.h"
#include "error_processing.h"
#include "input.h"
#include "normalized_form.h"
#include "division.h"
#include "output.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    setlocale(LC_ALL, " ");

    print_info();

    int error_code = OK;
    
    int_number dividend;
    real_number divisor;

    real_number normal_dividend, normal_divisor;
    real_number quotient;
    
    printf("Введите делимое:\n");
    error_code = input_int(&dividend);
     
    if (error_code == OK)
    {
        normalize_int(&dividend, &normal_dividend);
        
        printf("\nВведите делитель:\n");
        error_code = input_real(&divisor);

        if (error_code == OK)
        {
            error_code = normalize_real(&divisor, &normal_divisor);

            if (error_code == OK)
            {
                error_code = division(&normal_dividend, &normal_divisor, &quotient);
                
                if (error_code == OK)
                {
                    rounding(&quotient);
                    printf("\nРезультат деления:\n");
                    print_result(&quotient);
                }
            }
        }
    }

    print_error(error_code);

    return error_code;
}

void print_info()
{
    printf("===============================================================================\n");
    printf("Программа предназначена для деления целого числа на вещественное,\n\
когда числа выходят за разрядную сетку ПК.\n\n");
    printf("Допустимые символы: '+', '-', '.', 'E', 'e', цифры от '0' до '9'.\n");
    printf("Для целого числа: количество цифр не более 30.\n");
    printf("Для вещественного числа: длина мантиссы не более 30 цифр, порядка - не более 5.\n");
    printf("===============================================================================\n");
    printf("\n");
}
