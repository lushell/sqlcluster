%{
#include <stdio.h>
#include <string.h>
#include <math.h>
int sqlnum=0;
char *sql_type;
%}

%%
["\;"]		sqlnum++;
["select"]	sql_type = yytext;
["from"]	    printf("%s\n", yytext);
["where"]		printf("%s\n", yytext);
[0-9]*[a-zA-Z]*	printf("%s\n", yytext);
.
%%

int main(void)
{
	yylex();
	printf("sql type is %s, sql sum is %d\n", sql_type, sqlnum);
	return 0;
}	

int yywrap()
{
	return 1;
}
