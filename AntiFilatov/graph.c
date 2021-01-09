#include "graph.h"

void graph_menu(){
	struct graph *g=NULL;
	while(1){
	int optionn=0;
	printf("Меню:\n");
	printf("%d. Вывести граф.\n",++optionn);
	printf("%d. Ввести граф.\n",++optionn);
	printf("%d. Найти циклы в графе.\n",++optionn);
	printf("%d. Произвести топологическую сортировку графа.\n",++optionn);
	printf("%d. Найти хроматическое число графа (неориентированного).\n",++optionn);
	printf("%d. Найти максимальный поток/минимальный разрез (одно и то же число).\n",++optionn);
	printf("%d. Найти кратчайшее расстояние от v0 до наиболее удаленной вершины.\n",++optionn);
	printf("%d. Найти число компонент связности.\n",++optionn);
	printf("%d. Выход.\n",++optionn);
	int option=0;
	scanf("%d",&option);
	if(option==1)graph_out(g);
	if(option==2){graph_delete(g);g=NULL;g=graph_input();}
	if(option==3)graph_find_loops(g);
	if(option==4)graph_top_sort(g);
	if(option==5)graph_find_chrome(g);
	if(option==6)graph_find_flow(g);
	if(option==7)graph_not_dejkstra(g);
	if(option==8)graph_component_number(g);
	if(option==9)return;
	}
}
char *visited=NULL;
char pathexists(struct graph *g, unsigned long long from, unsigned long long to){
	if(from==to)return 1;
	visited[from]=1;
	for(unsigned long long i=0;i<g->nnodes;i++){
		if(g->arr[from][i])if(!visited[i])
			if(pathexists(g,i,to)){	visited[from]=0;return 1;}
	}
	visited[from]=0;
	return 0;
}
char path_print(struct graph *g, unsigned long long from, unsigned long long to){
	if(from==to){printf("%llu ",to);return 1;}
	visited[from]=1;
	for(unsigned long long i=0;i<g->nnodes;i++){
		if(g->arr[from][i])if(!visited[i])
			if(path_print(g,i,to)){	visited[from]=0; printf("%llu ",from); return 1;}
	}
	visited[from]=0;
	return 0;
}

char check_components(struct graph *g, char *components, char ncomponent){
	for(unsigned long long i=0; i<ncomponent; i++){
		for(unsigned long long j=0;j<g->nnodes;j++){
			if(components[j]!=(i+1)){continue;}
			for(unsigned long long k=0; k<g->nnodes; k++){
				if(components[k]!=(i+1))continue;
				if(k==j)continue;
				//printf("Checking path between %llu and %llu\n",j,k);
				if(!pathexists(g,k,j))return 0;
			}
		}
	}
	return 1;
}
void components_increment(struct graph *g, char *components, char *ncomponent){
	char needtoincrement=1;
	for(unsigned long long i=0;((i<g->nnodes)&&(needtoincrement));i++){
		needtoincrement=0;
		components[i]+=1;
		if(components[i]>(*ncomponent)){
			components[i]=1;
			needtoincrement=1;
		}
	}
	if(needtoincrement){
		*ncomponent+=1;
		for(unsigned long long i=0;i<g->nnodes;i++)
			components[i]=1;
	}
	
}

void graph_component_number(struct graph *g){
	char *component = malloc(sizeof(char)*g->nnodes);
	char ncomponent=1;
	for(unsigned long long i=0;i< g->nnodes;i++){
		component[i]=1;
	}
	visited=calloc(1,g->nnodes);
	while(!check_components(g, component, ncomponent)){
		components_increment(g,component,&ncomponent);
	}
	printf("Кол-во компонент:\n%llu\n",ncomponent);
	printf("Принадлежность вершин к компонентам:\n");
	for(unsigned long long i=0; i< g->nnodes; i++){
		printf("%llu ",component[i]);
	}
		free(visited);
		visited=calloc(1,g->nnodes);
	printf("\nПути:\n");
	for(unsigned long long i=0;i<g->nnodes;i++){
		for(unsigned long long j=0;j<g->nnodes;j++){
			if(i==j)continue;
			printf("Путь от %llu до %llu\n",i,j);
			char result=path_print(g,i,j);
//			if(result)printf("Path exists\n");else printf("No path\n");
			printf("\n");
		}
	}
	free(visited);
	free(component);
}
void graph_not_dejkstra(struct graph *g){
	printf("Введите номер изначальной вершины\n");
	unsigned long long start=0;
	scanf("%llu",&start);
	unsigned long long maxflow=0;
	unsigned long long maxflown=0;
	unsigned long long t=0;
	visited=calloc(1,g->nnodes);
	for(unsigned long long i=0;i<g->nnodes;i++){
		t=flow_rec(g,start,i);
		if(t>maxflow){maxflow=t; maxflown=i;}
	}
	free(visited);
	printf("Максимальное расстояние %llu до вершины %llu\n",maxflow,maxflown);
}
char checkcolors(struct graph *g, char *colors){
	for(unsigned long long i=0;i<g->nnodes;i++){
		for(unsigned long long j=0;j<g->nnodes;j++){
			if(!(g->arr[i][j]))continue;
			if(colors[i]==colors[j])return 0;
		}	
	}
	return 1;
}
void colors_increment(struct graph *g, char *colors, unsigned long long *ncolors){
	char needtoincrement=1;
	for(unsigned long long i=0;((i<g->nnodes)&&(needtoincrement));i++){
		needtoincrement=0;
		colors[i]+=1;
		if(colors[i]>(*ncolors)){
			colors[i]=1;
			needtoincrement=1;
		}
	}
	if(needtoincrement){
		*ncolors+=1;
		for(unsigned long long i=0;i<g->nnodes;i++)
			colors[i]=1;
	}
	
}

unsigned long long flow_rec(struct graph *g, unsigned long long start, unsigned long long finish){
//	printf("start %llu finish %llu\n",start,finish);
	unsigned long long max=0;
	if(start==finish)return 0;
	visited[start]=1;
	for(unsigned long long i=0;i<g->nnodes;i++){
		if(g->arr[start][i])if(!visited[i])if(max<((g->arr[start][i])+flow_rec(g,i,finish))){max=((g->arr[start][i])+flow_rec(g,i,finish));}
	}
	visited[start]=0;
	return max;
}
void graph_find_flow(struct graph *g){
	unsigned long long start=0;
	unsigned long long finish=0;
	char flag=0;
	for(unsigned long long i=0;i<g->nnodes;i++){
		flag=0;
		for(unsigned long long j=0;j<g->nnodes;j++){
			if(g->arr[j][i]){flag=1;break;}
		}
		if(!flag){start=i;break;}
	}
	for(unsigned long long i=0;i<g->nnodes;i++){
		flag=0;
		for(unsigned long long j=0;j<g->nnodes;j++){
			if(g->arr[i][j]){flag=1;break;}
		}
		if(!flag){finish=i;break;}
	}
	visited=calloc(1,g->nnodes);
	unsigned long long maxflow=flow_rec(g,start,finish);
	free(visited);
	printf("\nОтвет: %llu\n",maxflow);
}
void graph_find_chrome(struct graph *g){
	char *colors=calloc(sizeof(char),g->nnodes);
	for(unsigned long long i=0;i<g->nnodes;i++)
		colors[i]=1;
	unsigned long long ncolors=1;
	while(!checkcolors(g,colors)){
		colors_increment(g,colors,&ncolors);
	}
	printf("Раскрашено %llu цветами\n",ncolors);
	printf("Цвета:\n");
	for(unsigned long long i=0;i<g->nnodes;i++)
		printf("%d ",colors[i]);
	printf("\n");
}
void graph_top_sort(struct graph *g){
	char flag=0;
	if(!g)return;
	printf("Отсортированные вершины:\n");
	char *marks=NULL;
	marks=calloc(sizeof(unsigned long long),g->nnodes);
	unsigned long long nmarks=0;
	unsigned long long oldnmarks=1;
	while(nmarks!=g->nnodes){
		oldnmarks=nmarks;
		for(unsigned long long i=0;i<g->nnodes;i++){
			flag=0;
			if(marks[i] ){continue;}
			for(unsigned long long j=0;j<g->nnodes;j++){
				if(g->arr[j][i])if(!marks[j]){flag=1;break;}
			}
			if(!flag){
				printf("%llu ",i);
				marks[i]=1;
				nmarks+=1;
				break;
			}
		}
		if(nmarks==oldnmarks)printf("В графе есть циклы, сортировка невозможна\n");
	}
	printf("\n");
	free(marks);
}
struct graph *graph_new(unsigned long nnodes){
	struct graph *t=calloc(sizeof(struct graph),1);
	t->nnodes=nnodes;
	t->arr=calloc(sizeof(unsigned long long*),nnodes);
	for(unsigned long long i=0;i<nnodes;i++){
		t->arr[i]=calloc(sizeof(unsigned long long),nnodes);
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
			g->arr[i][j]=(unsigned long long)(rand()%100);
			if(rand()%2-1)g->arr[i][j]=0;

		}
	unsigned long long i=0;
	while((i< g->nnodes)&&(i< g->nnodes)){
		g->arr[i][i]=0;
		i+=1;
	}
}
struct graph *graph_input(){
	unsigned long long n=0;
	printf("Введите кол-во вершин в графе\n");
	scanf("%llu",&n);
	struct graph *g=graph_new(n);
	printf("Введите способ ввода графа. 1 - по ребрам, 2 - матрица смежности:\n");
	int way=0;
	scanf("%d",&way);
	if(way==1){
		printf("Граф ориентированный? 1-да, 2-нет\n");
		int direct=0;
		scanf("%d",&direct);
		printf("Вводите ребра графа по одному на строку в формате трех чисел(от, до, вес) разделенных пробелом. По окончании ввода введите -1. Вершины нумеруются с 0\n");
		unsigned long long from=0,to=0,weight=0;
		char s[30];
		while(1){
			fgets(s,30,stdin);
			if(s[0]=='-')return g;
			sscanf(s,"%llu %llu %llu",&from,&to,&weight);
			g->arr[from][to]=weight;
			if(direct==2)g->arr[to][from]=weight;
		}
	}
	if(way==2){
		for(unsigned long long i=0;i<n;i++){
			for(unsigned long long j=0;j<n;j++){
				scanf("%llu",&(g->arr[i][j]));
				
			}
		}
		printf("\n");
		return g;
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
	if(!g){printf("Граф не задан.\n");return;}
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
	if(!g){printf("Граф не задан.\n");return;}
	for(unsigned long long i=0;i< g->nnodes;i++){
		for(unsigned long long j=0;j< g->nnodes;j++)
			printf("%3llu",g->arr[i][j]);
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
	if(!g)return;
	for(unsigned long long i=0;i< g->nnodes;i++)
		free(g->arr[i]);
	free(g->arr);
	g->nnodes=0;
}
