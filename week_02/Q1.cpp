#include<bits/stdc++.h>
using namespace std;

struct symbol
{
    char sym;
    int terminal;//1 if symbol is terminal else 0
    int first_is_set;
    int follow_is_set;
    string first_set;
    string follow_set;
};

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
        for(j=0; j<n1; j++)// to check if B[i] is present in A
        {
            if(B[i]==A[j])
                break;
        }
        if(j==n1)
            res+=B[i];
    }

    if(A[n1-1]=='#' || B[n2-1]=='#')
        res+='#';

    return res;
}

string union_follows(string A, string B)
{
    int n1=A.length(), n2=B.length(), i, j;
    string res="";
    for(i=0; i<n1; i++)
    {
        res+=A[i];
    }

    for(i=0; i<n2; i++)
    {
        for(j=0; j<n1; j++)
        {
            if(B[i]==A[j])
                break;
        }
        if(j==n1)
            res+=B[i];
    }

    return res;
}

string find_first(vector<string> &productions, vector<struct symbol> &symbols, unordered_map<char, int> symbol_to_index, char sym)
{
    int sym_index=symbol_to_index[sym];
    if(symbols[sym_index].first_is_set)
        return symbols[sym_index].first_set;

    int no_p=productions.size();
    int find_for_next, p_len, found_first_len;
    string res="", FF, A, B;
    int res_len, FF_len;
    
    int i, j, k;

    for(i=0; i<no_p; i++)
    {
        if(productions[i][0]==sym)
        {
            res_len=res.length();
            if(productions[i][2]=='#')
            {
                if(res[res_len-1]!='#')
                {
                    res+='#';
                    res_len=res.length();
                }
            }
            else
            {
                j=2;
                find_for_next=1;
                p_len=productions[i].length();
                while(find_for_next && j<p_len)
                {
                    FF=find_first(productions, symbols, symbol_to_index, productions[i][j]);
                    FF_len=FF.length();
                    if(FF[FF_len-1]=='#')
                    {
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

string find_follow(vector<string> &productions, vector<struct symbol> &symbols, unordered_map<char, int> symbol_to_index, char sym, char start_symbol)
{
    int sym_index=symbol_to_index[sym];
    if(symbols[sym_index].follow_is_set)
        return symbols[sym_index].follow_set;

    int no_p=productions.size();
    int find_for_next, p_len, found_first_len;
    string res="", FF, A, B;//FF is found_follow or found_first
    int res_len, FF_len;
    
    int i, j, k;

    for(i=0; i<no_p; i++)
    {
        p_len=productions[i].length();
        for(j=2; j<p_len; j++)
        {
            if(productions[i][j]==sym)
            {
                if(j==p_len-1)
                {
                    if(productions[i][0]!=sym)
                    {
                        FF=find_follow(productions, symbols, symbol_to_index, productions[i][0], start_symbol);
                        res=union_follows(res, FF);
                    }
                }
                else
                {

                    FF=find_first(productions, symbols, symbol_to_index, productions[i][j+1]);
                    FF_len=FF.length();
                    if(FF[FF_len-1]=='#')
                    {
                        B="";
                        for(k=0; k<FF_len-1; k++)
                        {
                            B+=FF[k];
                        }
                        res=union_follows(res, B);
                        FF=find_follow(productions, symbols, symbol_to_index, productions[i][j+1], start_symbol);
                        res=union_follows(res, FF);
                    }
                    else
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

int main()
{
    int no_p, i, j;
    cout<<"Enter the number of productions in the grammar : ";
    cin>>no_p;

    cout<<"\nEnter the productions in each line (in the format A=X..Z and use # for epsilon) :-\n";
    vector<string> productions(no_p);
    for(i=0; i<no_p; i++)
    {
        cin>>productions[i];
    }

    unordered_map<char, int> symbol_to_index;
    vector<struct symbol> symbols;
    struct symbol temp;

    for(i=0; i<no_p; i++)
    {
        temp.sym=productions[i][0];
        temp.terminal=0;
        temp.first_is_set=0;
        temp.follow_is_set=0;
        temp.first_set="";
        temp.follow_set="";
        if(symbol_to_index.find(temp.sym)==symbol_to_index.end())
        {
            symbols.push_back(temp);
            symbol_to_index[temp.sym]=symbols.size()-1;
        }
    }

    for(i=0; i<no_p; i++)
    {
        if(productions[i][2]=='#')
            continue;
        for(j=2; j<productions[i].length(); j++)
        {
            temp.sym=productions[i][j];
            temp.terminal=1;
            temp.first_is_set=1;
            temp.follow_is_set=0;
            temp.first_set=productions[i][j];
            temp.follow_set="";
            if(symbol_to_index.find(temp.sym)==symbol_to_index.end())
            {
                symbols.push_back(temp);
                symbol_to_index[temp.sym]=symbols.size()-1;
            }
        }
    }

    
    int no_symbols=symbols.size();

    for(i=0; i<no_symbols; i++)
    {
        if(symbols[i].first_is_set==0)
        {
            symbols[i].first_set=find_first(productions, symbols, symbol_to_index, symbols[i].sym);
            symbols[i].first_is_set=1;
        }

        //printing FIRST sets of all Non-terminals
        if(symbols[i].terminal==0)
        {
            cout<<"FIRST("<<symbols[i].sym<<")={ ";
            for(j=0; j<symbols[i].first_set.length(); j++)
            {
                cout<<"'"<<symbols[i].first_set[j]<<"'";
                if(j!=symbols[i].first_set.length()-1)
                    cout<<", ";
                else cout<<" ";
            }
            cout<<"}\n";
        }
        
    }

    cout<<"\nEnter the starting symbol of the CFG : ";
    char start_symbol, gb;
    int st_sym_index;
    while(1)
    {
        cin>>start_symbol;
        if(symbol_to_index.find(start_symbol)!=symbol_to_index.end())
            break;
        cout<<"Enter a valid NT symbol as start symbol : ";
    }
    st_sym_index=symbol_to_index[start_symbol];

    for(i=0; i<no_symbols; i++)
    {
        if(symbols[i].terminal==0 && symbols[i].follow_is_set==0)
        {
            symbols[i].follow_set=find_follow(productions, symbols, symbol_to_index, symbols[i].sym, start_symbol);
            symbols[i].follow_is_set=1;
        }

        //printing FOLLOW sets of all non-terminals
        if(symbols[i].terminal==0)
        {
            cout<<"FOLLOW("<<symbols[i].sym<<")={ ";
            for(j=0; j<symbols[i].follow_set.length(); j++)
            {
                cout<<"'"<<symbols[i].follow_set[j]<<"'";
                if(j!=symbols[i].follow_set.length()-1)
                    cout<<", ";
                else cout<<" ";
            }
            cout<<"}\n";
        }

    }

}
