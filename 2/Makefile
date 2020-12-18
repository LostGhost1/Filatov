all: tree
edit:
	nano tree.h tree.c main.c
tree: tree.o main.o
	gcc -o tree -g tree.o main.o
tree.o: tree.c
	gcc -c -g tree.c
main.o: main.c
	gcc -c -g main.c
clean:
	rm *.o tree
