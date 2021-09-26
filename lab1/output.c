#include "output.h"
#include "normalized_form.h"

void rounding(real_number *num)
{
    int m_len = num->mantissa_len;
    if (m_len > MAX_MANTISSA_SIZE + 2)
        round_num(num->mantissa, &m_len);
    num->mantissa_len = m_len;
}

void round_num(char *num, int *len)
{
    int i = *len - 2;
    if ((num[*len - 1] - '0') >= 5)
    {
        if (num[i] != '9')
            num[i] = num[i] + 1;
        else
        {
            while (num[i] == '9' || num[i] == '.')
            {
                if (num[i] == '9')
                    num[i] = '0';
                i--;
            }
            num[i] = num[i] + 1;
        }
    }
    *len = *len - 1;
}

void print_result(real_number *res)
{
    if (res->sign == '-')
        printf("%c", res->sign);
    
    for (int i = 0; i < res->mantissa_len; i++)
        printf("%c", res->mantissa[i]);

    if (res->mantissa_len != 1 || res->mantissa[0] != '0')
    {
        printf("e");
        printf("%d", res->exponent);
    }
}