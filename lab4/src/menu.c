#include "menu.h"

void show_info()
{
    printf("\n"
           "=============================================================================\n"
           "\n"
		   "Информация о программе:\n"
           "\n"
           "Программа предназначена для работы со стеком, представленным в виде массива\n"
           "или односвязного линейного списка.\n"
           "Программа способна осуществлять добавление, удаление элементов и вывод\n"
           "текущего состояния стека, а также определять, является ли введенная строка\n"
           "палиндромом.\n"
           "Признаком окончания ввода строки считается символ переноса строки.\n"
           "Максимальный размер стека - 100 символов.\n"
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
           "1 - Добавить элементы в стек\n"
           "2 - Удалить элемент из стека\n"
           "3 - Вывести текущее состояние стека\n"
           "4 - Определить, является ли строка палиндромом\n"
           "5 - Выбрать реализацию стека (по умолчанию - массив)\n"
           "6 - Сравнение работы программы на разных реализациях стека\n"
           "0 - Выйти из программы\n"
           "\n");
    
    printf("Ваш выбор: ");

    char tmp[100];
    char *tmp_p = gets(tmp);

    if (strlen(tmp) == 0)
        tmp_p = gets(tmp);

    while (tmp_p == NULL || (atoi(tmp) < 0 || atoi(tmp) > 6) || (atoi(tmp) == 0 && tmp[0] != '0'))
    {
        printf("\n Ошибка ввода: необходимо ввести номер одного из предложенных вариантов\n");
        printf(" Ваш выбор: ");
        tmp_p = gets(tmp);
    }
    printf("\n");

    choice = atoi(tmp);

    return choice;
}

int choose_form(void)
{
    int choice;
    
    printf("\nРеализация стека:\n\n");

    printf("1 - Массив\n"
           "2 - Список\n\n");
    
    printf("Ваш выбор: ");

    char tmp[100];
    char *tmp_p = fgets(tmp, 100, stdin);

    while (tmp_p == NULL || (atoi(tmp) < 1 || atoi(tmp) > 2))
    {
        printf("\n Ошибка ввода: необходимо ввести номер одного из предложенных вариантов\n");
        printf(" Ваш выбор: ");
        tmp_p = fgets(tmp, 100, stdin);
    }
    printf("\n");

    choice = atoi(tmp);

    return choice;
}