#include "time_analysis.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

float random_time(float low, float high)
{
    float random_0_to_1 = (float)rand() / (float)RAND_MAX;

    return (high - low) * random_0_to_1 + low;
}

void analysis(void)
{
    array_queue_t arr_queue;
    array_init(&arr_queue);

    list_queue_t lst_queue;
    list_init(&lst_queue);

    uint64_t start, end, time = 0;

    int cnt = 0; 

    printf("Введите размер очереди для анализа эффективности работы программы\n"
           "на различных реализациях (массив и список): ");

    if (scanf("%d", &cnt) != 1 || cnt < 0 || cnt > MAX_QUEUE_SIZE)
        printf("\nВведено некорректное значение\n");
    else
    {
        printf("\nМассив: \n\n");

        start = tick();
        for (int i = 0; i < cnt; i++)
            array_push(&arr_queue, 11);
        end = tick();
    
        time = end - start;
        printf("Время добавления %d элементов: %lld тактов\n", cnt, time);
    
        start = tick();
        for (int i = 0; i < cnt; i++)
            array_pop(&arr_queue);
        end = tick();
    
        time = end - start;
        printf("Время удаления %d элементов: %lld тактов\n\n", cnt, time);

        printf("Занимаемая %d элементами память: %lld байт\n\n", cnt, sizeof(array_queue_t));

        printf("Список: \n\n");
    
        start = tick();
        for (int i = 0; i < cnt; i++)
            list_push(&lst_queue, 11);
        end = tick();
    
        time = end - start;
        printf("Время добавления %d элементов: %lld тактов\n", cnt, time);
    
        size_t addr;
        start = tick();
        for (int i = 0; i < cnt; i++)
            list_pop(&lst_queue, &addr);
        end = tick();
    
        time = end - start;
        printf("Время удаления %d элементов: %lld тактов\n\n", cnt, time);

        printf("Занимаемая %d элементами память: %lld байт\n\n", cnt, sizeof(list_queue_t) * cnt);
    
        free_list(&lst_queue);
    }
}