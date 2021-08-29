%{
    // lex program to remove redundant spaces.
    #include <stdio.h>
    #include <string.h>
    char s[] = " ";
%}
%%
[\t ]+ fprintf(yyout, " ");
.|\n fprintf(yyout, "%s", yytext);
%%

int yywrap() {
    return 1;
}

int main(int argc, char* argv[]) {
    yyin = fopen(argc > 1 ? argv[1] : "input.txt", "r");
    // yyout = fopen(argc > 2 ? argv[2] : "output.txt", "w");
    yylex();
    printf("%s", yyout);
    return 0;
}