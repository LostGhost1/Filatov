#include "graph.h"
struct graph *graph_new(unsigned long nnodes){
	struct graph *t=malloc(sizeof(struct graph));
	t->nnodes=nnodes;
	t->arr=malloc(sizeof(char*)*nnodes);
	for(unsigned long long i=0;i<nnodes;i++){
		t->arr[i]=malloc(sizeof(char)*nnodes);

		for(unsigned long long j=0;j<nnodes;j++){
			t->arr[i][j]=0;
		}
	}
	return t;
}
void graph_generate_random(struct graph *g){
	time_t t;
	srand((unsigned) time(&t));
	for(unsigned long long i=0;i< (g->nnodes);i++)
		for(unsigned long long j=0;j< (g->nnodes);j++){
			g->arr[i][j]=(char)(rand()%2-1);

		}
	unsigned long long i=0;
	while((i< g->nnodes)&&(i< g->nnodes)){
		g->arr[i][i]=0;
		i+=1;
	}
}

static unsigned long long rec(struct graph *g, unsigned long long *path, unsigned long long npath){
	unsigned long long loops=0;
	if(npath>1)
	if(path[0]==path[npath-1]){
		for(unsigned long long i=0;i<npath;i++){
			printf("%llu ",path[i]);
		}
		printf("\n");
		free(path);
		return 1;
	}
	for(unsigned long long i=1;i<npath-1;i++){
		if(path[i]==path[npath-1])return 0;
	}
	for(unsigned long long i=0;i< g->nnodes;i++){
		if(!(g->arr[path[npath-1]][i]))continue;
		unsigned long long *path_copy=malloc(sizeof(unsigned long long)*(npath+1));
		memcpy(path_copy,path,sizeof(unsigned long long)*npath);
		path_copy[npath]=i;
		loops+=rec(g,path_copy,npath+1);
	}
	free(path);
	return loops;
}

void graph_find_loops(struct graph *g){
	printf("Loops:\n");
	unsigned long long totalloops=0;
	for(unsigned long long i=0;i< (g->nnodes);i++){
		{
			unsigned long long *path=malloc(sizeof(unsigned long long));
			path[0]=i;
			totalloops+=rec(g,path,1);
		}
	}
	printf("Total loops: %llu\n",totalloops);
}
void graph_out(struct graph *g){
	for(unsigned long long i=0;i< g->nnodes;i++){
		for(unsigned long long j=0;j< g->nnodes;j++)
			printf("%c",(g->arr[i][j])?'1':'0');
		printf("\n");
	}
	printf("---------------------------\n");
	for(unsigned long long i=0;i< g->nnodes;i++){
		char flag;
		flag=0;
		for(unsigned long long j=0;j< g->nnodes;j++){
			if(g->arr[i][j])
				if(flag)
					printf("   +--->%d\n",j);
				else{
					printf("%2d-T--->%d\n",i,j);
					flag=1;
				}
		}
	}

}
void graph_delete(struct graph *g){
	for(int i=0;i< g->nnodes;i++)
		free(g->arr[i]);
	free(g->arr);
	g->nnodes=0;
}
