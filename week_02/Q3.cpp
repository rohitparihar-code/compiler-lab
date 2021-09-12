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

//function that returns the first_set of the right hand side of a production
string find_exp_first(vector<string> &productions, vector<struct symbol> &symbols, unordered_map<char, int> symbol_to_index, int p_no)
{
    //meaning of all variables are similar to what it is in the find_first function
    int p_len=productions[p_no].length();
    int i, j, k, find_for_next;
    string res="", FF, A, B;
    int FF_len;

    //The computation is similar to computation for each production in the find_first function
    i=2;
    find_for_next=1;
    while(i<p_len && find_for_next)
    {
        FF=find_first(productions, symbols, symbol_to_index, productions[p_no][i]);
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

        i++;
    }
    
    if(i==p_len && find_for_next)
    {
        res=union_firsts(res, "#");
    }

    return res;
}

int check_string(vector<string> &productions, vector<struct symbol> &symbols, unordered_map<char, int> symbol_to_index, vector<vector<int>> &parse_table, char start_symbol, string input)
{
    cout<<"The productions used while checking acceptance of string:-\n";
    
    //Initializing parse stack and pushing '$' and start symbol
    stack<char> parse_stack;
    parse_stack.push('$');
    parse_stack.push(start_symbol);

    int len=input.length();
    //i is used to iterate over the input string
    //top_sym_index is the index of the topmost symbol of the stack
    int i=0, j, top_sym_index;
    //r and c will be the index of the parse table that we are going to access
    int r, c;
    //p_no is production number and p_len is production length.
    int p_no, p_len;
    char top_sym, next;

    while(parse_stack.empty()==0 && i<len)
    {
        top_sym=parse_stack.top();
        if(symbol_to_index.find(top_sym)==symbol_to_index.end())
        {
            cout<<top_sym<<"\n"<<"The string \""<<input<<"\" dosen't belong to the given grammar.\n";
            return 0;
        }

        top_sym_index=symbol_to_index[top_sym];
        next=input[i];
        //cout<<"top_symbol='"<<top_sym<<"' next_symbol='"<<next<<"'\n";
        
        if(symbols[top_sym_index].terminal==1)//if top symbol of stack is a terminal symbol
        {
            if(top_sym==next)
            {
                parse_stack.pop();//popping the top terminal symbol from stack
                i++;//pointing to next input symbol
            }
            else
            {
                cout<<"The string \""<<input<<"\" dosen't belong to the given grammar.\n";
                return 0;
            }
        }
        else if(symbols[top_sym_index].terminal==0)// else if top symbol is a NT symbol find appropriate production using parse table and expand top symbol
        {
            r=top_sym_index;
            c=symbol_to_index[next];
            if(parse_table[r][c]!=-1)
            {
                p_no=parse_table[r][c];
                p_len=productions[p_no].length();
                
                parse_stack.pop();
                cout<<productions[p_no]<<"\n";

                //pushing symbols of productions[p_no] from back to front onto parse stack
                for(j=p_len-1; j>1; j--)
                {
                    if(productions[p_no][j]!='#')
                        parse_stack.push(productions[p_no][j]);
                }

            }
            else
            {
                cout<<"The string \""<<input<<"\" dosen't belong to the given grammar.\n";
                return 0;
            }
        }
    }

    if(parse_stack.empty() && i==len)
    {
        cout<<"The string \""<<input<<"\" belongs to the given grammar.\n";
        return 1;
    }

    cout<<"The string \""<<input<<"\" dosen't belong to the given grammar.\n";
    return 0;
}

int main()
{
    int no_p, i, j, k;
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

    cout<<"\n";
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

    //inserting $ as terminal symbol in symbols list
    temp.sym='$';
    temp.terminal=1;
    temp.first_is_set=1;
    temp.follow_is_set=1;
    temp.first_set="$";
    temp.follow_set="";
    symbols.push_back(temp);
    symbol_to_index['$']=symbols.size()-1;
    no_symbols=symbols.size();

    //Initializing the Parse table with -1 as all entries initially
    vector<vector<int>> parse_table(no_symbols, vector<int>(no_symbols, -1));

    int r, c, p_len, FF_len;
    string FF;

    //program section to fill the parse table
    for(i=0; i<no_p; i++)//outer loop iterates over each production and fills the corresponding production symbol row
    {
        r=symbol_to_index[productions[i][0]];
        FF=find_exp_first(productions, symbols, symbol_to_index, i);
        FF_len=FF.length();
        //Assume production is A->a
        if(FF[FF_len-1]=='#')//if(FIRST(a) has epsilon('#')) then for each x in {FIRST(a)-'#' U FOLLOW(A)} fill T[A][x]=A->a or T[A][x]=i
        {
            for(j=0; j<FF_len-1; j++)//filling T[A][x] for each x in {FIRST(a)-'#'}
            {
                c=symbol_to_index[FF[j]];
                parse_table[r][c]=i;
            }

            FF=find_follow(productions, symbols, symbol_to_index, productions[i][0], start_symbol);
            FF_len=FF.length();
            for(j=0; j<FF_len; j++)//filling T[A][x] for each x in {FOLLOW(A)}
            {
                c=symbol_to_index[FF[j]];
                parse_table[r][c]=i;
            }

        }
        else// else for each x in {FIRST(a)} fill T[A][x]=A->a
        {
            for(j=0; j<FF_len; j++)//filling T[A][x] for each x in {FIRST(a)}
            {
                c=symbol_to_index[FF[j]];
                parse_table[r][c]=i;
            }
        }
    }

    //Printing the Parse Table
    cout<<"\nParse Table :- \n";
    cout<<"    ";
    for(i=0; i<no_symbols; i++)
    {
        if(symbols[i].terminal==1)
            cout<<setw(4)<<symbols[i].sym;
    }
    cout<<"\n";
    for(i=0; i<no_symbols; i++)
    {
        if(symbols[i].terminal==0)
        {
            cout<<setw(4)<<symbols[i].sym;
            for(j=0; j<no_symbols; j++)
            {
                if(symbols[j].terminal)
                {
                    cout<<setw(4)<<parse_table[i][j]+1;
                }
            }
            cout<<"\n";
        }
    }

    cout<<"\n\nNow you can enter strings and check whether they belong to the given Grammar.\n\n";

    //Parsing Algorithm to check if an input string belongs to a the given Grammar
    int choice;
    string input_string;
    int inp_len;
    while(1)
    {
        cout<<"Enter 1.to check if string belongs to grammar 0.Exit : ";
        cin>>choice;
        if(choice==1)
        {
            cout<<"Enter the string to be checked : ";
            cin>>input_string;
            inp_len=input_string.length();
            if(input_string[inp_len-1]!='$')
            {
                input_string+='$';
            }
            check_string(productions, symbols, symbol_to_index, parse_table, start_symbol, input_string);
            cout<<"\n";
        }
        else
            break;
    }


    cout<<"\n";

    return 1;
}
