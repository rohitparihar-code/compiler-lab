%{
    #include <stdio.h>
    #include <string.h>
    char a[] = " ";
%}
%%
.|\n strcat(a, yytext);
%%

int yywrap() {
    return 1;
}

int main(int argc, char* argv[]) {
    yyin = fopen(argc > 1 ? argv[1] : "input.txt", "r");
    yylex();
    printf("%s", a);
    return 0;
}