#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
void timespec_diff(struct timespec *a, struct timespec *b, struct timespec *result) {
	result->tv_sec  = a->tv_sec  - b->tv_sec;
	result->tv_nsec = a->tv_nsec - b->tv_nsec;
		if (result->tv_nsec < 0) {
			--result->tv_sec;
			result->tv_nsec += 1000000000L;
		}
}

int main()
{
//	clock_gettime()
	srand(time(NULL));
	unsigned long long result=0;
	unsigned long long trash=0;
		struct timespec before,after,result_t;	
	for(int n=1;n<3002;n+=300){
		result=0;
		trash=0;
		struct queue *q=queue_new(&trash);
		for(int i=0;i<n;i++){
			queue_add(q,rand()%1000,&trash);
		}
		clock_gettime(CLOCK_REALTIME,&before);
		queue_sort(q,0,q->length-1,&result);
		clock_gettime(CLOCK_REALTIME,&after);
		queue_delete(q,&trash);
		timespec_diff(&after,&before,&result_t);
		printf("%d %llu ",n,result);
		printf("%lld.%.9ld\n", (long long)result_t.tv_sec, result_t.tv_nsec);
		fflush(stdout);
	}

	return 0;
}
