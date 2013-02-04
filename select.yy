%{
#include <math.h>
#include <string.h>
int key_flag = 0;
int table_flag = 0;
int insert_flag = 0;
int insert_field_order = 0;//记录insert语句中主键所在列的位置
int insert_value_order = 0;
int insert_tmp = 0;
char *id="id";
char *last_text;
%}
DIGIT    [0-9]
ID       [a-z][a-z0-9]*
%%
{DIGIT}+	{//输出整形数字
				if(key_flag == 2)//select，delete，update输出的主键的值
                                {   
                                        printf(" %d\n", atoi( yytext )); 
                                }   
                                if(insert_flag >=4 && (insert_flag % 2 == 0)) 
                                {   
                                        if(insert_value_order == insert_field_order)
                                        {   
                                                printf("insert primary key value:%d\n",atoi(yytext));
                                        }   
                                        insert_value_order ++; 
                                }   
                 }   
        {DIGIT}+"."{DIGIT}*        {//输出浮点型
                                if(key_flag == 2)
                                {   
                                        printf(" %g\n", atof( yytext ));
                                }
                       }
 
           select|insert|update|delete        {//碰到这几个关键字就输出
                                last_text=strdup(yytext);
                                if(strcmp(yytext, "insert") == 0)
                                {
                                        insert_flag = 1;
                                }
                                printf( "your sql command is %s\n", yytext );
                                }
           from|into   {
                                last_text=strdup(yytext);
                       }
           {ID}        {
                                if(!strcmp(last_text, "from")//输出表名
                                         ||!strcmp(last_text, "into") ||!strcmp(last_text, "update") )
                                {
                                        printf( "table name is %s\n", yytext );
                                }
                                last_text=strdup(yytext);//记录本次记录
                                if(strcmp(yytext,id)==0)
                                {
                                        key_flag = 1;//key_flag为1的时候，输出主键的操作符，是2的时候表示输出键值
                                        printf("the primary key is %s\n",yytext);
                                }
                                if(key_flag == 2)
                                {
                                        printf(" %s\n",  yytext );
                                }
                                if((insert_flag == 2) && (insert_tmp == 0))
                                {
                                        if(strcmp(yytext, id) == 0)
                                        {
                                                insert_tmp = 1;
                                        }
                                        else
                                        {
                                                insert_field_order ++;
                                        }
                                }
                      }
 
           "<"|"<="|">"|">="|"="  {
                                if((key_flag == 1)&&(strcmp(last_text, id)==0))
                                {
                                        key_flag = 2;
                                        last_text=strdup(yytext);
                                        printf( "<key-opt-value>: %s ", id );
                                        printf( " %s ", yytext );//碰到操作符输出
                                }
                                //else if(key_flag == 1)printf( "error input: %s\n", yytext );
                        }
           "("          {//当insert语句遇到第一个"("，表示后面紧跟着的是field，insert_flag 值为2，第二次碰到就是values了
                                if(insert_flag == 1)
                                {
                                        insert_flag = 2;
                                }
                                else if(insert_flag >=3 && (insert_flag % 2 ==1))
                                {
                                        insert_flag ++;
                                }
                        }
           ")"          {//第一次碰到insert_flag 值为3，表示field的结束。
                                if(insert_flag == 2)
                                {
                                        insert_flag = 3;
                                }
                                else if(insert_flag >=4 && (insert_flag % 2 == 0))
                                {
                                        insert_flag ++;
                                }
                        }
           "\n"         {
                                key_flag = 0;
                                insert_flag = 0;
                                insert_field_order = 0;
                                insert_value_order = 0;
                                insert_tmp = 0;
                        }
           .      //     printf( "Unrecognized character: %s\n", yytext );//最后是不能辨认的字符
%%
 
        int    sql_parse(int argc, char *argv[])
        {
                ++argv, --argc;//循环输入
               if ( argc > 0 )
                       yyin = fopen( argv[0], "r" );
               else
                       yyin = stdin;
 
                   yylex();
        }
        yywrap()//仅表示程序结束
        {
                return 0;
        }

