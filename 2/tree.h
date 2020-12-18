#ifndef TREE_H
#define TREE_H
//V37 , optimal binary tree, list of children, Urev, A-straight, B-reverse
#include <stdio.h>
#include <stdlib.h>
struct tree{
	unsigned long long maxcapacity;
	struct node *nodes;
	unsigned long long nnodes;
};
struct node{
	struct metanode *next;
	unsigned long long key;
	char value;
	unsigned long long layer;
	unsigned long long index;
};
struct metanode{
	struct metanode *next;
	struct node *node;
};
struct returninfo{
	struct node *where;
	unsigned long long layer;
};
struct tree* tree_new(unsigned long long maxcapacity);
void tree_output(struct tree *tree);
char traverse_and_add(struct tree *tree, char in);
struct returninfo *insert_node_rec(struct tree *tree,struct node *newnode, struct node *start, char in, unsigned long long layer);
void insert_node(struct tree *tree, char in);
void restructure_tree(struct tree *tree);
void tree_input(struct tree *tree, char in);
void preOrderOut(struct node *node) ;
void inOrderOut(struct node *node) ;
void postOrderMerge(struct tree *A, struct node *node); //B in reverse
void Aout(struct tree *tree);
void Bout(struct tree *tree);
struct tree *MergeAB(struct tree *A, struct tree *B);
#endif
