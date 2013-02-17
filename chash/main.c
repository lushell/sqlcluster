#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "md5hash.h"
#include "rbtree.h"

typedef struct _entity_node{
	char ident[255];
	int	vnum;
	char data[255];
} entity_node;


util_rbtree_t *vnode_tree;

int vnodes = 0;
int addnode(entity_node *node)
{
	if(node == NULL) 
		return -1;

	int max_vnode = node->vnum;
	if(max_vnode <= 0) 
		return -1;

	util_rbtree_node_t *rbnode;

	char str [1023];
	memset(str, 0, 1024);
	strncpy(str, node->ident, strlen(node->ident));

	long hash = 0;
	int i;
	unsigned char num[7];
	for(i = 0; i < max_vnode; i++)
	{
		sprintf(num, "%d", i);
		strcat(str, num);
		hash = md5hash((void *)str);
		if(!util_rbtree_search(vnode_tree,hash))
		{
			rbnode->key = hash;
			rbnode->data = node->data;
			if(rbnode!=NULL)
			{
				util_rbtree_insert(vnode_tree,rbnode);
				vnodes++;
			}
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	util_rbtree_init(vnode_tree);
	
	entity_node node1;
	strcpy(node1.ident, argv[1]);
	strcpy(node1.data, argv[2]);
	node1.vnum = 4;
	addnode(&node1);
	return 0;
}
