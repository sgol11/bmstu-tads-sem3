#include "general.h"
#include "menu.h"
#include "structs.h"
#include "binary_search_tree.h"
#include "avl_tree.h"
#include "hash_table.h"
#include "io.h"
#include "measurements.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    setlocale(LC_ALL, "");

    tree_node_t *bst = NULL;
    tree_node_t *avl = NULL;
    hash_table_t table;

    hash_table_init(&table, 0);

    int choice = 1;

    // show_info();

    FILE *f, *f_out;
    int words_num = 0, hash_t_size = 0, found = 0;
    char del_word[MAX_WORD_LEN];

    int bst_compare_num = 0, avl_compare_num = 0, hash_compare_num = 0, file_compare_num = 0;
    uint64_t start, bst_time, avl_time, hash_time, file_time;
    int bst_memory, avl_memory, hash_memory, file_memory;
    int restruct = 0;

    while (choice != EXIT)
    {
        choice = choose_action();

        switch (choice)
        {
        case READ_FROM_FILE:
            f = fopen(argv[1], "r");
            if (!f)
                printf("Не удалось открыть файл\n");
            else
            {
                words_num = fill_tree_from_file(f, &bst);
                rewind(f);
                fill_avl_tree_from_file(f, &avl);
                rewind(f);
                if (words_num == 0)
                    printf("Файл пуст.\n");
                else
                {
                    printf("Данные успешно прочитаны.\n");
                    printf("Введите размер хеш-таблицы: ");
                    scanf("%d", &hash_t_size);
                }
                hash_table_init(&table, hash_t_size);
                fill_hash_table_from_file(f, &table, restruct);
                fclose(f);
            }
            break;
        case BINARY_SEARCH_TREE:
            printf("\n");
            if (bst == NULL)
                printf("Дерево пусто\n\n");
            else
                print_tree(bst, 0, 0);
            printf("\n");
            break;
        case AVL_TREE:
            printf("\n");
            if (avl == NULL)
                printf("Дерево пусто\n\n");
            else
                print_tree(avl, 0, 0);
            printf("\n");
            break;
        case HASH_TABLE:
            print_table(&table, words_num);
            break;
        case DELETE_WORD:
            found = 0;
            bst_compare_num = 0;
            avl_compare_num = 0;
            file_compare_num = 0;
            if (bst)
            {
                f = fopen(argv[1], "r");
                f_out = fopen("out.txt", "w");

                input_word_to_delete(del_word);
                int max_compares = input_compares_num();
                if (max_compares < 1)
                    continue;

                start = get_time_ticks();
                bst = remove_bst_node(bst, del_word, &bst_compare_num, &found);
                bst_time = get_time_ticks() - start;
                bst_memory = words_num * sizeof(tree_node_t);

                start = get_time_ticks();
                if (strcmp(del_word, avl->data) == 0)
                    avl = remove_avl_node(avl, del_word, &avl_compare_num, &found);
                else
                    remove_avl_node(avl, del_word, &avl_compare_num, &found);
                avl_time = get_time_ticks() - start;
                avl_memory = words_num * sizeof(tree_node_t);

                start = get_time_ticks();
                remove_hash_table_value(&table, del_word, &hash_compare_num, restruct, &words_num);
                hash_time = get_time_ticks() - start;

                if (hash_compare_num > max_compares)
                {
                    printf("\nКоличество сравнений в хеш-таблице при удалении заданного слова превысило максимально допустимое.\n"
                           "Произведена реструктуризация. Новая хеш-таблица:\n\n");
                    restruct = 1;
                    free_table(&table);
                    hash_table_init(&table, words_num);
                    fill_hash_table_from_file(f, &table, restruct);
                    print_table(&table, words_num);
                }

                hash_memory = find_hash_table_size(&table);
                rewind(f);

                start = get_time_ticks();
                remove_file_value(f, f_out, del_word, &file_compare_num);
                file_time = get_time_ticks() - start;
                fseek(f, 0, SEEK_END);
                file_memory = ftell(f);

                if (!found)
                    printf("\nЗаданное слово не было найдено.\n\n");
                else
                {
                    printf("\nЗаданное слово было успешно удалено.\n");
                    printf("\nСравнительный анализ эффективности");
                    if (restruct == 1)
                        printf(" до реструктуризации хеш-таблицы");
                    printf(":\n\n");

                    print_time(bst_time, avl_time, hash_time, file_time);
                    print_memory(bst_memory, avl_memory, hash_memory, file_memory);
                    print_cmprs_num(bst_compare_num, avl_compare_num, hash_compare_num, file_compare_num);
                }

                fclose(f);
                fclose(f_out);
            }
            else if (!bst)
                printf("Данные не были загружены\n\n");
            break;
        }
    }

    printf("Выход\n");
    
    free_tree(&avl);
    free_tree(&bst);
    free_table(&table);

    return 0;
}