// Program to generate 3 address codes

#include <bits/stdc++.h>

using namespace std;

void quadruple()
{
    char g;
    scanf("%c", &g);
    char line[20];
    int s[20];
    int t = 1;
    int i = 0;

    printf("\nEnter Expression: ");
    gets(line);

    for (i = 0; i < 20; i++)
        s[i] = 0;

    // Op -> Operator
    // a1 -> Argument 1
    // a2 -> Argument 2
    // re -> Result
    printf("op\ta1\ta2\tre\n");

    for (i = 2; line[i] != '\0'; i++)
    {
        if (line[i] == '/' || line[i] == '*')
        {
            printf("\n");
            if (s[i] == 0)
            {
                if (s[i + 1] == 0)
                {
                    printf("= \t%c\t\tt%d\n", line[i + 1], t);
                    s[i + 1] = t++;
                }

                printf("%c\t", line[i]);

                (s[i - 1] == 0)
                    ? printf("%c\t", line[i - 1])
                    : printf("t%d\t", s[i - 1]);

                printf("t%d \tt%d", s[i + 1], t);

                s[i - 1] = s[i + 1] = t++;
                s[i] = 1;
            }
        }
    }

    for (i = 2; line[i] != '\0'; i++)
    {
        if (line[i] == '+' || line[i] == '-')
        {
            printf("\n");

            if (s[i] == 0)
            {
                if (s[i + 1] == 0)
                {
                    printf("= \t%c\t\tt%d\n", line[i + 1], t);
                    s[i + 1] = t++;
                }

                printf("%c\t", line[i]);

                (s[i - 1] == 0)
                    ? printf("%c\t", line[i - 1])
                    : printf("t%d\t", s[i - 1]);

                printf("t%d \tt%d", s[i + 1], t);

                s[i - 1] = s[i + 1] = t++;
                s[i] = 1;
            }
        }
    }

    printf("\n= \tt%d\t\t%c\n", t - 1, line[0]);
}

void triple()
{
    char g;
    scanf("%c", &g);
    char line[20];
    int s[20];
    int t = 0;
    int i = 0;

    printf("\nEnter Expression: ");
    gets(line);

    for (i = 0; i < 20; i++)
        s[i] = 0;

    // Op -> Operator
    // a1 -> Argument 1
    // a2 -> Argument 2
    // re -> Result
    printf("no\top\ta1\ta2\n");

    for (i = 2; line[i] != '\0'; i++)
    {
        if (line[i] == '/' || line[i] == '*')
        {
            printf("\n");
            if (s[i] == 0)
            {
                if (s[i + 1] == 0)
                {
                    printf("%d \t= \t%c\n", t, line[i + 1], t);
                    s[i + 1] = t++;
                }

                printf("%d \t%c\t", t, line[i]);

                (s[i - 1] == 0)
                    ? printf("%c\t", line[i - 1])
                    : printf("%d\t", s[i - 1]);

                printf("%d", s[i + 1]);

                s[i - 1] = s[i + 1] = t++;
                s[i] = 1;
            }
        }
    }

    for (i = 2; line[i] != '\0'; i++)
    {
        if (line[i] == '+' || line[i] == '-')
        {
            printf("\n");

            if (s[i] == 0)
            {
                if (s[i + 1] == 0)
                {
                    printf("%d \t= \t%c\t%d\n", t, line[i + 1], t);
                    s[i + 1] = t++;
                }

                printf("%d \t%c\t", t, line[i]);

                (s[i - 1] == 0)
                    ? printf("%c\t", line[i - 1])
                    : printf("%d\t", s[i - 1]);

                printf("%d", s[i + 1]);

                s[i - 1] = s[i + 1] = t++;
                s[i] = 1;
            }
        }
    }

    printf("\n%d \t= \t%d\t%c\n", t, t - 1, line[0]);
}

void indirect_triple()
{
    char g;
    scanf("%c", &g);
    char line[20];
    int s[20];
    int t = 100;
    int i = 0;

    printf("\nEnter Expression: ");
    gets(line);

    for (i = 0; i < 20; i++)
        s[i] = 0;

    // Op -> Operator
    // a1 -> Argument 1
    // a2 -> Argument 2
    // re -> Result
    printf("no\top\ta1\ta2\n");

    for (i = 2; line[i] != '\0'; i++)
    {
        if (line[i] == '/' || line[i] == '*')
        {
            printf("\n");
            if (s[i] == 0)
            {
                if (s[i + 1] == 0)
                {
                    printf("%d \t= \t%c\n", t, line[i + 1], t);
                    s[i + 1] = t++;
                }

                printf("%d \t%c\t", t, line[i]);

                (s[i - 1] == 0)
                    ? printf("%c\t", line[i - 1])
                    : printf("%d\t", s[i - 1]);

                printf("%d", s[i + 1]);

                s[i - 1] = s[i + 1] = t++;
                s[i] = 1;
            }
        }
    }

    for (i = 2; line[i] != '\0'; i++)
    {
        if (line[i] == '+' || line[i] == '-')
        {
            printf("\n");

            if (s[i] == 0)
            {
                if (s[i + 1] == 0)
                {
                    printf("%d \t= \t%c\t%d\n", t, line[i + 1], t);
                    s[i + 1] = t++;
                }

                printf("%d \t%c\t", t, line[i]);

                (s[i - 1] == 0)
                    ? printf("%c\t", line[i - 1])
                    : printf("%d\t", s[i - 1]);

                printf("%d", s[i + 1]);

                s[i - 1] = s[i + 1] = t++;
                s[i] = 1;
            }
        }
    }

    printf("\n%d \t= \t%d\t%c\n", t, t - 1, line[0]);

    printf("\nno\tStatement no\n");
    for (i = 0; i <= t - 100; i++)
    {
        printf("%d \t%d\n", i, i + 100);
    }
    cout << "\n";
}

int main()
{
    int choice;
    while (1)
    {
        cout << "\n1. Quadruple\n2. Triple\n3. Indirect Triple\n0. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 0:
            cout << "\nProgram Quit...\n\n";
            return 0;
        case 1:
            quadruple();
            break;
        case 2:
            triple();
            break;
        case 3:
            indirect_triple();
            break;
        default:
            cout << "\nInvalid Choice... Please Try Again\n";
            break;
        }
    }

    return 0;
}