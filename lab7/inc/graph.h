#ifndef __GRAPH__H__
#define __GRAPH__H__

#include "general.h"

typedef struct
{
    int size;
    int **matrix;
    int path_len;
    int *longest_path;
} graph_t;

void graph_init(graph_t *graph);
int longest_path(graph_t *graph);
void dfs(graph_t *graph, int cur_q, int *visited, int *M, int *q_count, int *cur_path, int *cur_path_len);
int find(int element, int *sequence, int len);
int no_paths(graph_t *graph);

#endif