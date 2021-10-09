%{
    #include <stdio.h>
    #include <string.h>
    char a[1000] = "";
%}
%%
.|\n strcat(a, yytext);
%%

int yywrap() {
    return 1;
}

int main(int argc, char* argv[]) {
    yyin = fopen(argc > 1 ? argv[1] : "input.c", "r");
    yylex();
    printf("%s", a);
    return 0;
}
