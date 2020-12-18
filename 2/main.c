#include "tree.h"
#include <string.h>
#include <stdio.h>
#include <stddef.h>
int main(){
	char A[1000];
	printf("-----------------Ввод дерева А-----------------\n");
	scanf("%s",A);
	struct tree *treeA = tree_new(strlen(A));
	for(int i=0;i<strlen(A);i++){
		tree_input(treeA,A[i]);
	}
	printf("-----------------Вывод дерева А в прямом порядке-----------------\n");
	Aout(treeA);
	printf("-----------------Обычный вывод дерева А-----------------\n");
	tree_output(treeA);
	char B[1000];
	printf("-----------------Ввод дерева B-----------------\n");
	scanf("%s",B);
	struct tree *treeB = tree_new(strlen(B));
	for(int i=0;i<strlen(B);i++){
		tree_input(treeB,B[i]);
	}
	printf("-----------------Вывод дерева B в симметричном порядке-----------------\n");
	Bout(treeB);
	printf("-----------------Обычный вывод дерева А-----------------\n");
	tree_output(treeB);
	struct tree *C=MergeAB(treeA,treeB);
	printf("-----------------C = A Uобр B-----------------\n");
	Aout(C);
	printf("-----------------Обычный вывод дерева C-----------------\n");
	tree_output(C);
	return 0;
}
