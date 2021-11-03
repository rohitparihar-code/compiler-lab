// Program to implement Type Checking

#include <bits/stdc++.h>
using namespace std;

struct symbol_table
{
    int type;
    char var[10];
} st[50];
// Type 1: int
// Type 2: float
// Type 3: char

int c = 0;

void extract(string s)
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
            else if (tp == "char")
                st[c].type = 3;
            strcpy(st[c++].var, temp);
            temp[0] = '\0';
            j = 0;
        }
    }
}

map<string, map<string, int>> c_pairs;

bool check(char a[])
{
    int len = strlen(a);
    int i, j = 0, key = 0, k;
    char temp[50];
    string prev = "";
    for (i = 0; i < len; ++i)
    {
        if (a[i] != ' ' && a[i] != '+' && a[i] != '=' && a[i] != ';' && a[i] != '*' && a[i] != '%' && a[i] != '/')
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
                        return false;
                }
            }
            j = 0;
        }
    }
    return true;
}

int main()
{
    int n, i;
    char s[50];
    printf("\nEnter the total lines of declaration (Ex: int a, b, c; is one line of declaration): ");
    scanf("%d", &n);
    cout << "Enter the declarations\n";
    i = 0;
    while (n--)
    {
        cout << i + 1 << ": ";
        scanf(" %[^\n]", s);
        extract(s);
        i++;
    }

    {
        c_pairs["int"]["float"] = 1;
        c_pairs["float"]["int"] = 1;
        c_pairs["double"]["float"] = 1;
        c_pairs["double"]["int"] = 1;
        c_pairs["float"]["double"] = 1;
        c_pairs["int"]["double"] = 1;
        c_pairs["string"]["string"] = 1;
        c_pairs[""]["int"] = 1;
        c_pairs[""]["float"] = 1;
        c_pairs[""]["double"] = 1;
        c_pairs[""]["string"] = 1;
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