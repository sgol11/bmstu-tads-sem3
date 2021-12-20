#ifndef __IO__H__
#define __IO__H__

#include "general.h"
#include "memory.h"
#include "graph.h"

void print_matrix(int **matr, int size);
void print_path(int *arr, int len);
graph_t read_adjacency_matrix_from_file(char *filename, int *rc);
void graph_visualization(char *filename, graph_t *graph);
void print_line_to_dot(FILE *f, graph_t *graph, int elem_1, int elem_2);
int neighbours_in_arr(int *arr, int len, int elem_1, int elem_2);

#endif