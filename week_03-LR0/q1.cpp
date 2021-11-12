#include <bits/stdc++.h>
using namespace std;

int num_productions;
vector<string> productions;
set<string> closure_set;
string s_compliment = "@";

bool isNonTerminal(char x) {
    if( 'A' <= x && x <='Z') return true;
    return false;
}

/// The Productions are copied from the input file to a 2d-matrix of Strings
/// Format of Input file:
/// 1. First Line should cotain number of Productions (say N)
/// 2. The next N lines should contain productions in the form S=aA (No space in between any character)
/// 3. Avoid Productions of Format S = aA | a
/// 4. Use # for epsilon
void copy_productions_from_file() {
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

void insert_initial_grammar() {
    string s = productions[0];
    string augment_product = s_compliment + "=";
    augment_product.append(s);
    augment_product = augment_product.substr(0, 3);
    num_productions++;
    productions.insert(productions.begin(), augment_product);
}

void print_sets() {
    cout << "\nItems\n";
    for(auto i = closure_set.begin(); i != closure_set.end(); i++) cout << *i << "\n";
    cout << endl;
}

void calculate_closure_rec(string p, bool insert_at_2) {
    if (closure_set.count(p) == 1) return ;
    if(p[2] != '.' && insert_at_2) {
        p.insert(p.begin()+2, 1, '.');
        closure_set.insert(p);
    } 
    int i, j;
    for(i=2; i<p.size()-1; i++) {
        if (p[i] == '.' && isNonTerminal(p[i+1])) {
            for(j=0; j<num_productions; j++) {
                if (productions[j][0] == p[i+1]) {
                    calculate_closure_rec(productions[j], true);
                }
            }
        }
    }
}

void calculate_closure() {
    // Add . at the beginning of right side in all prodcutions
    string temp = productions[0];
    int i, j;

    calculate_closure_rec(temp, true);
}

void calculate_goto() {
    auto p = closure_set.begin();
    string temp;
    for(p=closure_set.begin(); p != closure_set.end(); p++) {
        temp = *p;
        for(int i=2; i<temp.size()-1; i++) {
            if (temp[i] == '.') {
                swap(temp[i], temp[i+1]);
                closure_set.insert(temp);
                calculate_closure_rec(temp, false);
            }
        }
    }
}

int main() {
    copy_productions_from_file();
    insert_initial_grammar();
    calculate_closure();
    calculate_goto();
    print_sets();
    return 0;
}