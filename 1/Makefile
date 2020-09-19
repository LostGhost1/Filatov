all: queue
queue: queue.o main.o
	gcc -o queue queue.o main.o
queue.o: queue.c
	gcc -c queue.c
main.o: main.c
	gcc -c main.c
clean:
	rm *.o queue
