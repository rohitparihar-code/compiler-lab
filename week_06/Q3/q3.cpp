// Program to implement Type Checking

#include <bits/stdc++.h>
using namespace std;

struct symbol_table
{
    int type;
    char var[10];
} st[50];

int c = 0;

void sep(string s)
{
    int l = s.length();
    int i, j = 0;
    char temp[50];
    string tp;
    for (i = 0; i < l && s[i] != ' '; ++i)
    {
        tp.push_back(s[i]);
    }
    temp[0] = '\0';
    ++i;
    for (; i < l; ++i)
    {
        if (s[i] != ',' && s[i] != ' ' && s[i] != ';')
            temp[j++] = s[i];
        else
        {
            if (tp == "int")
                st[c].type = 1;
            else if (tp == "float")
                st[c].type = 2;
            strcpy(st[c++].var, temp);
            temp[0] = '\0';
            j = 0;
        }
    }
}
int check(char a[])
{
    int len = strlen(a);
    int i, j = 0, key = 0, k;
    char temp[50];
    for (i = 0; i < len; ++i)
    {
        if (a[i] != 32 && a[i] != '+' && a[i] != '=' && a[i] != ';')
            temp[j++] = a[i];
        else
        {
            temp[j] = '\0';
            for (k = 0; k < c; ++k)
            {
                if (strcmp(st[k].var, temp) == 0)
                {
                    if (key == 0)
                        key = st[k].type;
                    else if (st[k].type != key)
                        return 0;
                }
            }
            j = 0;
        }
    }
    return 1;
}
int main()
{
    int n, ans, i;
    char s[50];
    printf("\nEnter the total lines of declaration (Ex: int a, b, c; is one line of declaration): ");
    scanf("%d", &n);
    cout << "Enter the declarations\n";
    i = 0;
    while (n--)
    {
        cout << i + 1 << ": ";
        scanf(" %[^\n]", s);
        sep(s);
        i++;
    }

    int choice;
    while (1)
    {
        cout << "\n0. Exit\n1. Check Expressions\nEnter your choice : ";
        cin >> choice;
        if (choice != 1)
        {
            cout << "\n";
            break;
        }

        cout << "\nEnter the expression: ";
        scanf(" %[^\n]", s);

        cout << "Result: ";
        if (check(s))
            {
                cout << "No Errors Found\n\n";
            }
        else
            {
                cout << "Semantic Error Will Occur\n\n";
            }
        
    }

    return 0;
}