%{
#include<stdio.h>
%}
%token NUM
%left '+' '-' '*' '/'
%right NEGATIVE
%%
S   :   E {printf("\n");}
    ;
E   :   E '+' T {printf("+ ");}
    |   E '-' T {printf("- ");}
    |   T
    ;
T   :   T '*' F {printf("* ");}
    |   T '/' F {printf("/ ");}
    |   F
    ;

F   :   '(' E ')'
    |   NUM     {printf("%d ", yylval);}
    ;
%%

int main(){
    printf("Enter the infix expression : ");
    yyparse();
    printf("\n");
}

//char st[100] 

int yyerror (char *msg) {
    return printf ("error YACC: %s\n", msg);
}
