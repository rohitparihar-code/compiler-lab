%option noyywrap
%{
#include<stdio.h>
int c_idents=0, c_keys=0, c_opers=0;
int spaces=0;
%}
%%
stop return 0;
int|if|then|else|endif|while|do|enddo|print {printf("Key Word\n"); c_keys++;}
[a-z][a-z0-9]* {printf("Identifier\n"); c_idents++;}
\+|-|\*|\/|<|<=|==|>=|>|!=|= {printf("Operator\n"); c_opers++;}
. ;
\n ;
%%
int main()
{
    yylex();
    printf("\nNumber of identifiers = %d\nNumber of keywords = %d\nNumber of operators = %d\n", c_idents, c_keys, c_opers);
    return 0;
}
