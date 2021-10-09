#include <bits/stdc++.h>
using namespace std;

vector<string> productions;
set<char> terminal_set;
set<char> non_terminal_set;
set<char> symbol_set;
string s_compliment = "@";
vector<set<string>> I;
vector<map<char, set<string>>> goto_sets;
vector<vector<string>> parse_table;


vector<struct symbol> symbols;
unordered_map<char, int>symbol_to_index;

struct symbol
{
    char sym;//is the character/symbol of the structure whose details are stored in the struct
    int terminal;//1 if symbol is terminal else 0
    int first_is_set;
    int follow_is_set;
    string first_set;
    string follow_set;
    //remaining elements of the struct explain themselves
};

//function to find union of two FIRST sets(strings) and also makes sure the epislon('#') is at the end in the resultant set(string)
string union_firsts(string A, string B)
{
    string res="";
    int n1=A.length(), n2=B.length(), i, j;
    for(i=0; i<n1; i++)//copying all non-epsilon characters of A to res
    {
        if(A[i]!='#')
            res+=A[i];
    }

    for(i=0; i<n2; i++)
    {
        if(B[i]=='#')
            continue;
        for(j=0; j<n1; j++)//loop to check if B[i] is present in set(string) A
        {
            if(B[i]==A[j])
                break;
        }
        if(j==n1)
            res+=B[i];
    }

    //if epsilon('#') exists in either sets then add it at the end
    if(A[n1-1]=='#' || B[n2-1]=='#')
        res+='#';

    return res;
}

//function to find union of two FOLLOW sets(stings)
string union_follows(string A, string B)
{
    int n1=A.length(), n2=B.length(), i, j;
    string res="";//res is the resultant set of union of A and B
    for(i=0; i<n1; i++)//copying all characters of A to res
    {
        res+=A[i];
    }

    //for each character in B as B[i] not in res it adds B[i] to res
    for(i=0; i<n2; i++)
    {
        for(j=0; j<n1; j++)//loop to check if B[i] is in  set(string) A
        {
            if(B[i]==A[j])
                break;
        }
        if(j==n1)
            res+=B[i];
    }

    return res;
}

//function that returns the FIRST set(string) of the parameter symbol sym(NT or T)
string find_first(char sym)
{
    //if epsilon is the symbol then it itself will be the FIRST set
    if(sym=='#')
        return "#";

    //if FIRST set is already set then return directly 
    int sym_index=symbol_to_index[sym];
    if(symbols[sym_index].first_is_set)
        return symbols[sym_index].first_set;


    int no_p=productions.size();
    //find_for_next is flag to store whether or not FIRST set of next symbol is to be found based on whether the FIRST set of previous symbol has NULL or not
    //p_len is the length of the production string
    int find_for_next, p_len;
    //res is the FIRST set of the symbol sym that is being computed
    //FF is short for found FIRST of some symbol during the computaion
    //A and B are temporary strings used during computation
    string res="", FF, A, B;
    int res_len, FF_len;
    
    int i, j, k;

    for(i=0; i<no_p; i++)
    {
        //if the productions[i] is the expansion for sym
        if(productions[i][0]==sym)
        {
            res_len=res.length();
            if(productions[i][2]=='#')//if productions expands to a epsilon
            {
                if(res[res_len-1]!='#')
                {
                    res=union_firsts(res, "#");
                    res_len=res.length();
                }
            }
            else
            {
                j=2;
                find_for_next=1;
                p_len=productions[i].length();
                while(find_for_next && j<p_len)//keep unioning first set of each symbol until we find a first set without an epsilon
                {
                    FF=find_first(productions[i][j]);
                    FF_len=FF.length();
                    if(FF[FF_len-1]=='#')//if epsilon is there in the FF set
                    {
                        //copying non-epsilon symbols from FF to B and unit it with res
                        B="";
                        for(k=0; k<FF_len-1; k++)
                        {
                            B+=FF[k];
                        }
                        res=union_firsts(res, B);
                    }
                    else
                    {
                        res=union_firsts(res, FF);
                        find_for_next=0;
                        break;
                    }

                    j++;
                }

                //even if at the end of production there is no non-epsilon containing first set the add epsilon to the first set of the FIRST set of sym
                if(j==p_len && find_for_next)
                {
                    res=union_firsts(res, "#");
                }

            }
        }
    }

    symbols[sym_index].first_set=res;
    symbols[sym_index].first_is_set=1;

    return res;
}

//function that returns the FOLLOW set(string) of the parameter symbol sym(NT or T)
string find_follow(char sym, char start_symbol)
{
    //if FIRST set is already set then return directly 
    int sym_index=symbol_to_index[sym];
    if(symbols[sym_index].follow_is_set)
        return symbols[sym_index].follow_set;

    int no_p=productions.size();
    //p_len is the length of the production string
    int p_len;
    //res is the FOLLOW set of the symbol sym that is being computed
    //FF is short for found FIRST/FOLLOW of some symbol during the computaion
    //A and B are temporary strings used during computation
    string res="", FF, A, B;
    int res_len, FF_len;
    
    int i, j, k;

    for(i=0; i<no_p; i++)
    {
        p_len=productions[i].length();
        for(j=2; j<p_len; j++)
        {
            if(productions[i][j]==sym)//if sym is found on the right hand side of a production
            {
                if(j==p_len-1)//if sym is the last symbol in the production then find the follow of left hand symbol of the production and union it to the FOLLOW set of sym
                {
                    if(productions[i][0]!=sym)
                    {
                        FF=find_follow(productions[i][0], start_symbol);
                        res=union_follows(res, FF);
                    }
                }
                else//else find FIRST set of the following symbol and union it with the 
                {

                    FF=find_first(productions[i][j+1]);
                    FF_len=FF.length();
                    if(FF[FF_len-1]=='#')//if epsilon is there in the FOLLOW set of the symbol following sym then res=res U {found_FIRST-'#} U {found_FOLLOW}
                    {
                        B="";
                        for(k=0; k<FF_len-1; k++)
                        {
                            B+=FF[k];
                        }
                        res=union_follows(res, B);
                        FF=find_follow(productions[i][j+1], start_symbol);
                        res=union_follows(res, FF);
                    }
                    else //else just res=res U found_FIRST
                    {
                        res=union_follows(res, FF);
                    }
                }
            }
        }
    }

    if(sym==start_symbol)
        res+="$";

    symbols[sym_index].follow_set=res;
    symbols[sym_index].follow_is_set=1;

    return res;
}

bool isNonTerminal(char x)
{
    if ('A' <= x && x <= 'Z')
        return true;
    return false;
}

void print_productions()
{
    for (int i = 0; i < productions.size(); i++)
    {
        cout << i << ": " << productions[i] << endl;
    }
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

void print_parse_table()
{
    set<char> s = symbol_set;
    s.insert('$');
    cout << "  ";
    for (auto m = s.begin(); m != s.end(); m++)
        cout << "  " << *m;
    cout << endl;
    for (int i = 0; i < parse_table.size(); i++)
    {
        cout << "I" << i << " ";
        for (int j = 0; j < parse_table[i].size(); j++)
        {
            cout << parse_table[i][j] << " ";
        }
        cout << "\n";
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

int find_prod_in_I(string p)
{
    for (int i = 0; i < I.size(); i++)
    {
        if (I[i].count(p))
            return i;
    }
    return -1;
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
                    if (find_prod_in_I(temp) != -1)
                        break;
                    s.insert(temp);
                    break;
                }
            }
        }
        if (!s.empty())
        {
            I.push_back(s);
            calculate_closure(I[I.size() - 1]);
        }
    }
}

int is_in(string A, char B)
{
    int n=A.length();
    int i;
    for(i=0; i<n; i++)
    {
        if(B==A[i])
            return 1;
    }

    return 0;
}

void calculate_parse_table()
{
    set<char> s = symbol_set;
    s.insert('$');
    // vector<vector<string>> parse_table(I.size(), vector<string>(s.size(), "--"));
    parse_table.resize(I.size(), vector<string>(s.size(), "--"));
    string temp;
    int index;
    int j = 0;
    for (int i = 0; i < I.size(); i++)
    {
        j = 0;
        for (auto j2 = s.begin(); j < s.size() && j2 != s.end(); j++, j2++)
        {
            for (auto p = I[i].begin(); p != I[i].end(); p++)
            {
                temp = *p;
                index = -1;
                if (temp[temp.size() - 1] == '.')
                {
                    string pqr = temp.substr(0, temp.size() - 1);
                    // string pqr = temp;
                    if (pqr == productions[0])
                    {
                        if (*j2 == '$')
                            parse_table[i][j] = "@";
                        break;
                    }
                    for (int xyz = 0; xyz < productions.size(); xyz++)
                    {
                        if (pqr == productions[xyz] && !isNonTerminal(*j2))
                        {
                            string follow_set=find_follow(productions[xyz][0], '@');
                            if(is_in(follow_set, *j2))
                            {
                                parse_table[i][j] = "R" + to_string(xyz);
                                break;
                            }
                        }
                    }
                    continue;
                }
                else
                {
                    for (int k = 2; k < temp.size() - 1; k++)
                    {
                        if (temp[k] == '.' && temp[k + 1] == *j2)
                        {
                            swap(temp[k], temp[k + 1]);
                            index = find_prod_in_I(temp);
                            if (isNonTerminal(*j2))
                            {
                                parse_table[i][j] = "I" + to_string(index);
                            }
                            else
                            {
                                parse_table[i][j] = "S" + to_string(index);
                            }
                            break;
                        }
                    }
                }
            }
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
    for (int i = 0; i < I.size(); i++)
    {
        calculate_goto(i);
    }

    struct symbol temp;
    for(auto j=symbol_set.begin(); j!=symbol_set.end(); j++)
    {
        temp.sym=*j;
        if(('A'<=temp.sym && temp.sym<='Z') || temp.sym=='@')
            temp.terminal=0;
        else    temp.terminal=1;
        temp.first_set="";
        temp.follow_set="";
        temp.first_is_set=0;
        temp.follow_is_set=0;
        symbols.push_back(temp);
        symbol_to_index[*j]=symbols.size()-1;
    }

    calculate_parse_table();

    cout << "Productions" << endl;
    print_productions();
    cout << "\nAugment Grammar and Sets\n"
         << endl;
    print_sets();
    cout << "Parse Table\n"
         << endl;
    print_parse_table();

    return 0;
}
