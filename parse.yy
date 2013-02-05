%{
#include <stdio.h>
#include <string.h>
#include <math.h>
char *sql_type;
char *text;
%}

%%
["select"|"insert"]	printf("sql_type is %s\n", sql_type = yytext);
[0-9]*[a-zA-Z]*	printf("sql text is %s\n", text = yytext);
.
%%

int sql_parse(struct command *s)
/* int main(int argc, char *argv[]) */
{
	char *str = (char *)s->str;
	yyin = str;
	yylex();
	return 0;
}

int yywrap()
{
	return 1;
}
