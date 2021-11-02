%{
    #include <stdio.h>
    typedef struct node
    {
        struct node *left;
    struct node *right;
    char *token;
    } node;
 
    node *mknode(node *left, node *right, char *token);
    void printtree(node *tree);
    
    #define YYSTYPE struct node *
%}

%start S
%token NUMBER
%token PLUS MINUS TIMES DIVIDE POWER
%token LEFT_PARENTHESIS RIGHT_PARENTHESIS
%token END
%left PLUS MINUS
%left TIMES DIVIDE

%%
S   : E END { printtree($1); printf("\n"); return 1;}
    ;
E   : T {$$ = $1;}
    | E PLUS T {$$ = mknode($1, $3, "+");}
    | E MINUS T {$$ = mknode($1, $3, "-");} 
    ;
T   : F {$$ = $1;}
    | T TIMES F {$$ = mknode($1, $3, "*");}
    | T DIVIDE F {$$ = mknode($1, $3, "/");}
    ;
F   : NUMBER {$$ = mknode(0,0,(char *)yylval);}
    | LEFT_PARENTHESIS E RIGHT_PARENTHESIS {$$ = $2;}
    ;


%%
int main()
{
    printf("Enter integer expression : ");
    return yyparse ( );
}

node *mknode(node *left, node *right, char *token)
{ 
    /* malloc the node */
    node *newnode = (node *)malloc(sizeof(node));
    char *newstr = (char *)malloc(strlen(token)+1);
    strcpy(newstr, token);
    newnode->left = left;
    newnode->right = right;
    newnode->token = newstr;
    return(newnode);
}

void printtree(node *tree)
{
    int i;
    if (tree->left || tree->right)
    printf("(");
    printf(" %s ", tree->token);
    if (tree->left)
    printtree(tree->left);
    if (tree->right)
    printtree(tree->right);
    if (tree->left || tree->right)
    printf(")");
}

int yyerror (char *s)
{
    printf ("%s\n", s);
}