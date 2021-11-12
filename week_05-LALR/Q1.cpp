#include<bits/stdc++.h>
using namespace std;

struct symbol
{
    char sym;//is the character/symbol of the structure whose details are stored in the struct
    int terminal;//1 if symbol is terminal else 0
    int first_is_set;
    //int follow_is_set;
    string first_set;
    //string follow_set;
    //remaining elements of the struct explain themselves
};

struct item
{
    string aug_prod;//It is the augmented production
    int p_no;//It is the production number of the augmented production
    string look_ahead; //each character in the string is a lookahead symbol of the item

    // This function is used by set to order
    // elements of Test.
    bool operator<(const item &t) const
    {
        if(this->p_no< t.p_no)
            return true;
        if(this->p_no==t.p_no && this->aug_prod.compare(t.aug_prod)<0)
            return true;
        return false;
    }

};

int compare_string_sets(string A, string B)
{
    if(A.length()!=B.length())
        return 0;

    int n=A.length(), i, j;
    int flag=0;
    for(i=0;i<n; i++)
    {
        flag=0;
        for(j=0; j<n; j++)
        {
            if(A[i]==B[j])
            {
                flag=1;
                break;
            }
        }

        if(flag==0)
            return 0;
    }

    return 1;
}

int search_set(set<struct item> S, struct item I)
{
    for(auto itr=S.begin(); itr!=S.end(); itr++)
    {
        if(itr->aug_prod==I.aug_prod && compare_string_sets(itr->look_ahead, I.look_ahead))
            return 1;
    }
    return 0;
}


// A hash function used to hash a pair of any kind
//This is to create unordered_map<pair<int, char>> goto_list
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

vector<string> productions;//productions of grammar
vector<struct symbol> symbols;//symbol table
unordered_map<char , int> symbol_to_index;//map from symbol to corresponding index in symbol table

vector<set<struct item>> collection;
unordered_map<pair<int, int>, int, hash_pair> goto_list;
vector<vector<pair<char, int>>> parse_table(100, vector<pair<char, int>>(100, {'-', -1}));

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

//function that returns the first_set of the input string
string find_exp_first(string prod)
{
    if(prod=="")
        return "#";

    //meaning of all variables are similar to what it is in the find_first function
    int p_len=prod.length();
    int i, j, k, find_for_next;
    string res="", FF, A, B;
    int FF_len;

    //The computation is similar to computation for each production in the find_first function
    i=0;
    find_for_next=1;
    while(i<p_len && find_for_next)
    {
        FF=find_first(prod[i]);
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

//returns the closure of the item set according the grammar
set<struct item> find_closure(set<struct item> I)
{
    int no_items=I.size();

    int i, j, k;
    int p_len;
    struct item pres_item;
    struct item new_item;
    string new_item_aug_prod, new_item_look_ahead;

    char next, next_next;
    int next_index, next_next_index;

    auto itr=I.begin();
    //outer loop to iterate over each item in the set
    while(itr!=I.end())
    {
        pres_item=*itr;
        p_len=pres_item.aug_prod.length();
        if(pres_item.aug_prod[p_len-1]=='.')//if dot is at the end of the augmented production
        {
            itr++;
            continue;
        }

        //first for loop to find the dot in the present augmented production
        for(i=2; i<p_len; i++)
        {
            if(pres_item.aug_prod[i]=='.')//when you find the dot in the augmented production
            {
                next=pres_item.aug_prod[i+1];
                next_index=symbol_to_index[next];
                if(symbols[next_index].terminal)//if symbol after the dot is a termianal go to next item in set.
                {
                    itr++;
                }
                else//else then find all the production starting from next_symbol and add its audgmented form's item into the set
                {
                    //calculate the lookahead of all the new_items(if added) for the present item's derivative.
                    new_item_look_ahead=pres_item.aug_prod.substr(i+2, p_len);
                    new_item_look_ahead=find_exp_first(new_item_look_ahead);
                    int len=new_item_look_ahead.length();
                    if(new_item_look_ahead[len-1]=='#')
                    {
                        new_item_look_ahead=union_firsts(new_item_look_ahead, pres_item.look_ahead);
                        len=new_item_look_ahead.length();
                        new_item_look_ahead=new_item_look_ahead.substr(0, len-1);
                    }

                    for(j=0; j<productions.size(); j++)//loop over all the original producitons to find the production starting with the next_symbol
                    {
                        if(next==productions[j][0])
                        {
                            if(productions[j][2]=='#')
                            {
                                new_item.aug_prod=productions[j];
                                new_item.aug_prod[2]='.';
                                new_item.p_no=j;
                            }
                            else
                            {
                                new_item.aug_prod=productions[j];
                                new_item.aug_prod=new_item.aug_prod.insert(2, ".");
                                new_item.p_no=j;
                            }
                            new_item.look_ahead=new_item_look_ahead;

                            I.insert(new_item);
                        }
                    }

                    if(no_items!=I.size())
                    {
                        no_items=I.size();
                        itr=I.begin();
                    }
                    else
                    {
                        itr++;
                    }

                }

                break;
            }
        }
    }

    return I;
}

set<struct item> find_goto(int col_ind, int sym_ind)
{
    set<struct item> res;
    
    struct item pres_item, new_item;
    int p_len;

    auto itr=collection[col_ind].begin();

    int i, j;
    while(itr!=collection[col_ind].end())
    {
        pres_item=*itr;
        p_len=pres_item.aug_prod.length();
        if(pres_item.aug_prod[p_len-1]=='.')//if dot is at the end of the augmented production
        {
            itr++;
            continue;
        }

        for(i=2; i<p_len; i++)
        {
            if(pres_item.aug_prod[i]=='.')
            {
                if(pres_item.aug_prod[i+1]==symbols[sym_ind].sym)
                {
                    new_item.aug_prod=productions[pres_item.p_no];
                    new_item.aug_prod.insert(i+1,".");
                    new_item.p_no=pres_item.p_no;
                    new_item.look_ahead=pres_item.look_ahead;
                    res.insert(new_item);
                    itr++;
                }
                else
                {
                    itr++;
                }
                break;
            }
        }

    }

    res=find_closure(res);

    return res;
}

int compare_sets(set<struct item> A, set<struct item> B)
{
    if(A.size()!=B.size())
        return 0;
    
    auto itr1=A.begin(), itr2=B.begin();

    while(itr1!=A.end())
    {
        if(itr1->aug_prod!=itr2->aug_prod)
            return 0;
        itr1++;
        itr2++;
    }

    return 1;
}

set<struct item> merge_sets(set<struct item> A, set<struct item> B)
{
    auto itr1=A.begin(), itr2=B.begin();
    set<struct item> res;
    struct item new_item;

    while(itr1!=A.end() || itr2!=B.end())
    {
        new_item.aug_prod=itr1->aug_prod;
        new_item.p_no=itr1->p_no;
        new_item.look_ahead=union_firsts(itr1->look_ahead, itr2->look_ahead);
        res.insert(new_item);
        itr1++;
        itr2++;
    }

    return res;
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

    //Add initail production S'->S as @=S or instead of S whtever productions[0][0] is
    string initial_prod = "@=";
    initial_prod+=productions[0][0];
    productions.insert(productions.begin(), initial_prod);

}

//function to insert symbols into symbol table
void insert_symbols()
{
    int no_p=productions.size();
    int i, j;
    struct symbol temp;

    //adding Non-Termnals into symbols list
    for(i=0; i<no_p; i++)
    {
        temp.sym=productions[i][0];
        temp.terminal=0;
        temp.first_is_set=0;
        temp.first_set="";
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
            temp.first_set=productions[i][j];
            if(symbol_to_index.find(temp.sym)==symbol_to_index.end())
            {
                symbols.push_back(temp);
                symbol_to_index[temp.sym]=symbols.size()-1;
            }
        }
    }

    temp.sym='$';
    temp.first_is_set=1;
    temp.first_set="$";
    temp.terminal=1;
    symbols.push_back(temp);
    symbol_to_index[temp.sym]=symbols.size()-1;
    
}

//function to fill the FIRST sets of all the symbols
void fill_firsts()
{
    int i;
    int no_symbols=symbols.size();
    for(i=0; i<no_symbols; i++)
    {
        //Calling find_first function to set/find the FIRST set(string) of each NT symbol
        if(symbols[i].first_is_set==0)
        {
            symbols[i].first_set=find_first(symbols[i].sym);
            symbols[i].first_is_set=1;
        }
    }
}

void make_collection()
{
    //First we find the items in the starting state and add the set into the collection vector list
    set<struct item> starting_state;
    struct item temp;
    temp.aug_prod="@=.S";
    temp.p_no=0;
    temp.look_ahead="$";
    starting_state.insert(temp);
    starting_state=find_closure(starting_state);
    collection.push_back(starting_state);

    int i, j, k;
    set<struct item> goto_set;

    for(i=0; i<collection.size(); i++)
    {
        for(j=0; j<symbols.size(); j++)
        {
            goto_set = find_goto(i, j);
            if(goto_set.size()>0)
            {
                for(k=0; k<collection.size(); k++)
                {
                    if(compare_sets(collection[k], goto_set))
                    {
                        collection[k]=merge_sets(collection[k], goto_set);
                        if(symbols[j].terminal)
                            parse_table[i][j]={'S', k};
                        else
                            parse_table[i][j]={'I', k};
                        break;
                    }
                }

                if(k==collection.size())
                {
                    if(symbols[j].terminal)
                        parse_table[i][j]={'S', k};
                    else
                        parse_table[i][j]={'I', k};
                    collection.push_back(goto_set);
                }
            }
                //collection.push_back(goto_set);
        }
    }

}

void fill_parse_table()
{
    int i, j, p_len, la_len;//la_len is look ahead length
    int sym_ind;

    for(i=0; i<collection.size(); i++)
    {
        for(auto itr=collection[i].begin(); itr!=collection[i].end(); itr++)
        {
            p_len=itr->aug_prod.length();
            if(itr->aug_prod[0]=='@' && itr->aug_prod[3]=='.')
            {
                parse_table[i][symbol_to_index['$']].first='A';
                parse_table[i][symbol_to_index['$']].second=0;
                break;
            }
            if(itr->aug_prod[p_len-1]=='.')
            {
                la_len=itr->look_ahead.length();
                for(j=0; j<la_len; j++)
                {
                    sym_ind=symbol_to_index[itr->look_ahead[j]];
                    parse_table[i][sym_ind].first='R';
                    parse_table[i][sym_ind].second=itr->p_no;
                }
            }
        }
    }
}


//Printing functions
void print_parse_table()
{
    int i, j;
    cout<<"Parse Table:\n    ";
    for(i=symbols.size()-1; i>=0; i--)
    {
        cout<<setw(4)<<symbols[i].sym;
    }
    cout<<"\n";

    string temp;
    for(i=0; i<collection.size(); i++)
    {
        cout<<setw(4)<<i;
        for(j=symbols.size()-1; j>=0; j--)
        {
            temp=parse_table[i][j].first;
            if(parse_table[i][j].second==-1)
                temp+="-";
            else
                temp+=to_string(parse_table[i][j].second);
            cout<<setw(4)<<temp;
        }
        cout<<"\n";
    }

}

int main()
{
    int i, j, k;

    //copy productions from the file and print he productions
    copy_productions_from_file();
    cout<<"Productions in the grammar are as follows :\n";
    for(i=0; i<productions.size(); i++)
    {
        cout<<productions[i]<<'\n';
    }
    cout<<"\n";

    //insert symbols into the symbol table and print them
    insert_symbols();
    cout<<"Symbols of the grammar are :\n";
    for(i=0; i<symbols.size(); i++)
    {
        cout<<symbols[i].sym<<" ";
        if(symbols[i].terminal)
            cout<<"T\n";
        else cout<<"NT\n";
    }
    cout<<"\n";

    //making space for parse table

    fill_firsts();
    //following commented section used only for testing
    cout<<"FIRST sets of the grammar are:\n";
    for(i=0; i<symbols.size(); i++)
    {
        //printing FIRST sets of all Non-terminals
        if(1)
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
    cout<<"\n";

    make_collection();

    //Print the collection calulated
    cout<<"Cannonical Collection of sets of LALR items :\n";
    for(i=0; i<collection.size(); i++)
    {
        cout<<"S"<<i<<":\n";
        auto itr=collection[i].begin();
        while(itr!=collection[i].end())
        {            
            cout<<itr->aug_prod<<", "<<itr->look_ahead<<"\n";
            itr++;
        }
        cout<<"\n";
    }
    cout<<"\n";

    fill_parse_table();

    print_parse_table();

}

