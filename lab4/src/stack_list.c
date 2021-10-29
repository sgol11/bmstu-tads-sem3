#include "stack_list.h"

int list_input_element(list_stack_t **stack, free_areas_t *areas)
{
    int rc = OK;
    int first_node = (*stack == NULL ? 1 : 0);

    char cur_ch;
    printf("Введите строку: \n");
    while ((scanf("%c", &cur_ch)) == 1 && cur_ch != '\n')
    {
        rc = list_push(stack, cur_ch, first_node);
        first_node = 0;

        if (rc == OK)
        {
            printf("Элемент '%c' успешно добавлен\n", cur_ch);
            if (areas->len)
                areas->len--;
        }
        else if (rc == ERR_STACK_OVERFLOW)
            printf("Невозможно добавить элемент '%c': стек заполнен\n", cur_ch);
    }

    return rc;
}

int list_push(list_stack_t **head, char element, int first_node)
{
    int rc = OK;
    list_stack_t *node = NULL;

    if (*head && (*head)->index == MAX_STACK_SIZE - 1)
        rc = ERR_STACK_OVERFLOW;
    else
    {
        node = malloc(sizeof(list_stack_t));

        if (!node)
            rc = ERR_MEMORY;
        else
        {
            if (first_node)
            {
                node->index = 0;
                node->prev = NULL;
            }
            else
            {
                node->index = (*head)->index + 1;
                node->prev = *head;
            }
            node->value = element;
            *head = node;
        }
    }

    return rc;
}

int list_delete_element(list_stack_t **stack, free_areas_t *areas)
{
    int rc = OK;
    char cur_ch;
    size_t address;
    
    rc = list_pop(stack, &cur_ch, &address);
    if (rc == OK)
        printf("Элемент '%c' успешно удален\n", cur_ch);
    else if (rc == ERR_EMPTY_STACK)
        printf("Невозможно удалить элемент: стек пуст\n");

    if (areas->len == 0)
        create_areas(areas);
    
    areas->arr[areas->len] = address;
    areas->len++;

    return rc;
}

int list_pop(list_stack_t **head, char *element, size_t *address)
{
    int rc = OK;

    if ((*head) == NULL)
        rc = ERR_EMPTY_STACK;
    else
    {
        list_stack_t *old_head = *head;

        *element = old_head->value;
        *address = (size_t)old_head;
        *head = old_head->prev;
        old_head->prev = NULL;

        free(old_head);
    }

    return rc;
}

void list_print(list_stack_t *head, free_areas_t *areas)
{
    printf("Текущее состояние стека, реализованного в виде списка:\n\n");

    if (head == NULL)
        printf("Стек пуст\n\n");

    else
    {
        printf("->\n");
        while(head != NULL)
        {
            printf("  %c : %p\n", head->value, (void*)head);
            head = head->prev;
        } 
        printf("\n");
    }
    
    print_free_areas(areas);
}

int list_is_palindrome(list_stack_t **head, free_areas_t *areas)
{
    list_stack_t *second_half = NULL;
    size_t tmp_address;

    if (areas->arr == NULL)
        create_areas(areas);

    if ((*head) == NULL)
    {
        printf("Стек пуст\n");
        return OK;
    }

    int res = TRUE;
    int word_len = (*head)->index + 1;
    int first = 1;

    while (first || (*head)->index >= word_len / 2)
    {
        char cur_ch;
        list_pop(head, &cur_ch, &tmp_address);

        areas->arr[areas->len] = tmp_address;
        areas->len++;

        list_push(&second_half, cur_ch, first);
        first = 0;
    }

    char middle_element;
    if (word_len % 2 != 0)
    {
        list_pop(&second_half, &middle_element, &tmp_address);
        areas->arr[areas->len] = tmp_address;
        areas->len++;
    }

    while ((*head) && second_half && res)
    {
        char first_half_ch, second_half_ch;

        list_pop(head, &first_half_ch, &tmp_address);

        areas->arr[areas->len] = tmp_address;
        areas->len++;

        list_pop(&second_half, &second_half_ch, &tmp_address);
        
        if (first_half_ch != second_half_ch)
            res = FALSE;
    }
    
    free_list(&second_half);
    free_list(head);
    
    return res;
}

void create_areas(free_areas_t *areas)
{
    areas->len = 0;
    areas->arr = malloc(MAX_STACK_SIZE * sizeof(size_t));
}

void print_free_areas(free_areas_t *areas)
{
    printf("Массив освободившихся областей: \n\n");

    if (areas->len == 0)
        printf("Массив освободившихся областей пуст\n");
    else
        for (int i = 0; i < areas->len; i++)
            printf("%zx\n", areas->arr[i]);
}

void free_list(list_stack_t **head)
{
    list_stack_t *prev;

    while (*head)
    {
        prev = (*head)->prev;
        free(*head);
        (*head) = prev;
    }
}