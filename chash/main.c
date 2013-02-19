#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "md5hash.h"
#include "init.h"
#include "node.h"


/*****************************************************************/
int main(int argc, char *argv[])
{
    int i, count = atoi(argv[1]);
	if(count > nodes + 0xff || count <= 0)
	{
		printf("stdin error\n");
		exit(0);
	}

/* Init node */
	pnode mac_node[nodes + 0xff];
	my_init(mac_node);
	for(i = 0; i < count; i++)
	{
		printf("init node %d=%s.\n", mac_node[i].id, mac_node[i].ipv4);
	}
	printf(
		"***********************************************************\n"
		"***********************************************************\n"
		"**********************Init success*************************\n"
		"***********************************************************\n"
		"***********************************************************\n");
	

    rb_node_t* root = NULL, *node = NULL;
    hash_key key;
	unsigned char id[8];
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
        }
        else
        {
            printf("insert key[%ld] error!\n", key);
        }
	}

/* update node */
/*
	printf("******************update*********************\n");
	sprintf(id, "%d", mac_node[2].id);
	key = md5hash((void *)id);
	char c[] = "100.100.100.100", ret;
	if(ret = rb_update(key, root, c))
	{
		printf("update key[%ld] to new data %s error!\n", key, c);
	}
	else
	{
		printf("update key[%ld] to new data %s success!\n", key, c);
	}
*/
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
            printf("delete key %ld , %s success\n", key, mac_node[i].ipv4);
        }
        else
        {
            printf("delete key %ld->%s\n", key, root);
        }
    }
    return 0;
}
