#include<bits/stdc++.h>
using namespace std;

//The struct is a package/stuct containing the symbol and its corresponding details of first set and follow set
//Note:- string is used to represent a FIRST/FOLLOW set of characters
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
string find_first(vector<string> &productions, vector<struct symbol> &symbols, unordered_map<char, int> symbol_to_index, char sym)
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
                    res+='#';
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
                    FF=find_first(productions, symbols, symbol_to_index, productions[i][j]);
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
string find_follow(vector<string> &productions, vector<struct symbol> &symbols, unordered_map<char, int> symbol_to_index, char sym, char start_symbol)
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
                        FF=find_follow(productions, symbols, symbol_to_index, productions[i][0], start_symbol);
                        res=union_follows(res, FF);
                    }
                }
                else//else find FIRST set of the following symbol and union it with the 
                {

                    FF=find_first(productions, symbols, symbol_to_index, productions[i][j+1]);
                    FF_len=FF.length();
                    if(FF[FF_len-1]=='#')//if epsilon is there in the FOLLOW set of the symbol following sym then res=res U {found_FIRST-'#} U {found_FOLLOW}
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

int main()
{
    int no_p, i, j;
    cout<<"Enter the number of productions in the grammar : ";
    cin>>no_p;

    //Inputing all the productions
    cout<<"\nEnter the productions in each line (in the format A=X..Z and use # for epsilon) :-\n";
    vector<string> productions(no_p);
    for(i=0; i<no_p; i++)
    {
        cin>>productions[i];
    }

    unordered_map<char, int> symbol_to_index;//is  the mapping from symbol to the corresponding index in the symbols list
    vector<struct symbol> symbols;//is the list of symbols containing the respective details
    struct symbol temp;//a temporary symbol struc used while push_back ing

    //adding Non-Termnals into symbols list
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

    //adding Terminals into symbols list
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

    //stores number of symbols
    int no_symbols=symbols.size();

    //program section to fill the FIRST set of every Non-Terminal symbol while traversing through the symbols list
    for(i=0; i<no_symbols; i++)
    {
        //Calling find_first function to set/find the FIRST set(string) of each NT symbol
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

    //program section that inputs a valid Start symbol of the CFG
    cout<<"\nEnter the starting symbol of the CFG : ";
    char start_symbol, gb;
    int st_sym_index;
    while(1)
    {
        cin>>start_symbol;
        if(symbol_to_index.find(start_symbol)!=symbol_to_index.end() && symbols[symbol_to_index[start_symbol]].terminal==0)
            break;
        cout<<"Enter a valid NT symbol as start symbol : ";
    }
    st_sym_index=symbol_to_index[start_symbol];

    //program section to fill the FOLLOW set of every Non-Terminal symbol while traversing through the symbols list
    for(i=0; i<no_symbols; i++)
    {
        //Calling find_follow function to set/find the FOLLOW set(string) of each NT symbol
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

    return 1;
}
