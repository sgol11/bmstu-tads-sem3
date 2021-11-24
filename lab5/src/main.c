#include "general.h"
#include "menu.h"
#include "structs.h"
#include "queue_array.h"
#include "queue_list.h"

int main(void)
{
    setbuf(stdout, NULL);
    setlocale(LC_ALL, "");

    array_queue_t arr_queue;
    array_init(&arr_queue);

    list_queue_t lst_queue;
    list_init(&lst_queue);

    free_areas_t areas;
    areas.size = 0;

    int choice = 1, mode = 1;

    show_info();

    while (choice != EXIT)
    {
        choice = choose_action();

        switch (choice)
        {
            case CHOOSE_MODE:
                mode = choose_form();
                break;
            case ADD_ELEMENT:
                if (mode == 1)
                    array_input_element(&arr_queue);
                else
                    list_input_element(&lst_queue, &areas);
                break;
            case REMOVE_ELEMENT:
                if (mode == 1)
                    array_delete_element(&arr_queue);
                else
                    list_delete_element(&lst_queue, &areas);
                break;
            case SHOW_QUEUE_STATE:
                if (mode == 1)
                    array_print(&arr_queue);
                else
                    list_print(&lst_queue, &areas);
                break;
            case SIMULATION:
                if (mode == 1)
                    array_queue_simulation();
                else
                    list_queue_simulation();
                break;
            case ANALYSIS:
                analysis();
                break;
        }
    }

    free_list(&lst_queue);

    printf("Выход\n");

    return 0;
}