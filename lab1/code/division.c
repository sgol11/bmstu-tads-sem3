#include "division.h"

int division(real_number *dividend, real_number *divisor, real_number *quotient)
{
    int code = OK;

    initialization_real(quotient);

    char tmp_dividend[MAX_MANTISSA_SIZE + 3] = { '0' };
    char remainder[MAX_MANTISSA_SIZE + 3] = { '0' };
    
    for (int i = 0; i < dividend->mantissa_len; i++)
        tmp_dividend[i] = dividend->mantissa[i];

    int tmp_divid_len = 1;
    int compare, start = 0, shift = 0, zeros_after_dot = 0;
    int quot_len = 0, rem_len = 0;

    quotient->exponent = (dividend->exponent - divisor->exponent - 
    (dividend->mantissa_len - divisor->mantissa_len));

    if (dividend->sign != divisor->sign)
        quotient->sign = '-';
    
    for (int i = 1; i <= dividend->mantissa_len; i++)
    {
        compare = greater_or_equal(tmp_dividend, tmp_divid_len, 
        divisor->mantissa, divisor->mantissa_len);

        if (compare && !start)
        {
            small_division(tmp_dividend, tmp_divid_len, divisor->mantissa, 
            divisor->mantissa_len, quotient->mantissa, &quot_len, remainder, &rem_len);

            for (int j = 0; j < rem_len; j++)
                tmp_dividend[j] = remainder[j];
            tmp_divid_len = rem_len;

            start = 1;
        } 
        else if (compare && start)
        {
            small_division(tmp_dividend, tmp_divid_len, divisor->mantissa, 
            divisor->mantissa_len, quotient->mantissa, &quot_len, remainder, &rem_len);

            for (int j = 0; j < rem_len; j++)
                tmp_dividend[j] = remainder[j];
            tmp_divid_len = rem_len;
        }
        else
        {
            quotient->mantissa[quot_len++] = '0';
            for (int j = 0; j < tmp_divid_len; j++)
                remainder[j] = tmp_dividend[j];
            rem_len = tmp_divid_len;
        }
     
        if (i < dividend->mantissa_len)
            tmp_dividend[tmp_divid_len++] = dividend->mantissa[i];
  
        delete_init_zeros(tmp_dividend, &tmp_divid_len);
        delete_init_zeros(quotient->mantissa, &quot_len);
    }
    
    if (quotient->mantissa[0] != '0')
    {
        shift = quot_len;
        for (int i = quot_len + 1; i > 1; i--)
        {
            quotient->mantissa[i] = quotient->mantissa[i - 2];
        }
        quotient->mantissa[0] = '0';
        quot_len++;
    }
    quotient->mantissa[1] = '.';
    quot_len++;

    while(strcmp(remainder, "0") && quot_len < MAX_MANTISSA_SIZE + 3)
    {
        tmp_dividend[tmp_divid_len++] = '0';
            
        small_division(tmp_dividend, tmp_divid_len, divisor->mantissa, 
        divisor->mantissa_len, quotient->mantissa, &quot_len, remainder, &rem_len);

        if (quotient->mantissa[quot_len - 1] == '0' && 
        quotient->mantissa[2] == '0' && !zeros_after_dot)
        {
            quot_len--;
            shift--;
        }
        else
            zeros_after_dot = 1;

        for (int j = 0; j < rem_len; j++)
            tmp_dividend[j] = remainder[j];
        tmp_divid_len = rem_len;
    } 

    quotient->exponent += shift;

    quotient->mantissa_len = quot_len;

    if (quotient->exponent > 99999 || quotient->exponent < -99999)
        code = ERR_OVERFLOW_RES_EXP;

    return code;
}

void small_division(char *dividend, int len1, char *divisor, int len2, 
char *quotient, int *len3, char *remainder, int *len4)
{
    int k = 1;
    int incr_len2 = 0;
    
    char increased_divisor[MAX_MANTISSA_SIZE + 3] = { '0' };

    incr_len2 = multiplication(divisor, len2, k, increased_divisor);

    while (greater_or_equal(dividend, len1, increased_divisor, incr_len2))
    {
        k++;
        incr_len2 = multiplication(divisor, len2, k, increased_divisor);
    }

    incr_len2 = multiplication(divisor, len2, k - 1, increased_divisor);

    quotient[*len3] = (k - 1) + '0';
    *len3 = *len3 + 1;

    *len4 = difference(dividend, len1, increased_divisor, incr_len2, remainder);
}


int greater_or_equal(char *first_num, int first_len, char *second_num, int second_len)
{
    int res = 0, equal = 1;

    if (first_len > second_len)
        res = 1;
    else if (first_len < second_len)
        res = 0;
    else
    {
        int i = 0;
        while (i < first_len && equal)
        {
            if (first_num[i] > second_num[i])
            {
                res = 1;
                equal = 0;
            }
            else if ((first_num[i] + '0') < (second_num[i] + '0'))
            {
                res = 0;
                equal = 0;
            }
            i++;
        }
        if (equal)
            res = 1;
    }

    return res;
}

int multiplication(char *num, int len, int count, char *new_num)
{
    int idx = 0;
    int add = 0;

    for (int i = len - 1; i >= 0; i--)
    {
        new_num[idx++] = ((num[i] - '0') * count + add) % 10 + '0';
        add = ((num[i] - '0') * count + add) / 10;
    }
    if (add != 0)
        new_num[idx++] = add + '0';

    for (int i = 0; i < idx / 2; i++)
        swap(new_num, i, idx - i - 1);

    return idx;
}

void swap(char *num, int i1, int i2)
{
    char tmp = num[i1];
    num[i1] = num[i2];
    num[i2] = tmp;
}

int difference(char *num1, int len1, char *num2, int len2, char *res)
{
    int j = len2 - 1;
    int add = 10, idx = 0, k = 0;
    char dig = '0';

    for (int i = len1 - 1; i >= 0; i--)
    {
        if (j < 0)
            dig = '0';
        else
            dig = num2[j];

        if (num1[i] < dig)
        {
            k = add;
            add = 9;
        }
        else if (num1[i] == dig && add == 9)
        {
            k = add;
        }
        else if (add == 9)
        {
            k = -1;
            add = 10;
        }
        else
            k = 0;
        
        res[idx++] = (num1[i] - '0') + k - (dig - '0') + '0';
        j--;
    }

    for (int i = 0; i < idx / 2; i++)
        swap(res, i, idx - i - 1);

    delete_init_zeros(res, &idx);

    return idx;
}

void delete_init_zeros(char *num, int *len)
{
    while (num[0] == '0' && *len > 1)
    {
        for (int i = 0; i < *len; i++)
            num[i] = num[i + 1];
        *len = *len - 1;
    }
}
