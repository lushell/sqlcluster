#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"

/* Generation vnode from mac_node */
int add_vnode(pnode *vnode, rb_node_t* root)
{
	unsigned char id[1024];
	unsigned char tmp[0xffff];
	unsigned int i, key;
    for (i = 0; i < vnum_max; i++)
    {
		sprintf(id, "%d", vnode->id);
		sprintf(tmp, "%d", i);
		strcat(id, tmp); 
		
        key = md5hash(id);
		printf("ipv4 = %s\n", vnode->ipv4);
        if((root = rb_insert(key, vnode->ipv4, root)))
#ifdef debug
        {
            printf("insert key[%ld], rbnode key[%ld] = value[%s] success!\n", 
					key, root->key,  root->data);
			return -1;
        }
        else
#endif
        {
            printf("insert key[%ld] , error!\n", key, vnode->ipv4);
        }
	}
	return 0;
}

/* update vnode */
int update_vnode(unsigned int key, char *data, rb_node_t* root)
{
	int ret;
	if(ret = rb_update(key, root, data))
	{
		printf("update key[%ld] to new data %s error!\n", key, data);
		return -1;
	}
#ifdef debug
	else
	{
		printf("update key[%ld] to new data %s success!\n", key, data);
	}
#endif
	return 0;
}

/* search and delete */
int search_vnode(unsigned int key, rb_node_t* root, rb_node_t* node)
{
	if ((node = rb_search(key, root)))
#ifdef debug
    {
		printf("search key %ld success, data %s!\n", key, node->data);
	}
	else
#endif
	{
        printf("search key %ld no data!\n", key);
		return -1;
    }
	return 0;
}

/* delete vnode */
int delete_vnode(unsigned int key, rb_node_t* root, rb_node_t* node)
{
	if ((root = rb_delete(key, root)))
#ifdef debug
    {
        printf("delete key %ld , data %s success\n", key, root->data);
    }
    else
#endif
    {
        printf("delete key %ld error\n", key);
		return -1;
    }
	return 0;
}
