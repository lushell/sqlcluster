#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"

#define N 11
void printRBNode(RBTreeNode *node);

int main() {
	//数据
	int a[N] = {1, 2, 4, 5, 7, 8, 11, 14, 15, 9, 3}, i;

	RBTreeNode *root;
	//树根
	root = NULL;
	//测试插入
	for (i = 0; i < N; i++) {
		if (!rbInsertNode(&root, a[i])) {
			break;
		}
	}
	rbInorderTraversal(&root, printRBNode);
	//测试查找,后继
	RBTreeNode *fn, *fin, *sn, *tn;
	fn = rbSearch(&root, 4);
	sn = rbSearch(&root, 2);
	fin = rbSuccessor(fn);
	tn = rbSuccessor(sn);
	printf("%d, %d, %d, %d\n", fn->data, fin->data, sn->data, tn->data);
	//前驱
	fn = rbPredecessor(fin);
	sn = rbPredecessor(tn);
	printf("%d, %d, %d, %d\n", fn->data, fin->data, sn->data, tn->data);

	//测试删除: 删除红色结点
	rbDeleteNode(&root, 14);
	rbInorderTraversal(&root, printRBNode);
	printf("\n");
	//测试删除: 删除黑色结点
	rbDeleteNode(&root, 15);
	rbInorderTraversal(&root, printRBNode);
	printf("\n");
	//测试删除: 删除根结点
	rbDeleteNode(&root, 5);
	rbInorderTraversal(&root, printRBNode);
}

void printRBNode(RBTreeNode *node) {
	if (node != NULL) {
		printf("data: %d, color: %s, parent: %d\n",
			node->data, (node->color == RED ? "RED" : "BLACK"), 
			(node->parent != NULL) ? node->parent->data : -1);
	}
}

