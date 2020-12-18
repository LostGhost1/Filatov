#include "tree.h"
void Aout(struct tree *tree){
	preOrderOut(&(tree->nodes[0]));
	printf("\n");
}
void Bout(struct tree *tree){
	inOrderOut(&(tree->nodes[0]));
	printf("\n");
}
struct tree *MergeAB(struct tree *A, struct tree *B){
	struct tree *C = tree_new(A->nnodes+B->nnodes);
	postOrderMerge(C,&(A->nodes[0]));
	postOrderMerge(C,&(B->nodes[0]));
	return C;
}
void preOrderOut(struct node *node) {
	printf("%c(%llu) ", node->value, node->key);
	if(node->next)
		preOrderOut(node->next->node);
		if(node->next)
		if(node->next->next)
			preOrderOut(node->next->next->node);
	
}
void inOrderOut(struct node *node) {
	if(node->next)
		inOrderOut(node->next->node);
		printf("%c(%llu) ", node->value, node->key);
		if(node->next)
		if(node->next->next)
			inOrderOut(node->next->next->node);
	
}
void postOrderMerge(struct tree *A, struct node *node) { //B in reverse
	if(node->next)
		postOrderMerge(A,node->next->node);
		if(node->next)
		if(node->next->next)
			postOrderMerge(A,node->next->next->node);
			for(unsigned long long i=0; i< node->key; i++)
				tree_input(A,node->value);
		
	
}
struct tree* tree_new(unsigned long long maxcapacity){
	struct tree *tree=calloc(sizeof(struct tree),1);
	tree->maxcapacity=maxcapacity;
	return tree;
}
void tree_output(struct tree *tree){
//	for(unsigned long long i=0;i<tree ->nnodes;i++){
//		printf("%p\n",&(tree->nodes[i]));
//	}
	for(unsigned long long i=0;i<tree ->nnodes;i++){
		printf("%c ->%c %c\n",tree->nodes[i].value,(tree->nodes[i].next)?(tree->nodes[i].next->node->value):'_', (tree->nodes[i].next)?((tree->nodes[i].next->next)?(tree->nodes[i].next->next->node->value):'_'):'_');
	}
	for(unsigned long long i=0;i<tree ->nnodes;i++){
		printf("%llu ->%llu %llu\n",tree->nodes[i].key,(tree->nodes[i].next)?(tree->nodes[i].next->node->key):0, (tree->nodes[i].next)?((tree->nodes[i].next->next)?(tree->nodes[i].next->next->node->key):0):0);
	}
}
char traverse_and_add(struct tree *tree, char in){
	for(unsigned long long i=0;i< tree->nnodes; i++){
		if(tree->nodes[i].value==in){tree->nodes[i].key+=1; return 1;}
	}
	return 0;
}
struct returninfo *insert_node_rec(struct tree *tree,struct node *newnode, struct node *start, char in, unsigned long long layer){
	struct returninfo *info=calloc(sizeof(struct returninfo),1);
	if(start==NULL)return NULL;
	if(!start->key){
		return NULL;
	}
	if(!start->next){
		info->where=start;
		info->layer=layer+1;
		return info;
	}
	if(!start->next->next){
		info->where=start;
		info->layer=layer+1;
		return info;
	}
	struct returninfo *info1=insert_node_rec(tree,newnode,start->next->node,in,layer+1);
	struct returninfo *info2=insert_node_rec(tree,newnode,start->next->next->node,in,layer+1);
	if(info1->layer< info2->layer){
		info->where=info1->where;
		info->layer=info1->layer;
	}else{
		info->where=info2->where;
		info->layer=info2->layer;
	}
	free(info1);
	free(info2);
	return info;
}
void insert_node(struct tree *tree, char in){
	tree->nnodes+=1;
	tree->nodes[tree->nnodes-1].next=NULL;
	tree->nodes[tree->nnodes-1].key=1;
	tree->nodes[tree->nnodes-1].value=in;
	tree->nodes[tree->nnodes-1].index=tree->nnodes-1;
	struct returninfo *info=insert_node_rec(tree,&(tree->nodes[tree->nnodes-1]),&(tree->nodes[0]),in,0);
//	printf("Inserting %c, inserting into %llu, at %p at %llu layer\n",in,info->where->index,info->where,info->layer);
	if(!info->where->next){
		info->where->next=calloc(sizeof(struct metanode),1);
		info->where->next->node=&(tree->nodes[tree->nnodes-1]);
		tree->nodes[tree->nnodes-1].layer=info->layer;
	}else
	if(!info->where->next->next){
		info->where->next->next=calloc(sizeof(struct metanode),1);
		info->where->next->next->node=&(tree->nodes[tree->nnodes-1]);
		tree->nodes[tree->nnodes-1].layer=info->layer;
	}else{
		printf("FAIL\n");
		return;
	}
	free(info);
}
void swap(struct node *node1, struct node *node2){
		char t=0;
		unsigned long long tt=0;
		t=node1->value;
		node1->value=node2->value;
		node2->value=t;
		tt=node1->key;
		node1->key=node2->key;
		node2->key=tt;
		tt=node1->index;
		node1->index=node2->index;
		node2->index=tt;
}
char recursive_check(struct tree *tree, struct node *tocheck, struct node *parent){
	if(!tocheck)return 0;
	if(tocheck->key>parent->key){
		swap(tocheck,parent);
		return 1;
	}
	char result=0;
	if(tocheck->next){
		result=(result || recursive_check(tree,tocheck->next->node,tocheck));
		if(tocheck->next->next)
			result=(result || recursive_check(tree,tocheck->next->next->node,tocheck));
	}
	return result;
}
char checktree(struct tree *tree){
	if(tree->nodes[0].next){
		if(recursive_check(tree,tree->nodes[0].next->node,&(tree->nodes[0])))return 1;
		if(tree->nodes[0].next->next)
			if(recursive_check(tree,tree->nodes[0].next->next->node,&(tree->nodes[0])))return 1;
	}
	for(unsigned long long i=0;i< tree->nnodes; i++){
		for(unsigned long long j=0;j< tree->nnodes; j++){
			if(i==j)continue;
			if(tree->nodes[i].layer< tree->nodes[j].layer)
				if(tree->nodes[i].key < tree->nodes[j].key){
					swap(&(tree->nodes[i]),&(tree->nodes[j]));
					return 1;
				}
		}
	}
	return 0;
}
void restructure_tree(struct tree *tree){
	while(checktree(tree)){}
}
void tree_input(struct tree *tree, char in){
	if(!(tree->nodes)){
		tree->nodes=calloc(sizeof(struct node),tree->maxcapacity);
		tree->nnodes=1;
		tree->nodes[0].key+=1;
		tree->nodes[0].value=in;
//		tree_output(tree);
		return;
	}
	if(traverse_and_add(tree,in)){
	//tree_output(tree);
		restructure_tree(tree);
		//tree_output(tree);
		return;
	}
//	tree_output(tree);
	insert_node(tree,in);
//	tree_output(tree);
}
