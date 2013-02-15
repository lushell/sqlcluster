%{
#include <stdio.h>
#include <string.h>
#include <math.h>
char *cmd_type;
char *cmd_text;
%}

%%
"select"|"insert"	printf("sql_type is %s\n", cmd_type = yytext);
[0-9]*[a-zA-Z]*	printf("sql text is %s\n", cmd_text = yytext);
.
%%

int sql_parse()
{
	yylex();
	return 0;
}

int yywrap()
{
	return 1;
}
