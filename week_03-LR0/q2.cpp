#include <bits/stdc++.h>
using namespace std;

vector<string> productions;
set<char> terminal_set;
set<char> non_terminal_set;
set<char> symbol_set;
string s_compliment = "@";
vector<set<string>> I;
vector<map<char, set<string>>> goto_sets;

bool isNonTerminal(char x)
{
    if ('A' <= x && x <= 'Z')
        return true;
    return false;
}

void print_sets()
{
    for (int i = 0; i < I.size(); i++)
    {
        cout << "I" << i << endl;
        for (auto j = I[i].begin(); j != I[i].end(); j++)
        {
            cout << *j << endl;
        }
        cout << endl;
    }
}

void extract_terminals_nonTerminals()
{
    int i, j;
    for (i = 0; i < productions.size(); i++)
    {
        for (j = 0; j < productions[i].size(); j++)
        {
            if (productions[i][j] == '=')
                continue;
            if (isNonTerminal(productions[i][j]))
                non_terminal_set.insert(productions[i][j]);
            else
                terminal_set.insert(productions[i][j]);
            symbol_set.insert(productions[i][j]);
        }
    }
}

/// The Productions are copied from the input file to a vector of Strings
/// Format of Input file:
/// 1. First Line should cotain number of Productions (say N)
/// 2. The next N lines should contain productions in the form S=aA (No space in between any character)
/// 3. Avoid Productions of Format S = aA | a
void copy_productions_from_file()
{
    int num_productions;
    string text_in_file;
    ifstream InputFile("input.txt");
    getline(InputFile, text_in_file);
    num_productions = stoi(text_in_file);
    for (int i = 0; i < num_productions; i++)
    {
        getline(InputFile, text_in_file);
        productions.push_back(text_in_file);
    }
}

void insert_initial_grammar()
{
    string s = productions[0];
    string augment_product = s_compliment + "=";
    augment_product.append(s);
    augment_product = augment_product.substr(0, 3);
    productions.insert(productions.begin(), augment_product);
}

void calculate_closure(set<string> &s)
{
    string temp, temp_prod;
    bool flag = true;
    auto p = s.begin();
    while (p != s.end())
    {
        temp = *p;
        for (int i = 2; i < temp.size() - 1; i++)
        {
            if (temp[i] == '.' && isNonTerminal(temp[i + 1]))
            {
                for (int j = 0; j < productions.size(); j++)
                {
                    if (productions[j][0] == temp[i + 1])
                    {
                        temp_prod = productions[j];
                        temp_prod.insert(temp_prod.begin() + 2, 1, '.');
                        if (s.count(temp_prod) == 0)
                        {
                            s.insert(temp_prod);
                            p = s.begin();
                            flag = false;
                        }
                        else
                        {
                            flag = true;
                        }
                    }
                }
            }
        }
        if (flag)
            p++;
        flag = true;
    }
}

void insert_augment_grammar()
{
    // Add . to first Production (Augment Grammar)
    string aug_prod = productions[0];
    aug_prod.insert(aug_prod.begin() + 2, 1, '.');
    set<string> s;
    s.insert(aug_prod);
    I.push_back(s);
    calculate_closure(I[0]);
}

bool find_prod_in_I(string p) {
    for(int i=0; i<I.size(); i++) {
        if (I[i].count(p)) return true;
    }
    return false;
}

void calculate_goto(int index)
{
    set<string> s;
    string temp;
    int i = 0;
    for (auto c = symbol_set.begin(); c != symbol_set.end(); c++)
    {
        s.clear();
        for (auto p = I[index].begin(); p != I[index].end(); p++)
        {
            temp = *p;
            for (i = 2; i < temp.size() - 1; i++)
            {
                if (temp[i] == '.' && temp[i + 1] == *c)
                {
                    swap(temp[i], temp[i + 1]);
                    //TODO: Search in all other sets of I
                    if (find_prod_in_I(temp)) break ;
                    s.insert(temp);
                    break ;
                }
            }
        }
        if (!s.empty())
        {
            I.push_back(s);
            calculate_closure(I[I.size()-1]);
        }
    }


}

int main()
{
    copy_productions_from_file();
    extract_terminals_nonTerminals();
    insert_initial_grammar();
    insert_augment_grammar();

    // calculate goto for all Sets
    for(int i=0; i<I.size(); i++) {
        calculate_goto(i);
    }
    print_sets();
    return 0;
}