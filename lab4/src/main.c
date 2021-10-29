#include "general.h"
#include "menu.h"
#include "structs.h"
#include "stack_array.h"
#include "stack_list.h"
#include "analysis.h"

int main(void)
{
    setbuf(stdout, NULL);
    setlocale(LC_ALL, "");

    arr_stack_t stack;
    stack.cur_size = 0;

    list_stack_t *head = NULL;
    free_areas_t areas;
    areas.arr = NULL;

    int choice = 1, res = 0;
    int mode = 1;

    show_info();

    while (choice != EXIT)
    {
        choice = choose_action();

        switch (choice)
        {
            case ADD_ELEMENT:
                if (mode == 1)
                    array_input_element(&stack);
                else
                    list_input_element(&head, &areas);
                break;
            case REMOVE_ELEMENT:
                if (mode == 1)
                    array_delete_element(&stack);
                else
                    list_delete_element(&head, &areas);
                break;
            case SHOW_STACK_STATE:
                if (mode == 1)
                    array_print(&stack);
                else
                    list_print(head, &areas);
                break;
            case CHECK_PALINDROME:
                if (mode == 1)
                    res = array_is_palindrome(&stack);
                else
                    res = list_is_palindrome(&head, &areas);
                printf("Строка %sявляется палиндромом\n", res ? "" : "не ");
                break;
            case CHOOSE_MODE:
                mode = choose_form();
                printf("Вы выбрали %s в качестве реализации стека\n", mode == 1 ? "массив" : "список");
                break;
            case ANALYSIS:
                analysis();
                break;
        }
    }

    free_list(&head);
    free(areas.arr);

    printf("Выход\n");

    return 0;
}