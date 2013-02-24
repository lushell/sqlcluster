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
	}
	return ret;
}
