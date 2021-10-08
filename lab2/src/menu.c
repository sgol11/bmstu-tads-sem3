#include "menu.h"

void show_info()
{
    printf("\n"
           "=========================================================================\n"
           "\n"
		   "Информация о программе:\n"
           "\n"
           "Программа работает с таблицей, содержащей данные о машинах из автосалона.\n"
           "О каждом автомобиле известны:\n"
		   "- марка\n"
           "- страна-производитель\n"
           "- цена\n"
           "- цвет\n"
           "- состояние:\n"
           "  ~ новый => гарантия\n"
           "  ~ не новый => год выпуска, пробег, количество ремонтов, количество \n"
           "собственников\n"
           "\n"
		   "=========================================================================\n"
           "\n");
}

void choose_action(int *choice)
{
    printf("\n"
		   "Выберите действие:\n"
           "\n"
           " 1 - Вывести список автомобилей\n"
           " 2 - Добавить информацию об автомобиле в конец таблицы\n"
           " 3 - Удалить данные из таблицы по полю\n"
           " 4 - Вывести отсортированную (по ценам) таблицу ключей при несортированной\n"
           "исходной таблице\n"
           " 5 - Вывести отсортированную (по ценам) таблицу\n"
           " 6 - Вывести отсортированную (по ценам) таблицу, используя отсортированный\n"
           "массив ключей\n"
           " 7 - Вывести результаты анализа эффективности сортировок для\n"
           "текущей таблицы\n"
           " 8 - Вывести результаты полного анализа эффективности сортировок для\n"
           "заданных по умолчанию таблиц с разным количеством записей\n"
           " 9 - Вывести цены не новых машин указанной марки с одним предыдущим\n"
           "собственником и отсутствием ремонта, в указанном диапазоне цен\n"
           "10 - Выбрать новую исходную таблицу\n"
           " 0 - Выйти из программы\n"
           "\n");
    
    printf("Ваш выбор: ");

    char tmp[MAX_STR_LEN];
    char *tmp_p = fgets(tmp, MAX_STR_LEN, stdin);

    while (tmp_p == NULL || (atoi(tmp) < 0 || atoi(tmp) > 10) || (atoi(tmp) == 0 && tmp[0] != '0'))
    {
        printf(" Ошибка ввода: необходимо ввести номер одного из предложенных вариантов\n\n");
        printf("Ваш выбор: ");
        tmp_p = fgets(tmp, MAX_STR_LEN, stdin);
    }
    printf("\n");

    *choice = atoi(tmp);
}