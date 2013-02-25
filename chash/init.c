#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"

void strtrim(char *s)
{
    int l = strlen(s);
    char *tmp = (char *)malloc(l);
	memset(tmp, 0, l);
    int i=0, j=0; 
    for(i = 0; i < l; i++) 
    {
        if(s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
        {
            tmp[j] = s[i];
            j++; 
        } 
    }
	sprintf(s, "%s", tmp);
	free(tmp);
}

int my_init(pnode *node)
{
	FILE *fp = fopen("/home/sqlcluster/sqlcluster/chash/stdin.txt","r");
	int i = 0;
	char buf[31];
	while(i <= max_node)
	{
		if(fgets(buf, 31, fp))
		{
			node[i].id = i;
			strtrim(buf);
			strcpy(node[i].ipv4, buf);
			memset(buf, 0, 32);
			i++;
		}
		else
		{
			break;
		}
	}
	return 0;
}
