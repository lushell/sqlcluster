%{
#include <stdio.h>
#include <string.h>
int ADD, NUMBER;
ADD = 0;
NUMBER = 1;
%}

%%
"+"	{ return ADD; }
[0-9]+	{return NUMBER; }
[ \t]	{}
%%
int main(int argc, char **argv)
{
	printf("%d,%d\N", ADD, NUMBER);
	return 0;
}
