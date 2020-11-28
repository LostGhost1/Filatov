#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
#include "queue.c"
int main(int argc, char **argv)
{
	int n;
	sscanf(argv[1],"%d",&n);
	unsigned long long trash=0;
	unsigned long long result=0;
	srand(time(NULL));
	entries=0;
		result=0;
		trash=0;
		struct queue *q=queue_new(&trash);
		for(int i=0;i<n;i++)
			queue_add(q,rand()%1000,&trash);
		queue_out(q);
		queue_sort(q,0,q->length-1,&result);
		queue_out(q);
		queue_delete(q,&trash);
		printf("%llu %d\n",result,entries);

	return 0;
}
