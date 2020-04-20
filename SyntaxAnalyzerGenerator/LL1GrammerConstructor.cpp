//
// Created by Ahmed on 4/19/2020.
//

#include "LL1GrammerConstructor.h"
#include <iostream>
using namespace std;

LL1GrammerConstructor::LL1GrammerConstructor(ContextFreeGrammar input){
    this->input_grammer = input;
}

ContextFreeGrammar LL1GrammerConstructor::eliminate_left_recursion() {
    LL1_grammer.terminals = input_grammer.terminals;
    for (int i = 0; i < input_grammer.productions.size(); ++i){
        CFProduction current_p = input_grammer.productions[i];
        for (int j = 0; j < i; ++j) {
            CFProduction prev_p = input_grammer.productions[j];
            for (int m = 0; m < LL1_grammer.productions.size(); ++m) {
                if (LL1_grammer.productions[m].LHS.value == prev_p.LHS.value){
                    prev_p = LL1_grammer.productions[m];
                    break;
                }
            }
            Symbol prev_symbol = prev_p.LHS;
            vector<vector<Symbol>> new_RHS;
            for (vector<Symbol> p : current_p.RHS){
                bool found = false;
                for (int t = 0; t < p.size(); ++t){
                    Symbol s = p[t];
                    if (s.value == prev_symbol.value && s.type == prev_symbol.type){
                        //replace algorithm temp_RHS is filled
                        for (int g = 0; g < prev_p.RHS.size(); ++g){
                            vector<Symbol> temp;
                            //before non terminal
                            for (int q = 0; q < t; ++q){
                                temp.push_back(p[q]);
                            }
                            //non terminal position
                            for (int k = 0; k < prev_p.RHS[g].size(); ++k) {
                                temp.push_back(prev_p.RHS[g][k]);
                            }
                            //after non terminal
                            for (int l = t + 1; l < p.size(); ++l) {
                                temp.push_back(p[l]);
                            }
                            new_RHS.push_back(temp);
                        }
                        found = true;
                    }
                }
                if (!found){
                    new_RHS.push_back(p);
                }
            }
            current_p.RHS = new_RHS;
            input_grammer.productions[i] = current_p;
        }
        LL1_grammer.productions.push_back(input_grammer.productions[i]);
        eliminate_immediate_left_recursion(i);
    }
    return  LL1_grammer;
}

void LL1GrammerConstructor::eliminate_immediate_left_recursion(int position) {
    vector<vector<Symbol>> with_LL;
    vector<vector<Symbol>> without_LL;
    string temp = input_grammer.productions[position].LHS.value + "'";
    bool found = false;
    for (vector<Symbol> v : input_grammer.productions[position].RHS) {
        if (v[0].type == input_grammer.productions[position].LHS.type && v[0].value == input_grammer.productions[position].LHS.value){
            found = true;
            vector<Symbol>::iterator it;
            it = v.begin();
            v.erase(it);
            v.push_back(Symbol(nonTerminal, temp));
            with_LL.push_back(v);
        } else {
            v.push_back(Symbol(nonTerminal, temp));
            without_LL.push_back(v);
        }
    }
    if (found){
        LL1_grammer.productions[LL1_grammer.productions.size() - 1].RHS = without_LL;
        //Create new rule
        with_LL.push_back({Symbol(special, "L")});
        CFProduction new_rule(Symbol(nonTerminal, temp), with_LL);
        LL1_grammer.productions.push_back(new_rule);
    }
}