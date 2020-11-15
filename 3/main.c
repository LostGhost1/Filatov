#include "graph.h"
int main(){
	struct graph *g=graph_new(7);

	graph_generate_random(g);

	graph_out(g);
	graph_find_loops(g);
	graph_delete(g);

	g=NULL;
	return 0;
}
