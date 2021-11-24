#include "queue_array.h"

void array_init(array_queue_t *queue)
{
    queue->head_idx = -1;
    queue->tail_idx = -1;
}

int array_input_element(array_queue_t *queue)
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

        rc = array_push(queue, elem);

        if (rc == ERR_OVERFLOW)
            printf("\nНевозможно добавить элемент: очередь заполнена\n");
        else
            printf("\nЭлемент %d успешно добавлен в очередь\n", elem);
    }

    return rc;
}

int array_push(array_queue_t *queue, int element)
{
    if (queue->head_idx == (queue->tail_idx + 1) % MAX_QUEUE_SIZE)
        return ERR_OVERFLOW;

    if (queue->head_idx == -1)
        queue->head_idx = 0;

    queue->tail_idx = (queue->tail_idx + 1) % MAX_QUEUE_SIZE;
    queue->data[queue->tail_idx] = element;

    return OK;
}

int array_delete_element(array_queue_t *queue)
{
    int rc = OK;

    if (queue->head_idx == -1)
    {
        rc = ERR_EMPTY_QUEUE;
        printf("\nНевозможно удалить элемент: очередь пуста\n\n");
    }
    else
    {
        int elem = array_pop(queue);
        printf("\nЭлемент %d успешно удален\n\n", elem);
    }

    return rc;
}

int array_pop(array_queue_t *queue)
{
    if (queue->head_idx == -1)
        return 0;

    int element = queue->data[queue->head_idx];

    if (queue->head_idx == queue->tail_idx)
    {
        queue->head_idx = -1;
        queue->tail_idx = -1;
    }
    else
        queue->head_idx = (queue->head_idx + 1) % MAX_QUEUE_SIZE;

    return element;
}

void array_print(array_queue_t *queue)
{
    printf("\nТекущее состояние очереди (представление - массив):\n");

    if (queue->head_idx == -1)
        printf("\nОчередь пуста\n\n");
    else
    {
        printf("\n");
        if (queue->head_idx > queue->tail_idx)
        {
            for(int i = queue->head_idx; i < MAX_QUEUE_SIZE; i++)
                printf("%d ",queue->data[i]);
            for(int i = 0; i <= queue->tail_idx; i++)
                printf("%d ",queue->data[i]);
        }
        else
        {
            for(int i = queue->head_idx; i <= queue->tail_idx; i++)
                printf("%d ",queue->data[i]);
        }
        printf("\n\n");
    }
}

int array_size(array_queue_t *queue)
{
    int size = 0;

    if (queue->head_idx != -1)
    {
        if (queue->head_idx > queue->tail_idx)
            size = (MAX_QUEUE_SIZE - queue->head_idx) + queue->tail_idx + 1;
        else
            size = queue->tail_idx - queue->head_idx + 1;
    }

    return size;
}

void array_queue_simulation(void)
{
    array_queue_t queue;
    array_init(&queue);

    int element = 11;

    float input_low = 1.0, input_high = 6.0;
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

    int rc = OK;

    while (count_out < MAX_QUEUE_SIZE && rc == OK)
    {
        int cur_size = array_size(&queue);

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
            rc = array_push(&queue, element);
            if (rc == ERR_OVERFLOW)
                printf("Очередь заполнена, моделирование остановлено\n\n");

            count_in++;
            
            process_time -= input_time;
            model_time += input_time;
            input_time = random_time(input_low, input_high);
        }
        // извлечение заявки из очереди и ее обработка обслуживающим аппаратом
        else if (cur_size != 0)
        {
            array_pop(&queue);

            count_service_device++;

            float p_return = (float)rand() / (float)RAND_MAX;

            if (p_return < 0.8 + EPS)
            {
                array_push(&queue, element);

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

    int cur_size = array_size(&queue);

    printf("Обработано заявок: %d\n", count_out);
    printf("Текущая длина очереди: %d\n", cur_size);

    if (rc == OK)
    {
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
    }
}