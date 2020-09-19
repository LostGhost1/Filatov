#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
int main()
{
	struct queue *q=queue_new();
	queue_add(q,3);
	queue_add(q,4);
	queue_add(q,5);
	queue_add(q,2);
	queue_add(q,8);
	queue_add(q,-2);
	queue_add(q,3);
	queue_add(q,7);
	queue_add(q,2);
	queue_add(q,1);
	queue_add(q,-6);
	queue_add(q,5);
	queue_out(q);
	printf("\n");
	queue_sort(q,0,q->length-1);
	queue_out(q);
	printf("\n");
	queue_set(q,1,3);
	queue_set(q,0,2);
	queue_set(q,3,9);
	queue_out(q);
	printf("\n");
	queue_sort(q,0,q->length-1);
	queue_out(q);
	printf("\n");
	queue_delete(q);
	return 0;
}
