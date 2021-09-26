#include "input.h"

int input_int(int_number *num)
{
    initialization_int(num);

    int code = OK;

    char ch;
    int idx = 0, first_zero = 1;
    
    ch = getchar();
    while(ch != EOF && ch != '\n' && code == OK) 
    {
        if (first_zero && ch == '0')
            ;
        else if (idx == 0)
        {
            if (ch == '-' || ch == '+')
                num->sign = ch;
            else if (ch >= '1' && ch <= '9')
            {
                first_zero = 0;
                num->sign = '+';
                num->number[num->number_len++] = ch;
            }
            else
                code = ERR_DIVIDEND;
        }
        else
        {
            first_zero = 0;
            if (ch >= '0' && ch <= '9' && num->number_len < MAX_MANTISSA_SIZE)
                num->number[num->number_len++] = ch;
            else if (num->number_len == MAX_MANTISSA_SIZE)
                code = ERR_OVERFLOW_DIVIDEND;
            else
                code = ERR_DIVIDEND;
        }

        idx++;
        ch = getchar();
    }
    if (idx == 0)
        code = ERR_DIVIDEND;

    return code;
}

void initialization_int(int_number *num)
{
    num->sign = '+';
    
    num->number_len = 0;
    for (int i = 0; i < MAX_MANTISSA_SIZE + 3; i++)
        num->number[i] = '0';
}

int input_real(real_number *num)
{
    initialization_real(num);

    int code = OK;

    char ch;
    int idx = 0, mantissa_idx = 0, exponent_idx = 0;
    int e = 0, dot = 0, first_zero = 1;
    int comp1 = 0, comp2 = 0;
    int exp_sign = 1;
    char tmp_exp[MAX_EXPONENT_SIZE + 1] = { '0' };
    
    ch = getchar();
    while(ch != EOF && ch != '\n' && code == OK) 
    {
        if (first_zero && ch == '0')
            ;
        else if (idx == 0)
        {
            code = process_sign(num, &mantissa_idx, ch, &dot, &e, &comp1);
            if (ch != '0')
                first_zero = 0;
            idx = 1;
        }
        else if (dot && !e)
        {
            code = process_after_dot(num, &mantissa_idx, ch, &e, &comp1);
        }
        else if (e)
        {
            if (ch == '-')
                exp_sign = -1;
            else if (ch == '+')
                exp_sign = 1;
            else
                code = process_after_e(tmp_exp, &exponent_idx, ch, &comp2);
        }
        else
        {
            code = process_digits(num, &mantissa_idx, ch, &dot, &e, &comp1);
            if (ch != '0')
                first_zero = 0;
        }
        
        ch = getchar();
    }
    
    tmp_exp[exponent_idx] = '\0';
    num->exponent = atoi(tmp_exp) * exp_sign;
    
    num->mantissa_len = mantissa_idx;

    if (comp1 == 0 || (e && comp2 == 0))
        code = ERR_DIVISOR;

    return code;
}

void initialization_real(real_number *num)
{
    num->sign = '+';

    num->mantissa_len = 0;
    for (int i = 0; i < MAX_MANTISSA_SIZE + 3; i++)
        num->mantissa[i] = '0';

    num->exponent = 0;
}

int process_sign(real_number *num, int *idx, char ch, int *dot, int *e, int *comp)
{
    int code = OK;

    if (ch == '-' || ch == '+')
        num->sign = ch;
    else if (ch >= '0' && ch <= '9')
    {
        num->sign = '+';
        num->mantissa[*idx] = ch;
        *idx = *idx + 1;
        *comp = 1;
    }
    else if (ch == '.')
    {
        num->sign = '+';
        *dot = 1;
        num->mantissa[*idx] = ch;
        *idx = *idx + 1;
        *comp = 1;
    }
    else if (ch == 'e' || ch == 'E')
    {
        num->sign = '+';
        *e = 1;
    }
    else
        code = ERR_DIVISOR;
    
    return code;
}

int process_after_dot(real_number *num, int *idx, char ch, int *e, int *comp)
{
    int code = OK;
    
    if (ch >= '0' && ch <= '9')
    {
        num->mantissa[*idx] = ch;
        *idx = *idx + 1;
        if (*idx == MAX_MANTISSA_SIZE + 2)
            code = ERR_OVERFLOW_DIVISOR;
        *comp = 1;
    }
    else if (ch == 'e' || ch == 'E')
        *e = 1;
    else
        code = ERR_DIVISOR;
    
    return code;
}

int process_after_e(char *num, int *idx, char ch, int *comp)
{
    int code = OK;
    
    if (ch >= '0' && ch <= '9')
    {
        num[*idx] = ch;
        *idx = *idx + 1;
        if (*idx == MAX_EXPONENT_SIZE + 1)
            code = ERR_OVERFLOW_EXP;
        *comp = 1;
    }
    else
        code = ERR_DIVISOR;
    
    return code;
}

int process_digits(real_number *num, int *idx, char ch, int *dot, int *e, int *comp)
{
    int code = OK;
    
    if (ch >= '0' && ch <= '9')
    {
        num->mantissa[*idx] = ch;
        *idx = *idx + 1;
        if (*idx == MAX_MANTISSA_SIZE + 1)
            code = ERR_OVERFLOW_DIVISOR;
        *comp = 1;
    }
    else if (ch == '.')
    {
        num->mantissa[*idx] = ch;
        *idx = *idx + 1;
        *dot = 1;
        *comp = 1;
    }
    else if (ch == 'e' || ch == 'E')
    {
        *e = 1;
    }
    else
        code = ERR_DIVISOR;
    
    return code;
}