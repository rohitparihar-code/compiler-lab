%option noyywrap
%{
#include<stdio.h>
int c_idents=0, c_keys=0, c_opers=0;
int spaces=0;
%}
%%
stop return 0;
main|then|endif|enddo|auto|else|long|switch|break|enum|register|typedef|case|extern|return|union|char|float|short|unsigned|const|for|signed|void|continue|goto|sizeof|volatile|default|if|staticwhile|do|int|struct|_Packed|double {printf("Key Word\n"); c_keys++;}
[a-z_][a-z0-9_]* {printf("Identifier\n"); c_idents++;}
\+|-|\*|\/|<|<=|==|>=|>|!= {printf("Operator\n"); c_opers++;}
. ;
\n ;
%%
int main()
{
    yylex();
    printf("\nNumber of identifiers = %d\nNumber of keywords = %d\nNumber of operators = %d\n", c_idents, c_keys, c_opers);
    printf("Total Number of Tokens in the program=%d\n",  c_idents+c_keys+c_opers);
    return 0;
}