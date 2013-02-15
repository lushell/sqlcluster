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
	node *prev, *next, *head, *data;
	int i;
	if((head = (node *)malloc(sizeof(node))) == NULL)
	{
		perror("malloc");
		exit(1);
	}
	head->name[0] = '\0';
	head->link = NULL;
	prev = head;
	for(i = 0; i < n; i++)
	{
		if((data = (node *)malloc(sizeof(node))) == NULL)
		{
			perror("malloc");
			exit(1);
		}
		prev->link = data;
		printf("Please %sth's name\n", i + 1);
		scanf("%s", data->name);
		data->link = NULL;
		prev = data;
	}
	return head;
}

int main(void)
{
	int number;
	number = 10;
	node *stu;
	stu = create(number);
	return 0;
}
