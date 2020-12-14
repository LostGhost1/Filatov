#include "graph.h"
int main(){
	struct graph *g=graph_new(5);
	int l1[5]={0,0,0,7,0};
	int l2[5]={6,0,2,0,0};
	int l3[5]={3,0,0,0,1};
	int l4[5]={9,2,5,0,9};
	int l5[5]={1,0,0,0,0};
	for(int i=0;i<5;i++){
		g->arr[0][i]=l1[i];
	}
	for(int i=0;i<5;i++){
		g->arr[1][i]=l2[i];
	}
	for(int i=0;i<5;i++){
		g->arr[2][i]=l3[i];
	}
	for(int i=0;i<5;i++){
		g->arr[3][i]=l4[i];
	}
	for(int i=0;i<5;i++){
		g->arr[4][i]=l5[i];
	}
	//graph_generate_random(g);
	graph_out(g);
	graph_find_loops(g);
	graph_delete(g);

	g=NULL;
	return 0;
}

