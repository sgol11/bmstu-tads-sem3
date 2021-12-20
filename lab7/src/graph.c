#include "graph.h"
#include "io.h"

void graph_init(graph_t *graph)
{
    graph->size = 0;
    graph->matrix = NULL;
    graph->path_len = 0;
    graph->longest_path = NULL;
}

int longest_path(graph_t *graph)
{
    int rc = OK;

    if (no_paths(graph))
        return NO_PATHS;

    int *weights = malloc(graph->size * sizeof(int));
    int *visited = malloc(graph->size * sizeof(int));
    int *cur_path = malloc(graph->size * sizeof(int));

    int visit_cnt, cur_path_len;

    if (weights == NULL || visited == NULL || cur_path == NULL)
        rc = ERR_MEMORY;

    for (int i = 0; i < graph->size; i++)
    {
        visit_cnt = 0;
        cur_path_len = 0;

        if (!find(i, cur_path, cur_path_len))
        {
            for (int j = 0; j < graph->size; j++)
                weights[j] = 0;
            visited[visit_cnt++] = i;

            dfs(graph, i, visited, weights, &visit_cnt, cur_path, &cur_path_len);

            if (cur_path_len > graph->path_len)
            {
                graph->path_len = cur_path_len;
                for (int j = 0; j < graph->path_len; j++)
                    graph->longest_path[j] = cur_path[j];
            }
        }
        
        /*
        printf("%d: ", i);
        print_path(cur_path, cur_path_len);
        printf("\n");
        */
    }

    free(weights);
    free(visited);
    free(cur_path);

    return rc;
}

void dfs(graph_t *graph, int cur_q, int *visited, int *weights, int *visit_cnt, int *cur_path, int *cur_path_len)
{
    for (int i = 0; i < graph->size; i++)
    {
        if (graph->matrix[cur_q][i] && i != cur_q)
        {
            if (weights[cur_q] + 1 > weights[i])
            {
                weights[i] = weights[cur_q] + 1;

                if (!find(i, visited, *visit_cnt))
                {
                    visited[(*visit_cnt)++] = i;
                    dfs(graph, i, visited, weights, visit_cnt, cur_path, cur_path_len);
                }
            }
        }
    }

    if (*cur_path_len < *visit_cnt)
    {
        *cur_path_len = *visit_cnt;
        for (int i = 0; i < *cur_path_len; i++)
            cur_path[i] = visited[i];
    }

    (*visit_cnt)--;
}

int find(int element, int *sequence, int len)
{
    int res = 0;

    for (int i = 0; i < len && !res; i++)
    {
        if (sequence[i] == element)
            res = 1;
    }

    return res;
}

int no_paths(graph_t *graph)
{
    int res = 1;

    for (int i = 0; i < graph->size && res; i++)
    {
        for (int j = 0; j < graph->size && res; j++)
        {
            if (graph->matrix[i][j] == 1 && i != j)
                res = 0;
        }
    }

    return res;
}