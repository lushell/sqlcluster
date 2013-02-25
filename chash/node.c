/* Copyright (c) 2000, 2011, tangchao@360buy.com and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., Beijing China - 2013.1.24 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"

<<<<<<< HEAD
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
=======
int generate_vkey(pnode *mac_node)
{
	int i;
	hash_key vkey;
	unsigned char id[1023], tmp[15];
	sprintf(id, "%u", mac_node->id);
	for(i = 0; i < vns; i++)
	{
		sprintf(tmp, "%u", i);
		strcat(id, tmp);
		vkey = md5hash((void *)id);
		mac_node->vkey[i] = vkey;
	}
	return 0;
}

int add_vnode(rb_node_t *root, pnode *mac_node)
{
	rb_node_t *node = NULL;
	int ret, i;
	for(i = 0; i < vns; i++)
	{
      	if (rb_insert(mac_node->vkey[i], mac_node->ipv4, root))
        {
           	printf("rbtree insert vkey[%u], %s success.\n", 
							mac_node->vkey[i], mac_node->ipv4);
			node = rb_search(mac_node->vkey[i], root);
			printf("search result %u\t%s.\n", node->key, node->data);
			ret = 0;
       	}
       	else
       	{
           	printf("rbtree insert vkey[%u] error.\n", mac_node->vkey[i]);
			ret = -1;
       	}
>>>>>>> 6db37952fadc9ab313299bfc85fbd431eef46c10
	}
	return ret;
}
