#include "memory.h"

int **allocate_matrix(int size)
{
    int **matrix = malloc(size * sizeof(int *));

    if (!matrix)
        return NULL;

    for (int i = 0; i < size; i++)
    {
        matrix[i] = malloc(size * sizeof(int));

        if (!matrix[i])
        {
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            matrix = NULL;
        }
    }

    return matrix;
}

void free_graph(graph_t *graph)
{
    for (int i = 0; i < graph->size; i++)
        free(graph->matrix[i]);

    free(graph->matrix);
    free(graph->longest_path);

    graph_init(graph);
}