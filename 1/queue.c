#include "queue.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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
void queue_set(struct queue *q, unsigned int index, int value, unsigned long long *return_n){//22+6n
	unsigned long long n=*return_n;
	if(q==NULL)return;
	if((q->aptr==NULL)||q->length==0)return;
	int *arrcpy=malloc(sizeof(int)*(q->length));//1+1+1+1+1
	n+=5;
	memmove(arrcpy,q->aptr,(q->length)*sizeof(int));//1+1+1+1+1+1+1
	n+=7;
	arrcpy[index]=value;//1+1
	n+=2;
	free(q->aptr);//1+1+1
	n+=3;
	q->aptr=NULL;//1+1
	n+=2;
	n+=3;
	for(int i=q->length-1;i>=0;i--){//3+sigma(1+1+(1+1+1+1))=3+6n
		n+=2;	
		queue_add(q,arrcpy[i],&n);//1+1+1+1+1+1
		n+=6;
	}
	*return_n=n;
}
int queue_get(struct queue *q, unsigned int index, unsigned long long *return_n){//86+25n
	unsigned long long n=*return_n;
	if((q->aptr==NULL)||q->length==0)return 0;
	unsigned int trueind=q->length-index;//1+1+1
	n+=3;
	struct queue *tmp=queue_copy(q,&n);//28
	n+=1;
	for(int i=0;i<trueind-1;i++){//1+sigma(2+1+(21+1))=1+25n
		n+=3;
		queue_pop(tmp,&n);//21+1
	}
	int result=queue_pop(tmp,&n);//21+1+1
	queue_delete(tmp,&n);//7+1
	*return_n=n;
	return result;//1
}
struct queue *queue_copy(struct queue *q, unsigned long long *return_n){//28
	unsigned long long n=*return_n;
	if(q==NULL) return NULL;
	struct queue *copy=malloc(sizeof(struct queue));//1+1+1
	n+=3;
	int *aptr=malloc(sizeof(int)*(q->length));//1+1+1+1+1
	n+=5;
	memcpy(aptr,q->aptr,sizeof(int)*(q->length));//1+1+1+1+1+1+1
	n+=7;
	copy->aptr=aptr;//1+1
	n+=2;
	copy->length=q->length;//1+1+1
	n+=3;
	copy->last=copy->aptr+(copy->length-1);//1+1+1+1+1+1
	n+=6;
	n+=1;
	*return_n=n;
	return copy;//1
}
//void queue_out(struct queue *q){
//	if(q==NULL) return;
//	struct queue *tmp=queue_copy(q);
//	while(tmp->length>0){
//		printf("%d ",queue_pop(tmp));
//	}
//}
int queue_sort(struct queue *q, int left, int right, unsigned long long *return_n)
{
	unsigned long long n=*return_n;
	if(q==NULL) return 0;
	long base, opposite, p;
	int c;
	base=left;//1
	n+=1;
	opposite=right;//1
	n+=1;
	while (base!=opposite){//sigma(1+429+87n)=430n+87n^2
		n+=1;
		if ((queue_get(q,base,&n)>queue_get(q,opposite,&n))^(base>opposite)){//86+25n+2+1+86+25n+2+1+1
			n+=3;
			c=queue_get(q,base,&n);//1+1+1+86+25n
			queue_set(q,base,queue_get(q,opposite,&n),&n);//25+6n+1+1+1+1+1+86+25n
			queue_set(q,opposite,c,&n);//25+6n+1+1+1
			p=base;//+1
			n+=1;
			base=opposite;//+1
			n+=1;
			n+=1;
			if (p<opposite)//+1
				{
					opposite=p+1;
					n+=2;
				} else 
				{
					opposite=p-1;//1+1
					n+=2;
				}
		} else {
			n+=1;
			if (base<opposite)
				opposite--; else opposite++;
			n+=1;
		};
	};
	n+=2;
	if (left<base-1) queue_sort(q,left,base-1,&n);
	n+=2;
	if (base+1<right) queue_sort(q,base+1,right,&n);
	*return_n=n;
};
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
