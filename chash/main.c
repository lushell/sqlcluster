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

/* If you need to modify vnodes in multi-event, and suggest it is use lock. */
int vnodes = 0;
/*****************************************************************/
int main(int argc, char *argv[])
{
    int i, count = atoi(argv[1]);
	if(count > nodes + 0xff || count < 0)
	{
		printf("stdin error\n");
		exit(0);
	}

/* Init node */
	pnode mac_node[nodes + 0xfff];
	my_init(mac_node);
	for(i = 0; i < count; i++)
	{
		printf("init node\t%d\t%s.\n", mac_node[i].id, mac_node[i].ipv4);
	}
	printf(
		"***********************************************************\n"
		"**********************Init success*************************\n"
		"***********************************************************\n\n");
	

    rb_node_t* root = NULL, *node = NULL;
    hash_key key;
	unsigned char id[16];
/* add node */
	printf("******************addition*********************\n");
    for (i = 0; i < count; i++)
    {
		sprintf(id, "%d", mac_node[i].id);
        key = md5hash((void *)id);
        if ((root = rb_insert(key, mac_node[i].ipv4, root)))
        {
            printf("insert key[%ld], %s success!\n", 
					key, mac_node[i].ipv4);
			vnodes++;
        }
        else
        {
            printf("insert key[%ld] error!\n", key);
        }
	}

	printf("rbtree data node sum = %d\n", vnodes);
/* update node */
	printf("******************update*********************\n");
	sprintf(id, "%d", mac_node[0].id);
	key = md5hash((void *)id);
	char c[] = "www.360buy.com", ret;
	if(ret = rb_update(key, root, c))
	{
		printf("update key[%ld] to new data %s error!\n", key, c);
	}
	else
	{
		printf("update key[%ld] to new data %s success!\n", key, c);
	}
	printf("******************search*********************\n");
/* search and delete */
    for (i = 0; i < count; i++)
    {
		sprintf(id, "%d", mac_node[i].id);
        key = md5hash((void *)id);
        if ((node = rb_search(key, root)))
        {
            printf("search key %ld success, data %s!\n", node->key, node->data);
        }
        else
        {
            printf("search key %ld->%s!\n", key, node);
        }
	}

	printf("******************delete*********************\n");
	for(i = 0; i < count; i++)
	{
		sprintf(id, "%d", mac_node[i].id);
        key = md5hash((void *)id);
        if ((root = rb_delete(key, root)))
        {
            printf("delete key %ld success\n", key);
			vnodes--;
        }
        else
        {
            printf("delete key %ld->%s\n", key, root);
        }
    }
	printf("rbtree data node sum = %d\n", vnodes);
    return 0;
}
