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
#include "md5hash.h"
#include "init.h"
#include "node.h"

/* If you need to modify vnodes in multi-event, 
and suggest it is use lock. */
int vnodes = 0;

/*****************************************************************/
int main(int argc, char *argv[])
{
    int i, ret, count = atoi(argv[1]) - 1;
	if(count > max_nodes || count < 0)
	{
		printf("stdin error\n");
		exit(0);
	}

/* Init node */
	pnode mac_node[nodes + 0xffff];
	my_init(mac_node);
	printf(
		"**********************Init starting************************\n");
	
	for(i = 0; i <= count; i++)
	{
		printf("init node\t%d\t%s.\n", mac_node[i].id, mac_node[i].ipv4);
	}
	printf(
		"**********************Init success*************************\n");
	

    rb_node_t* root = NULL, *node = NULL;	/* Init rbtree */
    hash_key key;
	unsigned char id[1024];
/* add node */
    for (i = 0; i <= count; i++)
    {
        ret = add_vnode(&mac_node[i], root, vnum_max);
		if(ret != 0)
        {
            printf("insert error %lld %d!\n", mac_node[i].id, ret);
        }
	}

/* search */
	unsigned char tmp[0xf];
	int j;
    for (i = 0; i <= count; i++)
    {
        sprintf(id, "%d", mac_node[i].id);
		for(j = 0; j <= vnum_max; j++)
		{
        	if((strlen(tmp) + strlen(id)) > 1024)
        	{
            	printf("Too long.\n");
      	    }        

			sprintf(tmp, "%d", j);
     	    strcat(id, tmp);
			printf("id = %s\n", id);
    	    key = md5hash((void *)id);
	        if ((node = rb_search(key, root)))
	        {
	            printf("search key %ld->%s!\n", node->key, node->data);
	        }
	        else
	        {
	           	printf("search key %ld->%s!\n", key, node);
       		}
		}
	}
    return 0;
}
