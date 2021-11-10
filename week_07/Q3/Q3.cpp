// Dead Code Removal Program

#include <stdio.h>
#include <conio.h>
#include <string.h>

struct expression
{
    char l;
    char r[20];
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
        exp[i].l = getche();
        scanf("%c%s", &gb, exp[i].r);
    }

    // printf("\nIntermediate Code :\n");
    printf("\n\n");
    for (i = 0; i < n; i++)
    {
        printf("%c", exp[i].l);
        printf("%s\n", exp[i].r);
    }

    for (i = 0; i < n - 1; i++)
    {
        temp = exp[i].l;
        for (j = 0; j < n; j++)
        {
            p = strchr(exp[j].r, temp);
            if (p)
            {
                res[z].l = exp[i].l;
                strcpy(res[z].r, exp[i].r);
                z++;
            }
        }
    }

    res[z].l = exp[n - 1].l;
    strcpy(res[z].r, exp[n - 1].r);
    z++;

    printf("\nAfter dead code Removal :\n");
    for (k = 0; k < z; k++)
    {
        printf("%c", res[k].l);
        printf("%s\n", res[k].r);
    }

    //sub expression elimination
    for (m = 0; m < z; m++)
    {
        tem = res[m].r;
        for (j = m + 1; j < z; j++)
        {
            p = strstr(tem, res[j].r);
            if (p)
            {
                t = res[j].l;
                res[j].l = res[m].l;
                for (i = 0; i < z; i++)
                {
                    l = strchr(res[i].r, t);
                    if (l)
                    {
                        a = l - res[i].r;
                        res[i].r[a] = res[m].l;
                    }
                }
            }
        }
    }

    printf("\nAfter eliminating common expression :\n");
    for (i = 0; i < z; i++)
    {
        printf("%c", res[i].l);
        printf("%s\n", res[i].r);
    }

    // duplicate production elimination
    for (i = 0; i < z; i++)
    {
        for (j = i + 1; j < z; j++)
        {
            q = strcmp(res[i].r, res[j].r);
            if ((res[i].l == res[j].l) && !q)
            {
                res[i].l = '\0';
                strcpy(res[i].r, "\0");
            }
        }
    }

    printf("\nOptimized code :\n");
    for (i = 0; i < z; i++)
    {
        if (res[i].l != '\0')
        {
            printf("%c", res[i].l);
            printf("%s\n", res[i].r);
        }
    }

    printf("\n");
}