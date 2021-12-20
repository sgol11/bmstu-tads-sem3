#include "io.h"

void print_matrix(int **matr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            printf("%d ", matr[i][j]);
        printf("\n");
    }
}

void print_path(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d ", arr[i] + 1);
        if (i < len - 1)
            printf("-> ");
    }
    printf("\n");
}

graph_t read_adjacency_matrix_from_file(char *filename, int *rc)
{
    graph_t graph;
    graph_init(&graph);

    FILE *file = fopen(filename, "r");

    if (!file)
        *rc = ERR_READ;

    if (fscanf(file, "%d", &graph.size) != 1)
        *rc = ERR_READ;

    graph.matrix = allocate_matrix(graph.size);
    graph.longest_path = malloc(graph.size * sizeof(int));

    if (graph.matrix == NULL || graph.longest_path == NULL)
        *rc = ERR_READ;

    for (int i = 0; i < graph.size && *rc == OK; i++)
    {
        if (feof(file))
            *rc = ERR_READ;

        for (int j = 0; j < graph.size && *rc == OK; j++)
        {
            if (fscanf(file, "%d", &graph.matrix[i][j]) != 1)
                *rc = ERR_READ;
        }
    }

    fclose(file);

    return graph;
}

void graph_visualization(char *filename, graph_t *graph)
{
    FILE *file = fopen(filename, "w");

    fprintf(file, "digraph { \n");

    for (int i = 0; i < graph->size; i++)
    {
        int no_connections = 1;
        for (int j = i; j < graph->size; j++)
        {
            if (graph->matrix[i][j] == 1 && graph->matrix[j][i] == 1)
            {
                fprintf(file, "\t%d -> %d ", i + 1, j + 1);
                if (neighbours_in_arr(graph->longest_path, graph->path_len, i, j))
                    fprintf(file, " [dir=both, color=red];\n");
                else
                    fprintf(file, " [dir=both, color=black];\n");
                no_connections = 0;
            }
            else if (graph->matrix[i][j] == 1 && graph->matrix[j][i] == 0)
            {
                print_line_to_dot(file, graph, i, j);
                no_connections = 0;
            }
            else if (graph->matrix[i][j] == 0 && graph->matrix[j][i] == 1)
            {
                print_line_to_dot(file, graph, j, i);
                no_connections = 0;
            }
        }
        if (no_connections)
            fprintf(file, "\t%d;\n", i + 1);
    }

    fprintf(file, "}\n");

    char command[100] = "dot -Tpng ";
    strcat(command, filename);
    strcat(command, " -o graph_pic.png");

    // system("dot -Tpng graph.dot -o graph.png");
    // system("graph.png");

    fclose(file);
}

void print_line_to_dot(FILE *f, graph_t *graph, int elem_1, int elem_2)
{
    fprintf(f, "\t%d -> %d ", elem_1 + 1, elem_2 + 1);
    if (neighbours_in_arr(graph->longest_path, graph->path_len, elem_1, elem_2))
        fprintf(f, " [color=red];\n");
    else
        fprintf(f, " [color=black];\n");
}

int neighbours_in_arr(int *arr, int len, int elem_1, int elem_2)
{
    int res = 0;

    for (int i = 0; i < len - 1 && !res; i++)
    {
        if (arr[i] == elem_1 && arr[i + 1] == elem_2)
            res = 1;
        else if (arr[i] == elem_2 && arr[i + 1] == elem_1)
            res = 1;
    }

    return res;
}