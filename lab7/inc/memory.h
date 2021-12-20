#ifndef __MEMORY__H__
#define __MEMORY__H__

#include "general.h"
#include "graph.h"
#include "io.h"

int **allocate_matrix(int size);
void free_graph(graph_t *graph);

#endif