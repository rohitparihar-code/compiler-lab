// Dead Code Removal Program

#include <stdio.h>
#include <conio.h>
#include <string.h>

struct expression
{
    char lhs;
    char rhs[20];
} exp[10], res[10];

int main()
{
    int a, i, k, j, n, z = 0, m, q;
    char *p, *l;
    char temp, t;
    char *tem;
    char gb;

    printf("Enter no of expressions : ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Expression %d : ", i + 1);
        exp[i].lhs = getche();
        scanf("%c%s", &gb, exp[i].rhs);
    }

    // printf("\nIntermediate Code :\n");
    printf("\n\n");
    for (i = 0; i < n; i++)
    {
        printf("%c", exp[i].lhs);
        printf("%s\n", exp[i].rhs);
    }

    for (i = 0; i < n - 1; i++)
    {
        temp = exp[i].lhs;
        for (j = 0; j < n; j++)
        {
            p = strchr(exp[j].rhs, temp);
            if (p)
            {
                res[z].lhs = exp[i].lhs;
                strcpy(res[z].rhs, exp[i].rhs);
                z++;
            }
        }
    }

    res[z].lhs = exp[n - 1].lhs;
    strcpy(res[z].rhs, exp[n - 1].rhs);
    z++;

    printf("\nAfter dead code Removal :\n");
    for (k = 0; k < z; k++)
    {
        printf("%c", res[k].lhs);
        printf("%s\n", res[k].rhs);
    }

    for (m = 0; m < z; m++)
    {
        tem = res[m].rhs;
        for (j = m + 1; j < z; j++)
        {
            p = strstr(tem, res[j].rhs);
            if (p)
            {
                t = res[j].lhs;
                res[j].lhs = res[m].lhs;
                for (i = 0; i < z; i++)
                {
                    l = strchr(res[i].rhs, t);
                    if (l)
                    {
                        a = l - res[i].rhs;
                        res[i].rhs[a] = res[m].lhs;
                    }
                }
            }
        }
    }

    printf("\nAfter eliminating common expression :\n");
    for (i = 0; i < z; i++)
    {
        printf("%c", res[i].lhs);
        printf("%s\n", res[i].rhs);
    }

    // duplicate production elimination
    for (i = 0; i < z; i++)
    {
        for (j = i + 1; j < z; j++)
        {
            q = strcmp(res[i].rhs, res[j].rhs);
            if ((res[i].lhs == res[j].lhs) && !q)
            {
                res[i].lhs = '\0';
                strcpy(res[i].rhs, "\0");
            }
        }
    }

    printf("\nOptimized code :\n");
    for (i = 0; i < z; i++)
    {
        if (res[i].lhs != '\0')
        {
            printf("%c", res[i].lhs);
            printf("%s\n", res[i].rhs);
        }
    }

    printf("\n");
}