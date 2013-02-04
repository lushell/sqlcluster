%{
#include <stdio.h>
#include <string.h>
#include <math.h>
int sqlnum = 0;
%}
select	[sS]+[eE]+[lL]+[eE]+[cC]+[tT]+
from	[fF]+[rR]+[oO]+[mM]+
where	[wW]+[hH]+[eE]+[rR]+[eE]+
%%
[;]	sqlnum++;
[0-9]	printf("int :%s\n", yytext);
[0-9]*\.[0-9]+	printf("float :%s\n", yytext);
[a-zA-Z][a-zA-Z0-9]*	printf("var :%s\n", yytext);
[\+\-\*\/\%]	printf("op :%s\n", yytext);
.	printf("unkown :%c\n", yytext[0]);
%%

int main(void)
{
	linenum = 0;
	yylex();
	printf("\nLine Count: %d\n", linenum);
	return 0;
}

int yywrap()
{
	return 1;
}
