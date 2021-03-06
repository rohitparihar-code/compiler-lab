// Program to convert Intermediate code to Machine-Level-Code/Assembly Code

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int ch;
    string s1, s2, s3, s4, output;
    while (1)
    {
        cout << "1. Generate machine code\n0. Exit Program\nEnter your choice: ";
        cin >> ch;
        if (ch == 1)
        {
            cout << "\nEnter the quadraple form of three-address code : ";
            cin >> s1 >> s2 >> s3 >> s4;
            cout << "\nMachine code : ";
            //cout<<s1<<"|"<<s2<<"|"<<s3<<"|"<<s4<<"\n";
            if (s1 == "+")
            {
                if (s3 != "NULL")
                    cout << "ADD " << s4 << ", " << s2 << ", " << s3 << "\n";
                else
                    cout << "ADD " << s4 << ", " << 0 << ", " << s2 << "\n";
            }
            else if (s1 == "-")
            {
                if (s3 != "NULL")
                    cout << "SUB " << s4 << ", " << s2 << ", " << s3 << "\n";
                else
                    cout << "SUB " << s4 << ", " << 0 << ", " << s2 << "\n";
            }
            else if (s1 == "*")
                cout << "MUL " << s4 << ", " << s2 << ", " << s3 << "\n";
            else if (s1 == "/")
                cout << "DIV " << s4 << ", " << s2 << ", " << s3 << "\n";
            else if (s1 == "=")
                cout << "ADD " << s4 << ", " << s2 << ", " << 0 << "\n";
        }
        else
            break;
        cout << "\n";
    }

    cout << "\nExiting Program...\n\n";
}