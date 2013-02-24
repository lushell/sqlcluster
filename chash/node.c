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

int add_vnode(rb_node_t *root, pnode *mac_node)
{
	int ret, i;
    hash_key key;
	unsigned char id[1023], tmp[15];
	sprintf(id, "%d", mac_node->id);
	for(i = 0; i < vns; i++)
	{
		sprintf(tmp, "%d", i);
		strcat(id, tmp);
       	key = md5hash((void *)id);
		printf("key = %u, ptr = %u, ", key, &key);
      	if (rb_insert(key, mac_node->ipv4, root))
        {
           	printf("insert key[%u], %s success, ", 
							key, mac_node->ipv4);
			ret = 0;
       	}
       	else
       	{
           	printf("insert key[%ld] error!\n", key);
			ret = -1;
       	}
	}
	return ret;
}
