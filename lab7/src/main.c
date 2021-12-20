#include "general.h"
#include "menu.h"
#include "io.h"
#include "graph.h"
#include "memory.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    setlocale(LC_ALL, "");

    int error_code = OK;

    graph_t graph;
    graph_init(&graph);

    show_info();

    int choice = 1;

    while (choice != EXIT)
    {
        choice = choose_action();

        switch (choice)
        {
        case READ_FROM_FILE:
            graph = read_adjacency_matrix_from_file(argv[1], &error_code);
            if (error_code != OK)
                printf("\nОшибка при чтении матрицы смежности из файла\n\n");
            else
                printf("\nМатрица смежности успешно прочитана\n\n");
            break;
        case PRINT_MATRIX:
            if (graph.size == 0)
                printf("\nГраф пуст. Выберите пункт 1, чтобы прочитать матрицу смежности графа из файла\n\n");
            else
            {
                printf("\nМатрица смежности:\n\n");
                print_matrix(graph.matrix, graph.size);
                printf("\n");
            }
            break;
        case FIND_PATH:
            error_code = longest_path(&graph);
            if (graph.size == 0)
                printf("\nГраф пуст. Выберите пункт 1, чтобы прочитать матрицу смежности графа из файла\n\n");
            else if (error_code == NO_PATHS)
                printf("\nВ графе нет простых путей\n\n");
            else if (error_code == OK)
            {
                printf("Самый длинный простой путь в графе: ");
                print_path(graph.longest_path, graph.path_len);
                printf("\n");
            }
            break;
        case VIS_GRAPH:
            if (graph.size == 0)
                printf("\nГраф пуст. Выберите пункт 1, чтобы прочитать матрицу смежности графа из файла\n\n");
            else
            {
                graph_visualization("graph.dot", &graph);
                printf("Файл graph.dot создан. Для получения графического файла введите в командной строке\n"
                "\"dot -Tpng graph.dot -o graph.png\"\n\n");
            }
            break;
        }
    }

    free_graph(&graph);

    printf("Выход\n");

    return 0;
}