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

entity_node * mylookup(void *object)
{
	if(object == NULL || vnodes == 0) 
		return NULL;

	util_rbtree_node_t * rbnode;
	rbnode = (util_rbtree_node_t *)malloc(sizeof(rbnode));
	memset(rbnode, 0, sizeof(rbnode));
	long int hash_key = md5hash(object);

	rbnode = util_rbtree_search(vnode_tree, hash_key);
	if(rbnode != NULL)
	{
		printf("%s\n", rbnode->data);
	}
	else
	{
		printf("[%s hash = %ld]rbnode is null!\n", (char *)object, hash_key);
	}
	free(rbnode);
	return NULL;
}

int addnode(entity_node *node);
int main(int argc, char *argv[])
{
	util_rbtree_init(vnode_tree);
    char baidu[] = "www.baidu.com";
	char baiduip[] = "192.168.1.1";	
	entity_node *node1, *node2, *node3, *node4; 
	entity_node node[1023];
	int i;
	for(i = 0; i < 1023 + 1; i++)
	{
		node[i].vnum = 0;	
	}
	
	strcpy(node[1].ident, baidu); 
	strcpy(node[2].ident, "www.360buy.com"); 
	strcpy(node[3].ident, "www.qq.com"); 
	strcpy(node[4].ident, "host.peking"); 
	strcpy(node[1].data, baiduip); 
	strcpy(node[2].data, "10.10.1.1"); 
	strcpy(node[3].data, "2.2.2.2"); 
	strcpy(node[4].data, "1.1.1.1"); 
	node[1].vnum = node[2].vnum = node[3].vnum = node[4].vnum= 8;
	for(i = 0; i < 1024; i++)
	{
		if(node[i].vnum > 0)
		{
			printf("i = %d, %s, %s, %d\n", i, node[i].ident, node[i].data, node[i].vnum);
			addnode(&node[i]);
		}
	}

#define _NULL(rbtree) (&((rbtree)->null))
	long key = md5hash((void *)"www.qq.com1");
    if(vnode_tree != NULL)
    {   
        util_rbtree_node_t *snode = vnode_tree->root;
        util_rbtree_node_t *null = _NULL(vnode_tree);
        while(snode != null)
        {   
            if(key < snode->key) 
				snode = snode->left;
            else if(key > snode->key) 
				snode = snode->right;
            else if(snode->key == key) 
				printf("%ld\n", snode->key);
				
        } 
    } 
	return 0;
}

int addnode(entity_node *node)
{
	if(node == NULL)
		return -1;

	int max_vnode = node->vnum;
	if(max_vnode <= 0) 
		return -1;

	util_rbtree_node_t *rbnode;
	rbnode = (util_rbtree_node_t *)malloc(sizeof(rbnode));
	memset(rbnode, 0, sizeof(rbnode));

	char str [1023];

	long int hash = 0;
	int i;
	unsigned char num[7];
	for(i = 0; i < max_vnode; i++)
	{
		memset(str, 0, 1023 + 1);
		strncpy(str, node->ident, strlen(node->ident));
		sprintf(num, "%d", i);
		strcat(str, num);
		hash = md5hash((void *)str);
		if(!util_rbtree_search(vnode_tree, hash))
		{
			rbnode->key = hash;
			rbnode->data = node->data;
			if(rbnode != NULL)
			{
				printf("add vnodes \t%ld\t(%s), %s into rbtree.\n", 
								rbnode->key, str, rbnode->data);
				util_rbtree_insert(vnode_tree, rbnode);
				vnodes++;
			}
		}
	}
	return 0;
}
<<<<<<< HEAD

entity_node * mylookup(void *object)
{
	if(object == NULL || vnodes == 0) 
		return NULL;

	util_rbtree_node_t * rbnode;
	long key = md5hash(object);
	printf("%ld\n", key);

	rbnode = util_rbtree_lookup(vnode_tree, key);
	if(rbnode != NULL)
	{
		printf("%s\n", (char *)rbnode->data);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	util_rbtree_init(vnode_tree);
	
	entity_node node1;
	strcpy(node1.ident, argv[1]);
	strcpy(node1.data, argv[2]);
	node1.vnum = 64;

	addnode(&node1);

	mylookup((void *) argv[1]);

	return 0;
}
=======
>>>>>>> 2f6f1454c0935cd8f923a799a983ec766c76f5bc