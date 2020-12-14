#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define A 18446744073709551615
struct graph{
	unsigned long long **arr;
	char **marks;
	unsigned long long nnodes;
};
struct graph *graph_new(unsigned long nnodes);
void graph_generate_random(struct graph *g);
void graph_out(struct graph *g);
void graph_delete(struct graph *g);
void graph_find_loops(struct graph *g);
unsigned long long first(struct graph *g, unsigned long long v);
unsigned long long next(struct graph *g, unsigned long long v, unsigned long long j);
char *vertex(struct graph *g, unsigned long long v, unsigned long long j);
unsigned long long add_v(struct graph *g, char *mark);
void add_e(struct graph *g, unsigned long long from, unsigned long long to, unsigned long long weight);
void del_v(struct graph *g, unsigned long long v);
void del_e(struct graph *g, unsigned long long from, unsigned long long to);
void edit_v(struct graph *g, unsigned long long index, char *mark);
void edit_e(struct graph *g, unsigned long long from, unsigned long long to, unsigned long long weight);


#endif
