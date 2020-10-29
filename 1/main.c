#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
int main()
{
	srand(time(NULL));
	unsigned long long result=0;
	unsigned long long trash=0;
	
	for(int n=0;n<20;n++){
		result=0;
		trash=0;
		struct queue *q=queue_new(&trash);
		for(int i=0;i<n;i++){
			queue_add(q,rand()%1000,&trash);
		}
		queue_sort(q,0,q->length-1,&result);
		queue_delete(q,&trash);
		printf("%d %llu\n",n,result);
		fflush(stdout);
	}
	for(int n=21;n<100;n+=5){
		result=0;
		trash=0;
		struct queue *q=queue_new(&trash);
		for(int i=0;i<n;i++){
			queue_add(q,rand()%1000,&trash);
		}
		queue_sort(q,0,q->length-1,&result);
		queue_delete(q,&trash);
		printf("%d %llu\n",n,result);
		fflush(stdout);
	}
	for(int n=101;n<1000;n+=20){
		result=0;
		trash=0;
		struct queue *q=queue_new(&trash);
		for(int i=0;i<n;i++){
			queue_add(q,rand()%1000,&trash);
		}
		queue_sort(q,0,q->length-1,&result);
		queue_delete(q,&trash);
		printf("%d %llu\n",n,result);
		fflush(stdout);
	}
	for(int n=1001;n<10000;n+=200){
		result=0;
		trash=0;
		struct queue *q=queue_new(&trash);
		for(int i=0;i<n;i++){
			queue_add(q,rand()%1000,&trash);
		}
		queue_sort(q,0,q->length-1,&result);
		queue_delete(q,&trash);
		printf("%d %llu\n",n,result);
		fflush(stdout);
	}
	return 0;
}
