#ifndef QUEUE_H
#define QUEUE_H
struct queue{
	unsigned int length;
	int *aptr;
	int *last;
};
void *queue_new();
void queue_add(struct queue *q, int value);
int queue_pop(struct queue *q);
struct queue *queue_copy(struct queue *q);
void queue_delete(struct queue *q);
void queue_set(struct queue *q, unsigned int index, int value);
int queue_sort(struct queue *q, int left, int right);
void queue_out(struct queue *q);
#endif // QUEUE_H
