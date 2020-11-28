#include "queue.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int entries;
void *queue_new(unsigned long long *return_n){//10
	unsigned long long n=*return_n;
	struct queue *q=malloc(sizeof(struct queue));
	n+=3;
	q->length=0;
	n+=2;
	q->aptr=NULL;
	n+=2;
	q->last=NULL;
	n+=2;
	n+=1;
	*return_n=n;
	return q;
}
char queue_isempty(struct queue *q, unsigned long long *return_n){//3
	unsigned long long n=*return_n;
	n+=3;
	*return_n=n;
	return ((q->length)==0);//1+1+1
}
void queue_add(struct queue *q, int value, unsigned long long *return_n){//29
	unsigned long long n=*return_n;
	if(q==NULL)return;
	if((q->aptr==NULL)&&(q->length!=0)){//1+1+1+1+1
		n+=5;
		q->length=1;
		n+=2;
		q->aptr=malloc(sizeof(int));
		n+=3;
		q->aptr[0]=value;
		n+=3;
		q->last=q->aptr+(q->length-1);
		n+=6;
		*return_n=n;
		return;
	}else{
		q->aptr=realloc(q->aptr,(q->length+1)*sizeof(int));//1+1+1+1+1+1+1+1+1
		n+=9;
		memmove(q->aptr+1,q->aptr,(q->length)*sizeof(int));//1+1+1+1+1+1+1+1+1
		n+=9;
		q->aptr[0]=value;//1+1+1
		n+=3;
		q->length+=1;//1+1
		n+=2;
		q->last=q->aptr+(q->length-1);//1+1+1+1+1+1
		n+=6;
		*return_n=n;
	}
}
int queue_pop(struct queue *q, unsigned long long *return_n){//21
	unsigned long long n=*return_n;
	if(q==NULL)return 0;
	if(q->length==0)return 0;
	int result=*(q->last);//1+1+1
	n+=3;
	q->aptr=realloc(q->aptr,(q->length-1)*sizeof(int));//1+1+1+1+1+1+1+1+1
	n+=9;
	q->length-=1;//1+1
	n+=2;
	q->last=q->aptr+(q->length-1);//1+1+1+1+1+1
	n+=6;
	n+=1;
	*return_n=n;
	return result;//+1
}

void queue_set(struct queue *q, unsigned int index, int value, unsigned long long *return_n){
	unsigned long long n=*return_n;
	n+=1;
	for(int i=index;i<q->length-1;i++){
		n+=4;
		queue_add(q,queue_pop(q,&n),&n);
		n+=9;
	}
	queue_pop(q,&n);
	n+=4;
	queue_add(q,value,&n);
	n+=5;
	n+=1;
	for(int i=0;i<index;i++){
		n+=2;
		queue_add(q,queue_pop(q,&n),&n);
		n+=9;
	}
	*return_n=n;
}
int queue_get(struct queue *q, unsigned int index, unsigned long long *return_n){
	unsigned long long n=*return_n;
	n+=1;
	for(int i=index;i<q->length-1;i++){
		n+=4;
		queue_add(q,queue_pop(q,&n),&n);
		n+=9;
	}
	int result=queue_pop(q,&n);
	n+=4;
	queue_add(q,result,&n);
	n+=5;
	n+=1;
	for(int i=0;i<index;i++){
		n+=2;
		queue_add(q,queue_pop(q,&n),&n);
		n+=9;
	}

	n+=1;
	*return_n=n;
	return result;
}
void queue_out(struct queue *q){
	unsigned long long trash=0;
	if(q==NULL) return;
	for(int i=0;i<q->length;i++)
		printf("%d ",q->aptr[i]);
	printf("\n");
}

int partition (struct queue *q, int low, int high, unsigned long long *return_n) //0.67*n
{
	unsigned long long n=*return_n;
	int pivot = queue_get(q,high,&n);
	n+=5;
	int i = (low - 1);
	n+=1;
	n+=1;
	for (int j = low; j <= high- 1; j++)
	{
		n+=3;
		n+=6;
		if (queue_get(q,j,&n) <= pivot)
		{
			entries+=1;
			i++;
			n+=1;
			int t=queue_get(q,i,&n);
			n+=5;
			queue_set(q,i,queue_get(q,j,&n),&n);
			n+=11;
			queue_set(q,j,t,&n);
			n+=6;
		}
	}
	int t=queue_get(q,i+1,&n);
	n+=6;
	queue_set(q,i+1,queue_get(q,high,&n),&n);
	n+=11;
	queue_set(q,high,t,&n);
	n+=6;
	n+=2;
	*return_n=n;
	return (i + 1);
}

void queue_sort(struct queue *q, int low, int high, unsigned long long *return_n) //1.34*n
{

	unsigned long long n=*return_n;
	n+=1;
	if (low < high)
	{
		int pivot = partition(q, low, high,&n);
		n+=5;
		queue_sort(q, low, pivot - 1,&n);
		n+=5;
		queue_sort(q, pivot + 1, high,&n);
		n+=5;
	}
	*return_n=n;
}
void queue_delete(struct queue *q, unsigned long long *return_n){//7
	unsigned long long n=*return_n;
	if(q==NULL) return;
	q->length=0;//1+1
	n+=2;
	free(q->aptr);//1+1+1
	n+=3;
	free(q);//1+1
	n+=2;
	*return_n=n;
}
