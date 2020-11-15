#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct graph{
	char **arr;
	unsigned long long nnodes;
};
struct graph *graph_new(unsigned long nnodes);
void graph_generate_random(struct graph *g);
void graph_out(struct graph *g);
void graph_delete(struct graph *g);
void graph_find_loops(struct graph *g);
#endif
