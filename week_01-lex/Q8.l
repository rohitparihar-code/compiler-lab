%option noyywrap

%{
#include<stdio.h>
int idents=0, keywords=0, operators=0, comments=0, strings=0, numerics=0, paranthesis=0;

%}

%%
"/*"(.|\n|\t)*"*/" {printf("%s : Multiline comment\n", yytext); comments++;}
int|if|then|else|endif|while|do|enddo|print {printf("%s : Keyword\n", yytext); keywords++;}
\{ {printf("%s : Block starts\n", yytext);}
\} {printf("%s : Block ends\n", yytext);}
\".*\" {printf("%s : String\n", yytext); strings++;}
[a-z_][a-z0-9_]* {printf("%s : Identifier\n", yytext); idents++;}
[0-9]+ {printf("%s : Constant\n", yytext); numerics++;}
= {printf("%s : Assignment Operator\n", yytext); operators++;}
\+|-|\*|"/" {printf("%s : Arithmetic Operator\n", yytext); operators++;}
"<"|"<="|"=="|">="|">"|"!=" {printf("%s : Relational Operator\n", yytext); operators++;}
\[|\]|\(|\) {printf("%s : Paranthesis\n", yytext); paranthesis++;}

%%
int main(int argc, char* argv[])
{
    yyin = fopen(argc > 1 ? argv[1] : "input.c", "r");
    yyout = fopen(argc > 2 ? argv[2] : "output.c", "w"); 
    yylex();

    printf("\n\n");
    printf("Number of keywords=%d\n", keywords);
    printf("Number of identifiers=%d\n", idents);
    printf("Number of operators=%d\n", operators);
    printf("Number of strings=%d\n", strings);
    printf("Number of numerics=%d\n", numerics);
    printf("Number of comments=%d\n", comments);
    printf("Number of paranthesis=%d\n", paranthesis);
    printf("Total number of Tokens=%d\n", keywords+idents+operators);
    return 0;
}
