#include "normalized_form.h"

void normalize_int(int_number *init_int, real_number *normal_int)
{
    initialization_real(normal_int);

    normal_int->sign = init_int->sign;

    normal_int->mantissa_len = init_int->number_len;

    for (int i = 0; i < init_int->number_len; i++)
        normal_int->mantissa[i] = init_int->number[i];
    
    normal_int->exponent = init_int->number_len;
}

int normalize_real(real_number *init_real, real_number *normal_real)
{
    initialization_real(normal_real);

    int code = OK;

    normal_real->sign = init_real->sign;

    int dot_idx = -1, zeros_cnt = 0, zeros_end = 0;
    
    normal_real->mantissa_len = init_real->mantissa_len;

    int idx = 0;
    for (int i = 0; i < init_real->mantissa_len; i++)
    {
        if (init_real->mantissa[i] == '.')
            dot_idx = i;

        else if (dot_idx != -1)
        {
            if (init_real->mantissa[i] == '0' && !zeros_end)
                zeros_cnt++;
            else if (init_real->mantissa[i] != '0')
                zeros_end = 1;

            if (zeros_end)
                normal_real->mantissa[idx++] = init_real->mantissa[i];
        }

        else
            normal_real->mantissa[idx++] = init_real->mantissa[i];
    }
    
    if (dot_idx == -1)
    {
        dot_idx = init_real->mantissa_len;
    }
    else if ((dot_idx == 1 && init_real->mantissa[0] == '0') || dot_idx == 0)
    {
        dot_idx = (-1) * zeros_cnt;
        normal_real->mantissa_len -= (zeros_cnt + 1);
    }
    else
    {
        normal_real->mantissa_len -= 1;
    }
    
    normal_real->exponent = init_real->exponent + dot_idx;

    code = zero_check(normal_real->mantissa, normal_real->mantissa_len);
    return(code);
}


int zero_check(char *num, int len)
{
    int res = ERR_DIVISION_BY_ZERO;
    for (int i = 0; i < len; i++)
        if (num[i] != '0')
            res = OK;
    return res;
}