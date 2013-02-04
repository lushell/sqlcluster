#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 10
typedef struct _node
{
	char name[20];
	struct node *link;
} node;

node * create(int n)
{
	node *p, *h, *s; /* h head, p prev, s current */
	int i;
	if((h = (node *)malloc(sizeof(node))) == NULL)
	{
		perror("malloc");
		exit(1);
	}
	h->name[0] = '\0';
	h->link = NULL;
	p = h;
	for(i = 0; i < n; i++)
	{
		if((s = (node *)malloc(sizeof(node))) == NULL)
		{
			perror("malloc");
			exit(1);
		}
		p->link = s;
		printf("Please %sth's name\n", i + 1);
		scanf("%s", s->name);
		s->link = NULL;
		p = s;
	}
	return h;
}

int main(void)
{
	int number;
	node *head;
	number = 10;
	head = create(number);
	return 0;
}
