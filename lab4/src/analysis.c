#include "analysis.h"

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

void analysis(void)
{
    arr_stack_t arr[MAX_STACK_SIZE];
    arr->cur_size = 0;
    list_stack_t *list = NULL;
    uint64_t start, end, time = 0;
    free_areas_t areas;
    areas.arr = NULL;

    int cnt = 5;
    
    printf("Массив: \n\n");

    start = tick();
    for (int i = 0; i < cnt; i++)
        array_push(arr, 'a');
    end = tick();
    
    time = end - start;
    printf("Время добавления %d элементов: %lld тактов\n", cnt, time);

    start = tick();
    array_is_palindrome(arr);
    end = tick();
    
    time = end - start;
    printf("Время проверки строки из %d символов на палиндром: %lld тактов\n", cnt, time);
    
    char ch;
    start = tick();
    for (int i = 0; i < cnt; i++)
        array_pop(arr, &ch);
    end = tick();
    
    time = end - start;
    printf("Время удаления %d элементов: %lld тактов\n\n", cnt, time);

    printf("Занимаемая %d элементами память: %lld байт\n\n", cnt, sizeof(arr_stack_t));

    printf("Список: \n\n");
    
    int first = 1;
    start = tick();
    for (int i = 0; i < cnt; i++)
    {
        list_push(&list, 'a', first);
        first = 0;
    }
    end = tick();
    
    time = end - start;
    printf("Время добавления %d элементов: %lld тактов\n", cnt, time);

    start = tick();
    list_is_palindrome(&list, &areas);
    end = tick();
    
    time = end - start;
    printf("Время проверки строки из %d символов на палиндром: %lld тактов\n", cnt, time);
    
    size_t addr;
    start = tick();
    for (int i = 0; i < cnt; i++)
        list_pop(&list, &ch, &addr);
    end = tick();
    
    time = end - start;
    printf("Время удаления %d элементов: %lld тактов\n\n", cnt, time);

    printf("Занимаемая %d элементами память: %lld байт\n\n", cnt, sizeof(list_stack_t) * cnt);
    
    free_list(&list);
}
