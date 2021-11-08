%{
    #include<stdio.h>
    extern FILE *yyin;
    int a[100];
    int a1[100];
    int a2[100];
    int k=0;
%} 

%token HEADER DIGIT ENTER HEADER1 MAIN OPENC CLOSEC INT FLOAT ID SPACE COMMA SEMICOLON OPENB CLOSEB EQUAL GT LT FOR WHILE PLUS MINUS MULTIPLY IF ERROR ELSE

%%
s:HEADER HEADER1 ENTER MAIN OPENB CLOSEB ENTER OPENC ENTER a ENTER b l CLOSEC {printf("success\n"); display();exit(0);}
; 
l:loop l|ie l|loop|ie
;
ie:IF OPENB s2 sym k CLOSEB ENTER OPENC ENTER e CLOSEC ENTER ELSE ENTER OPENC ENTER e CLOSEC ENTER {a2[$3]=1; if($5>=0) a2[$5]=1; }
;
loop:FOR OPENB s2 EQUAL DIGIT SEMICOLON s2 sym k SEMICOLON s2 PLUS PLUS CLOSEB ENTER OPENC ENTER e CLOSEC ENTER {a1[$3]=1;a2[$3]=1;a2[$7]=1;a2[$11]=1;if($9>=0) a2[$9]=1;}
;
e:loop|expr|expr e|a ENTER e|ie e|ie
;
expr:s2 EQUAL expr1 SEMICOLON ENTER {if (a1[$1]!=1){ a1[$1]=1; } a2[$1]=1;}
;
expr1:k PLUS k {if ($1 >=0) {a2[$1]=1;} if ($3 >=0) {a2[$1]=1;}}
      |k MINUS k {if ($1 >=0) {a2[$1]=1;} if ($3 >=0) {a2[$1]=1;}}
      |k MULTIPLY k {if ($1 >=0) {a2[$1]=1;} if ($3 >=0) {a2[$1]=1;}}
      |k {if ($1 >=0) {a2[$1]=1;}}
;
sym:LT|GT
;
k:DIGIT
 | s2 {$$=$1;}
;
b:p |p b
;
p:t SPACE a2
  |a2
;
a2:s2 EQUAL DIGIT SEMICOLON ENTER {a1[$1]=1;a[$1]=1;}
;
a:t SPACE s1 SEMICOLON
;
s1: s2 COMMA s1 {a[$1]=1;}
    |s2 {a[$1]=1;}
;
s2: ID {$$=$1; k++;}
;
t:INT | FLOAT
;
%%
main()
{
	yyin=fopen("test2.c","r");
	yyparse();
}
yyerror()
{
	printf("error has occured\n");
}
display()
{
	int i=0;
	int j;
	int c=0;
	while(i<100)
	{
		c=97+i;
		if(a[i]==1 && a1[i]==1 && a2[i]==1)
		{
			// printf("%c",c);
			// printf(" is a beauty \n");
            continue ;
		}
		if(a[i]==1 && a1[i]==1 && a2[i]!=1)
		{
			printf("%c",c);
			printf(" has been initialized but not been used \n");
			
		}
		if(a[i]!=1 || a1[i]!=1)
		{
			if(a2[i]==1)
                        {
				printf("%c",c);
				printf(" has been used but not initialized \n");
			}
						
		}
		i++;
	}
}