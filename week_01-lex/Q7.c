#include<stdio.h>
#include<string.h>
#include<ctype.h>

int is_keyword(char *A)
{
    if(!strcmp(A, "int") || !strcmp(A, "if") || !strcmp(A, "then")
    || !strcmp(A, "else") || !strcmp(A, "endif") || !strcmp(A, "while")
    || !strcmp(A, "do") || !strcmp(A, "enddo") || !strcmp(A, "print"))
        return 1;
    return 0;
}

int is_operator(char a)
{
    if(a=='+' || a=='-' || a=='*' || a=='/' ||
       a=='<' || a=='<' || a=='=')
        return 1;
    return 0;
}

int is_parenthesis(char a)
{
    if(a=='{' || a=='}'  || a=='('  || a==')'  || a=='['  || a==']')
        return 1;
    return 0;
}

int main(int argc, char* argv[])
{
    FILE *fptr=fopen(argc > 1 ? argv[1] : "input.c", "r");
    
    char cur=getc(fptr);
    if(cur==EOF)
        return 0;
    char next=getc(fptr);

    char current_token[100];
    int pos=0;
    current_token[0]=0;

    int comment_active=0;
    int token_activity=0;
    //0 for token inactive
    //1 for token active is keyword or identifier
    //2 for token active is numeric
    //3 for token is 
    while(cur!=EOF)
    {
        if(comment_active==0 && cur=='/' && next=='*')
        {
            comment_active=1;
            if(cur==EOF)
                return 0;
            next=getc(fptr);
            continue;
        }
        else if(comment_active==1 && cur=='*' && next=='/')
        {
            comment_active=0;
            cur=getc(fptr);
            if(cur==EOF)
                return 0;
            next=getc(fptr);
            continue;
        }
        else if(comment_active==1)
        {
            cur=next;
            next=getc(fptr);
            continue;
        }
        
        if(token_activity==0)
        {
            if(cur==' ' || cur=='\t' || cur=='\n' || cur==';')
            {
                cur=next;
                next=getc(fptr);
                continue;
            }
            else if(is_parenthesis(cur))
            {
                printf("%c : Parenthesis\n", cur);
                cur=next;
                next=getc(fptr);
                continue;
            }
            else if('a'<=cur && cur<='z')
            {
                token_activity=1;
                current_token[0]=cur;
                pos=1;
                current_token[1]=0;
                cur=next;
                next=getc(fptr);
                continue;
            }
            else if('0'<=cur && cur<='9')
            {
                token_activity=2;
                current_token[0]=cur;
                pos=1;
                current_token[1]=0;
                cur=next;
                next=getc(fptr);
                continue;
            }
            else if(is_operator(cur))
            {
                if(cur=='=' && next=='=')
                {
                    printf("== : Assignment operator\n");
                    cur=getc(fptr);
                    if(cur==EOF)
                        return 0;
                    next=getc(fptr);
                    continue;
                }
                else if(cur=='+' || cur=='-' || cur=='*' || cur=='/')
                {
                    printf("%c : Arithmetic operator\n", cur);
                    cur=next;
                    next=getc(fptr);
                    continue;
                }
                else if(next=='=')
                {
                    printf("%c%c : Relational operator\n", cur, next);
                    cur=getc(fptr);
                    if(cur==EOF)
                        return 0;
                    next=getc(fptr);
                    continue;
                }
                else
                {
                    printf("%c : Relational operator\n", cur);
                    cur=next;
                    next=getc(fptr);
                    continue;
                }
            }
        }
        else if(token_activity==1)
        {
            if(('a'<=cur && cur<='z') || ('0'<=cur && cur<='9'))
            {
                current_token[pos]=cur;
                pos++;
                current_token[pos]=0;
                cur=next;
                next=getc(fptr);
                continue;
            }
            else
            {
                if(is_keyword(current_token))
                    printf("%s : Keyword\n", current_token);
                else
                    printf("%s : Identifier\n", current_token);
                token_activity=0;
                current_token[0]=0;
                pos=0;
                continue;
            }
        }
        else
        {
            if('0'<=cur && cur<='9')
            {
                current_token[pos]=cur;
                pos++;
                current_token[pos]=0;
                cur=next;
                next=getc(fptr);
                continue;
            }
            else
            {
                printf("%s : Numeric\n", current_token);
                token_activity=0;
                current_token[0]=0;
                pos=0;
                continue;
            }
        }

        cur=next;
        next=getc(fptr);
    }

    if(token_activity==1)
    {
        if(is_keyword(current_token))
            printf("%s : Keyword\n", current_token);
        else
            printf("%s : Identifier\n", current_token);
    }
    else if(token_activity==2)
    {
        printf("%s : Numeric\n", current_token);
    }

}