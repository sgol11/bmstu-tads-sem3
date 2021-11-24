#include "queue_list.h"

void list_init(list_queue_t *queue)
{
    queue->head = NULL;
    queue->tail = NULL;
}

int list_input_element(list_queue_t *queue, free_areas_t *areas)
{
    int rc = OK;

    printf("Введите число: \n");
    
    int elem;

    char tmp[100];
    char *tmp_p = gets(tmp);

    if (strlen(tmp) == 0)
        tmp_p = gets(tmp);

    if (tmp_p == NULL || (atoi(tmp) == 0 && tmp[0] != '0'))
        printf("\nОшибка ввода: введено не целое число\n");
    else
    {
        elem = atoi(tmp);

        rc = list_push(queue, elem);

        exclude_addresses(areas, (size_t)queue->tail);

        if (rc == ERR_OVERFLOW)
            printf("\nНевозможно добавить элемент: очередь заполнена\n");
        else if (rc == ERR_MEMORY)
            printf("\nНе удалось выделить память\n");
        else
            printf("\nЭлемент %d успешно добавлен в очередь\n", elem);
    }

    return rc;
}

int list_push(list_queue_t *queue, int element)
{
    int rc = OK;

    // if (queue->head && queue->tail && list_size(queue) == MAX_QUEUE_SIZE)
        // return ERR_OVERFLOW;

    node_t *node = malloc(sizeof(node_t));
    
    if (!node)
        rc = ERR_MEMORY;
    else
    {
        if (queue->head == NULL)
            queue->head = node;

        if (queue->tail)
            queue->tail->next = node;

        node->data = element;
        node->next = NULL;
        queue->tail = node;
    }

    return rc;
}

int list_delete_element(list_queue_t *queue, free_areas_t *areas)
{
    int rc = OK;

    if (queue->head == NULL)
    {
        rc = ERR_EMPTY_QUEUE;
        printf("\nНевозможно удалить элемент: очередь пуста\n\n");
    }
    else
    {
        size_t cur_area;

        int elem = list_pop(queue, &cur_area);
        areas->address[areas->size] = cur_area;
        areas->size++;

        printf("\nЭлемент %d успешно удален\n\n", elem);
    }

    return rc;
}

int list_pop(list_queue_t *queue, size_t *address)
{
    if (queue->head == NULL)
        return 0;
    
    int element = queue->head->data;
    
    node_t *old_head = queue->head;

    queue->head = old_head->next;

    *address = (size_t)old_head;

    free(old_head);

    return element;
}

void list_print(list_queue_t *queue, free_areas_t *areas)
{
    printf("\nТекущее состояние очереди (представление - список):\n");

    if (queue->head == NULL)
        printf("\nОчередь пуста\n\n");
    else
    {
        printf("\n");

        node_t *cur_node = queue->head;
        int first = 1;

        while(cur_node != NULL)
        {
            if (first && cur_node->next == NULL)
            {
                printf("head and tail -> %d : %p\n", cur_node->data, (void*)cur_node);
                first = 0;
            }
            else if (first)
            {
                printf("head -> %d : %p\n", cur_node->data, (void*)cur_node);
                first = 0;
            }
            else if (cur_node->next == NULL)
            {
                printf("tail -> %d : %p\n", cur_node->data, (void*)cur_node);
            }
            else
                printf("        %d : %p\n", cur_node->data, (void*)cur_node);
            cur_node = cur_node->next;
        } 
        printf("\n\n");
    }
    
    print_free_areas(areas);
}

void print_free_areas(free_areas_t *areas)
{
    printf("Массив освободившихся областей: \n\n");

    if (areas->size == 0)
        printf("Массив освободившихся областей пуст\n\n");
    else
    {
        for (int i = 0; i < areas->size; i++)
            printf("%zx\n", areas->address[i]);
        printf("\n");
    }
}

void exclude_addresses(free_areas_t *areas, size_t addr)
{
    for (int i = 0; i < areas->size; i++)
    {
        if ((size_t)areas->address[i] == addr)
        {
            for (int j = i; j < areas->size - 1; j++)
                areas->address[j] = areas->address[j + 1];
            areas->size--;
            i--;
        }
    }
}

void free_list(list_queue_t *queue)
{
    node_t *next_node;

    while (queue->head)
    {
        next_node = queue->head->next;
        free(queue->head);
        queue->head = next_node;
    }

    queue->head = NULL;
    queue->tail = NULL;
}

int list_size(list_queue_t *queue)
{
    int count = 0;
    node_t *next_node = queue->head;

    while (next_node)
    {
        count++;
        next_node = next_node->next;
    }

    return count;
}

void list_queue_simulation(void)
{
    list_queue_t queue;
    list_init(&queue);

    int element = 11;

    float input_low = 0.0, input_high = 6.0;
    float process_low = 0.0, process_high = 1.0;
    
    float model_time = 0;          // общее время моделирования
    float forced_downtime = 0;     // время простоя аппарата
    float avg_time_in_queue = 0;   // среднее время пребывания заявки в очереди

    int count_in = 0;              // количество вошедших в систему заявок
    int count_out = 0;             // количество вышедших из системы заявок
    int count_service_device = 0;  // количество срабатываний обслуживающего аппарата
    int count_return  = 0;         // количество возвращенных в очередь заявок

    int check_repeat = 0, sum_length = 0, iter = 0;

    float input_time = random_time(input_low, input_high);
    float process_time = random_time(process_low, process_high);

    printf("\n");

    while (count_out < MAX_QUEUE_SIZE)
    {
        int cur_size = list_size(&queue);

        if (count_out != 0 && count_out % 100 == 0 && check_repeat == 0)
        {
            printf("Обработано заявок: %d\n", count_out);
            printf("Текущая длина очереди: %d\n", cur_size);
            printf("Средняя длина очереди: %f\n\n", (float)sum_length / iter);

            check_repeat = 1;
        }
       
        // добавление заявки в очередь
        if (input_time < process_time)
        {
            list_push(&queue, element);

            count_in++;
            
            process_time -= input_time;
            model_time += input_time;
            input_time = random_time(input_low, input_high);
        }
        // извлечение заявки из очереди и ее обработка обслуживающим аппаратом
        else if (cur_size != 0)
        {
            size_t tmp;
            list_pop(&queue, &tmp);

            count_service_device++;

            float p_return = (float)rand() / (float)RAND_MAX;

            if (p_return < 0.8 + EPS)
            {
                list_push(&queue, element);

                count_in++;
                count_return++;
            }
            else
            {
                count_out++;
                check_repeat = 0;
            }

            input_time -= process_time;
            model_time += process_time;
            process_time = random_time(process_low, process_high);
        }
        // простой обслуживающего аппарата
        else
        {
            input_time -= process_time;
            forced_downtime += process_time;
            process_time = random_time(process_low, process_high);
        }

        sum_length += cur_size;
        iter++;
    }

    int cur_size = list_size(&queue);

    printf("Обработано заявок: %d\n", count_out);
    printf("Текущая длина очереди: %d\n", cur_size);
    printf("Средняя длина очереди: %f\n\n", (float)sum_length / iter);

    model_time += forced_downtime;

    avg_time_in_queue = (model_time - forced_downtime) / count_service_device * (float)sum_length / iter;

    int expected_model_time = fmax(((input_high - input_low) / 2 + input_low) * 1000, ((process_high - process_low) / 2 + process_low) * 5 * 1000);
    int expected_forced_downtime = ((input_high - input_low) / 2 + input_low) * 1000 - ((process_high - process_low) / 2 + process_low) * 5 * 1000;
    expected_forced_downtime = expected_forced_downtime < 0 ? 0 : expected_forced_downtime;
    float avg_time_in = ((input_high - input_low) / 2 + input_low);

    printf("\n===========================================================================\n\n");
    
    printf("Ожидаемое время моделирования: %d е.в.\n", expected_model_time);
    printf("Полученное время моделирования: %f е.в.\n\n", model_time);

    printf("Ожидаемое время простоя: %d е.в\n", expected_forced_downtime);
    printf("Полученное время простоя: %f е.в.\n\n", forced_downtime);

    printf("Количество вошедших заявок: %d, из них повторно возвращенных заявок: %d\n", count_in, count_return);
    printf("Количество срабатываний ОА: %d, из них успешно обработанных заявок: %d\n\n", count_service_device, count_out);

    printf("Время среднего пребывания заявки в очереди: %f е.в.\n\n", avg_time_in_queue);
    
    float error_input = 100 * fabs((count_in - count_return - model_time / avg_time_in) / (model_time / avg_time_in));
    float error_output = 100 * fabs((model_time - expected_model_time) / expected_model_time);
    
    printf("\nПроверка работы системы по входным и выходным данным:\n");
    printf("Погрешность по входу: %f%%\n", error_input);
    printf("Погрешность по выходу: %f%%\n\n", error_output);

    printf("===========================================================================\n\n");

    free_list(&queue);
}