%{
    // Lex program to count the number of lines and characters.
    #include <stdio.h>
    int ch=0, l=0;    
%}
%%
. {ch++; if (l==0) l++;}
\n l++;
%%

int yywrap() {
    return 1;
}

int main(int argc, char*argv[]) {
    yyin = fopen(argc > 1 ? argv[1] : "input.txt", "r");
    yylex();
    printf("Number of characters = %d\nNumber of lines = %d\n", ch, l);
    return 0;
}
