#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"

/* Generation vnode from mac_node */
int add_vnode(pnode *vnode, rb_node_t* rbtree, int vnum)
{
	unsigned long int key;
	int ret;
	unsigned char id[1024];
	rb_node_t *root;
	sprintf(id, "%d", vnode->id);
	if(vnum <= 1)
	{
		key = md5hash((void *)id);
		if(root = rb_insert(key, vnode->ipv4, rbtree))
		{
			ret = 0;
		}	
		else
		{
			ret = -1;
		}
	}
	else if(vnum > 1)
	{
		unsigned char tmp[0xf];
		unsigned int i;
    	for (i = 0; i < vnum_max + 1; i++)
    	{
			if((strlen(tmp) + strlen(id)) > 1024)
			{
				printf("Too long.\n");
				ret = -1;
				exit(ret);
			}
			sprintf(tmp, "%d", i);
			strcat(id, tmp); 
        	key = md5hash((void *)id);
        	if((root = rb_insert(key, vnode->ipv4, rbtree)))
			{
				ret = 0;
        	}
        	else
			{
				ret = -1;
    	    }
		}
	}
	else if(vnum < 0)
	{
		ret = -1;
	}
	return ret;
}
