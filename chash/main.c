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
    hash_key key;
    rb_node_t* root = NULL, *node = NULL;
	unsigned char id[8];
	pnode mac_node[nodes + 0xff];
	my_init(mac_node);
	for(i = 0; i < count; i++)
	{
		printf("node%d=%s.\n", mac_node[i].id, mac_node[i].ipv4);
	}
	printf("\n"
		"***********************************************************\n"
		"***********************************************************\n"
		"**********************Init success*************************\n"
		"***********************************************************\n"
		"***********************************************************\n");
	

/* add node */
    for (i = 0; i < count; i++)
    {
		sprintf(id, "%d", mac_node[i].id);
        key = md5hash(id);
		printf("ipv4 = %s\n", mac_node[i].ipv4);
        if ((root = rb_insert(key, mac_node[i].ipv4, root)))
        {
            printf("insert key[%ld], rbnode key[%ld] = value[%s] success!\n", 
					key, root->key,  root->data);
        }
        else
        {
            printf("insert key[%ld] error!\n", key);
            exit(-1);
        }
	}

/* update node */
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

/* search and delete */
    for (i = 0; i < count; i++)
    {
		sprintf(id, "%d", mac_node[i].id);
        key = md5hash((void *)id);
        if ((node = rb_search(key, root)))
        {
            printf("search key %ld success, data %s!\n", key, node->data);
        }
        else
        {
            printf("search key %ld no data!\n", key);
        }

            if ((root = rb_delete(key, root)))
            {
                printf("delete key %ld success\n", key);
            }
            else
            {
                printf("delete key %ld error\n", key);
            }
    }
    return 0;
}
