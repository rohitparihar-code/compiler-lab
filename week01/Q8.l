%option noyywrap

%{
#include<stdio.h>
int idents=0, keywords=0, operators=0, comments=0, strings=0, numerics=0, paranthesis=0;

%}

%%
"/*"(.|\n|\t)*"*/" {printf("%s : Multiline comment\n", yytext); comments++;}
"//"(.|\t)*"\n" {printf("%s : Line comment\n", yytext); comments++;}
main|then|endif|enddo|auto|else|long|switch|break|enum|register|typedef|case|extern|return|union|char|float|short|unsigned|const|for|signed|void|continue|goto|sizeof|volatile|default|if|staticwhile|do|int|struct|_Packed|double {printf("%s : Keyword\n", yytext); keywords++;}
\{ {printf("%s : Block starts\n", yytext);}
\} {printf("%s : Block ends\n", yytext);}
\".*\" {printf("%s : String\n", yytext); strings++;}
[a-z_][a-z0-9_]* {printf("%s : Identifier\n", yytext); idents++;}
[0-9]+ {printf("%s : Numeric\n", yytext); numerics++;}
= {printf("%s : Assignment Operator\n", yytext); operators++;}
\+|-|\*|"/" {printf("%s : Arithmetic Operator\n", yytext); operators++;}
"<"|"<="|"=="|">="|">"|"!=" {printf("%s : Relational Operator\n", yytext); operators++;}
\{|\}|\[|\]|\(|\) {printf("%s : Paranthesis\n", yytext); paranthesis++;}

%%
int main(int argc, char* argv[])
{
    yyin = fopen(argc > 1 ? argv[1] : "input.c", "r");
    yyout = fopen(argc > 2 ? argv[2] : "output.c", "w"); 
    yylex();

    printf("\n\n");
    printf("Number of keywords=%d\n", keywords);
    printf("Number of idents=%d\n", idents);
    printf("Number of operators=%d\n", operators);
    printf("Number of strings=%d\n", strings);
    printf("Number of numerics=%d\n", numerics);
    printf("Number of comments=%d\n", comments);
    printf("Number of paranthesis=%d\n", paranthesis);
    return 0;
}
