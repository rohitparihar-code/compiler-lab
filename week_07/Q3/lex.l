%{
    #include"y.tab.h"
    extern yylval;
%}
digit [0-9]
letter [a-zA-Z]
id {letter}({letter}|{digit})*

%%
"#include" {return HEADER;}
"<stdio.h>" {return HEADER1;}
"main" {return MAIN;}
"("  {return OPENB;}
")"  {return CLOSEB;}
"{"  {return OPENC;}
"}" {return CLOSEC;}
"=" {return EQUAL;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MULTIPLY;}
{digit} {return DIGIT;}
"int" {return INT;}
"for" {return FOR;}
"float" {return FLOAT;}
"if" {return IF;}
"else" {return ELSE;}
"while" {return WHILE;}
"<" {return GT;}
">" {return LT;}
{id} {yylval=yytext[0]-'a';return ID;}
"," {return COMMA;}
";" {return SEMICOLON;}
[" "] {return SPACE;}
"\n" {return ENTER;}
. {return ERROR;}
%%
int yywrap() {
    return 1;
}