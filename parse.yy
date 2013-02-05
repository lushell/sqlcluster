%{
#include <stdio.h>
<<<<<<< HEAD
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
=======
#include <math.h>
#include <string.h>
%}
int 	[0-9]+
float	[0-9]*\.[0-9]+
%%
>>>>>>> c43e9e766be03fa9ec79c2bd3568b372730a7f34

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
