#ifndef QUEUE_H
#define QUEUE_H
struct queue{
	unsigned int length;
	int *aptr;
	int *last;
};

void *queue_new(unsigned long long *return_n);
char queue_isempty(struct queue *q, unsigned long long *return_n);
void queue_add(struct queue *q, int value, unsigned long long *return_n);
int queue_pop(struct queue *q, unsigned long long *return_n);
struct queue *queue_copy(struct queue *q, unsigned long long *return_n);
void queue_delete(struct queue *q, unsigned long long *return_n);
void queue_set(struct queue *q, unsigned int index, int value, unsigned long long *return_n);
void queue_sort(struct queue *q, int left, int right, unsigned long long *return_n);
void queue_out(struct queue *q);
#endif // QUEUE_H
