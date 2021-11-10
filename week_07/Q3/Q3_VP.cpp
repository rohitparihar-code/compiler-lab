// Program to implement Variable Propagation

#include <bits/stdc++.h>

using namespace std;

int searchVectorPair(vector<pair<char, string>> &exp, char key, int index)
{
    for (int i = 0; i < index; i++)
    {
        if (key == exp[i].first)
        {
            return i;
        }
    }

    return -1;
}

int main()
{
    int n;
    cout << "\nEnter the number of expressions: ";
    cin >> n;

    // map<char, string> exp;
    vector<pair<char, string>> exp;

    char lhs, g;
    string rhs;
    cout << "\nEnter the Expressions\n";
    for (int i = 0; i < n; i++)
    {
        printf("Expression %d: ", i + 1);
        scanf("%c%c%c", &g, &lhs, &g);
        cin >> rhs;
        exp.push_back(make_pair(lhs, rhs));
    }

    for (auto i = 0; i < exp.size(); i++)
    {
        lhs = exp[i].first;
        rhs = exp[i].second;
        for (int j = 0; j < rhs.length(); j++)
        {
            int p = searchVectorPair(exp, rhs[j], i);
            if (p != -1)
            {
                for (int k = 0; k < exp[p].second.length(); k++)
                {
                    rhs.insert(rhs.begin() + j + 1 + k, exp[p].second[k]);
                }
                cout << rhs << "\n";
                rhs.erase(rhs.begin() + j);
            }
        }
        exp[i].second = rhs;
    }

    cout << endl;
    for (auto i = exp.begin(); i != exp.end(); i++)
    {
        cout << i->first << "=" << i->second << "\n";
    }

    return 0;
}