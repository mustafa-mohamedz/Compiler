//
// Created by Ahmed on 4/19/2020.
//

#include "LL1GrammerConstructor.h"
#include <iostream>
using namespace std;

LL1GrammerConstructor::LL1GrammerConstructor(ContextFreeGrammar input){
    this->input_grammer = input;
}

void LL1GrammerConstructor::eliminate_left_recuresion() {
    for (int i = 0; i < input_grammer.productions.size(); ++i){
        CFProduction current_p = input_grammer.productions[i];
        for (int j = 0; j < i; ++j) {
            CFProduction prev_p = input_grammer.productions[j];
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
            eliminate_immediate_left_recuresion(j);
        }
    }
}

void LL1GrammerConstructor::eliminate_immediate_left_recuresion(int position) {
    cout << "eliminate_immediate_left_recuresion";
}