#include "queue.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
void *queue_new(){
	struct queue *q=malloc(sizeof(struct queue));
	q->length=0;
	q->aptr=NULL;
	q->last=NULL;
	return q;
}
void queue_add(struct queue *q, int value){
	if(q==NULL)return;
	if((q->aptr==NULL)&&(q->length!=0)){
		q->length=1;
		q->aptr=malloc(sizeof(int));
		q->aptr[0]=value;
		q->last=q->aptr+(q->length-1);
		return;
	}
	q->aptr=realloc(q->aptr,(q->length+1)*sizeof(int));
	memmove(q->aptr+1,q->aptr,(q->length)*sizeof(int));
	q->aptr[0]=value;
	q->length+=1;
	q->last=q->aptr+(q->length-1);
}
int queue_pop(struct queue *q){
	if(q==NULL)return 0;
	if(q->length==0)return 0;
	int result=*(q->last);
	q->aptr=realloc(q->aptr,(q->length-1)*sizeof(int));
	q->length-=1;
	q->last=q->aptr+(q->length-1);
	return result;
}
void queue_set(struct queue *q, unsigned int index, int value){
	if(q==NULL)return;
	if((q->aptr==NULL)||q->length==0)return;
	int *arrcpy=malloc(sizeof(int)*(q->length));
	memmove(arrcpy,q->aptr,(q->length)*sizeof(int));
	arrcpy[index]=value;
	free(q->aptr);
	q->aptr=NULL;
	for(int i=q->length-1;i>=0;i--){
		queue_add(q,arrcpy[i]);
	}
}
int queue_get(struct queue *q, unsigned int index){
	if((q->aptr==NULL)||q->length==0)return 0;
	unsigned int trueind=q->length-index;
	struct queue *tmp=queue_copy(q);
	for(int i=0;i<trueind-1;i++){
		queue_pop(tmp);
	}
	int result=queue_pop(tmp);
	queue_delete(tmp);
	return result;
}
struct queue *queue_copy(struct queue *q){
	if(q==NULL) return NULL;
	struct queue *copy=malloc(sizeof(struct queue));
	int *aptr=malloc(sizeof(int)*(q->length));
	memcpy(aptr,q->aptr,sizeof(int)*(q->length));
	copy->aptr=aptr;
	copy->length=q->length;
	copy->last=copy->aptr+(copy->length-1);
	return copy;
}
void queue_out(struct queue *q){
	if(q==NULL) return;
	struct queue *tmp=queue_copy(q);
	while(tmp->length>0){
		printf("%d ",queue_pop(tmp));
	}
}
int queue_sort(struct queue *q, int left, int right)
{
	if(q==NULL) return 0;
	long base, opposite, p;
	int c;
	base=left;
	opposite=right;
	while (base!=opposite){
		if ((queue_get(q,base)>queue_get(q,opposite))^(base>opposite)){
			c=queue_get(q,base);
			queue_set(q,base,queue_get(q,opposite));
			queue_set(q,opposite,c);
			p=base;
			base=opposite;
			if (p<opposite)
				opposite=p+1; else opposite=p-1;
		} else {
			if (base<opposite)
				opposite--; else opposite++;
		};
	};
	if (left<base-1) queue_sort(q,left,base-1);
	if (base+1<right) queue_sort(q,base+1,right);
};
void queue_delete(struct queue *q){
	if(q==NULL) return;
	q->length=0;
	free(q->aptr);
	free(q);
}
