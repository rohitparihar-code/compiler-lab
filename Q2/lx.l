%{
#include "y.tab.h"
%}


%%
[0-9]+ {yylval = (int)yytext; return NUMBER;}
[\t] ;
"+" return(PLUS);
"-" return(MINUS);
"*" return(TIMES);
"/" return(DIVIDE);
"^" return(POWER);
"(" return(LEFT_PARENTHESIS);
")" return(RIGHT_PARENTHESIS);
\n  return(END);


%%
int yywrap()
{
    return 1;
} 