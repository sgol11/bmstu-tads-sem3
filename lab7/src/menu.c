#include "menu.h"

void show_info()
{
    printf("\n"
           "=============================================================================\n"
           "\n"
		   "Информация о программе:\n"
           "\n"
           "Программа предназначена для работы с деревом, реализованным с помощью матрицы смежности.\n"
           "Основная задача - нахождение самого длинного простого пути.\n"
           "\n"
		   "==============================================================================\n"
           "\n");
}

int choose_action(void)
{
    int choice;

    printf("\n"
		   "Выберите действие:\n"
           "\n"
           "1 - Прочитать матрицу смежности графа из файла\n"
           "2 - Напечатать матрицу смежности\n"
           "3 - Найти самый длинный простой путь в графе\n"
           "4 - Создать схему графа\n"
           "0 - Выйти из программы\n"
           "\n");
    
    printf("Ваш выбор: ");

    char tmp[100];
    char *tmp_p = gets(tmp);

    if (strlen(tmp) == 0)
        tmp_p = gets(tmp);

    while (tmp_p == NULL || (atoi(tmp) < 0 || atoi(tmp) > 4) || (atoi(tmp) == 0 && tmp[0] != '0'))
    {
        printf("\n Ошибка ввода: необходимо ввести номер одного из предложенных вариантов\n");
        printf(" Ваш выбор: ");
        tmp_p = gets(tmp);
    }
    printf("\n");

    choice = atoi(tmp);

    return choice;
}