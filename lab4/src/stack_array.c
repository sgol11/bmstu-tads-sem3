#include "stack_array.h"

int array_input_element(arr_stack_t *stack)
{
    int rc = OK;

    char cur_ch;
    printf("Введите строку: \n");

    while ((scanf("%c", &cur_ch)) == 1 && cur_ch != '\n')
    {
        rc = array_push(stack, cur_ch);

        if (rc == OK)
            printf("Элемент '%c' успешно добавлен\n", cur_ch);
        else if (rc == ERR_STACK_OVERFLOW)
            printf("Невозможно добавить элемент '%c': стек заполнен\n", cur_ch);
    }

    return rc;
}

int array_push(arr_stack_t *stack, char element)
{
    int rc = OK;

    if (stack->cur_size == MAX_STACK_SIZE)
        rc = ERR_STACK_OVERFLOW;
    else
    {
        stack->data[stack->cur_size] = element;
        stack->cur_size++;
    }

    return rc;
}

int array_delete_element(arr_stack_t *stack)
{
    int rc = OK;
    char cur_ch;

    rc = array_pop(stack, &cur_ch);

    if (rc == OK)
        printf("Элемент '%c' успешно удален\n", cur_ch);
    else if (rc == ERR_EMPTY_STACK)
        printf("Невозможно удалить элемент: стек пуст\n");

    return rc;
}

int array_pop(arr_stack_t *stack, char *element)
{
    int rc = OK;

    if (stack->cur_size == 0)
        rc = ERR_EMPTY_STACK;
    else
    {
        stack->cur_size--;

        *element = stack->data[stack->cur_size];
    }

    return rc;
}

void array_copy(arr_stack_t *dst, arr_stack_t *src)
{
    dst->cur_size = src->cur_size;
    for (int i = 0; i < src->cur_size; i++)
        dst->data[i] = src->data[i];
}

void array_print(arr_stack_t *stack)
{
    arr_stack_t stack_copy;
    array_copy(&stack_copy, stack);

    printf("Текущее состояние стека, реализованного в виде массива:\n\n");

    if (stack->cur_size == 0)
        printf("Стек пуст\n");

    else
    {
        char ch = '\0';
        printf("->\n");
        while(stack_copy.cur_size != 0)
        {
            array_pop(&stack_copy, &ch);
            printf("  %c\n", ch);
        }
        printf("\n");
    }
}

int array_is_palindrome(arr_stack_t *word)
{
    arr_stack_t stack_copy, second_half;
    array_copy(&stack_copy, word);

    int res = TRUE;
    int word_len = stack_copy.cur_size;
    second_half.cur_size = 0;

    while (second_half.cur_size != word_len / 2)
    {
        char cur_ch;
        array_pop(&stack_copy, &cur_ch);
        array_push(&second_half, cur_ch);
    }

    char middle_element;
    if (word_len % 2 != 0)
        array_pop(&stack_copy, &middle_element);

    while (stack_copy.cur_size && second_half.cur_size && res)
    {
        char first_half_ch, second_half_ch;

        array_pop(&stack_copy, &first_half_ch);
        array_pop(&second_half, &second_half_ch);
        
        if (first_half_ch != second_half_ch)
            res = FALSE;
    }
    
    return res;
}