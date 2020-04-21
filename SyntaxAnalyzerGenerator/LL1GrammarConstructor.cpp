//
// Created by Ahmed on 4/19/2020.
//

#include "LL1GrammarConstructor.h"
#include <iostream>
#include <map>

using namespace std;
int counter = 0;
LL1GrammarConstructor::LL1GrammarConstructor(ContextFreeGrammar input){
    this->input_grammer = input;
    this->LL1_grammer.terminals = this->input_grammer.terminals;
}

ContextFreeGrammar LL1GrammarConstructor::eliminate_left_recursion() {
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

void LL1GrammarConstructor::eliminate_immediate_left_recursion(int position) {
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

ContextFreeGrammar LL1GrammarConstructor::left_factor() {
    LL1_grammer = input_grammer;

    for (int i = 0; i < LL1_grammer.productions.size(); ++i) {
        counter = 0;
        string temp_LHS = LL1_grammer.productions[i].LHS.value + "'";
        CFProduction current_rule = LL1_grammer.productions[i];
        int pointer = 0;
        map<Symbol, vector<int>> m;
        for (int j = 0; j < current_rule.RHS.size(); ++j) {
            vector<Symbol> current_production = current_rule.RHS[j];
            if (pointer >= current_production.size()) continue;
            Symbol current_symbol = current_production[pointer];
            map<Symbol, vector<int>>::iterator it = m.find(current_symbol);
            if (it != m.end()) {
                //exist
                it->second.push_back({j});
            } else {
                m.insert({current_symbol, {j}});
            }
        }
        map<Symbol, vector<int>>::iterator it;
        for (it = m.begin(); it != m.end(); it++) {
            vector<int> partition_indexes = it->second;
            vector<Symbol> common_prefix;
            if (it->second.size() > 1) {
                for (int n = 0; n < counter; ++n) {
                    temp_LHS.append("'");
                }
                counter++;
                common_prefix.push_back(it->first);
                int min_size = 1000;
                for (int i : partition_indexes) {
                    if (current_rule.RHS[i].size() < min_size) min_size = current_rule.RHS[i].size();
                }
                for (int k = 1; k < min_size; ++k) {
                    bool matched = true;
                    for (int j = 1; j < partition_indexes.size(); ++j) {
                        if (!(current_rule.RHS[partition_indexes[0]][k].value ==
                              current_rule.RHS[partition_indexes[j]][k].value &&
                              current_rule.RHS[partition_indexes[0]][k].type ==
                              current_rule.RHS[partition_indexes[j]][k].type)) {
                            matched = false;
                            break;
                        }
                    }
                    if (matched) {
                        common_prefix.push_back(current_rule.RHS[partition_indexes[0]][k]);
                    }
                }
                //create new rule
                vector<vector<Symbol>> new_RHS;
                bool empty = true;
                bool add_epsilon = false;
                for (int n = 0; n < partition_indexes.size(); ++n) {
                    vector<Symbol> new_p;
                    for (int j = common_prefix.size(); j < current_rule.RHS[partition_indexes[n]].size(); ++j) {
                        new_p.push_back(current_rule.RHS[partition_indexes[n]][j]);
                        empty = false;
                    }
                    if (!empty){
                        new_RHS.push_back(new_p);
                    }
                    else{
                        add_epsilon = true;
                    }
                }
                if (add_epsilon){
                    new_RHS.push_back({Symbol(special, "L")});
                }
                CFProduction new_rule(Symbol(nonTerminal, temp_LHS), new_RHS);
                LL1_grammer.productions.push_back(new_rule);
                //replace productions
                common_prefix.push_back(Symbol(nonTerminal, temp_LHS));
                LL1_grammer.productions[i].RHS[partition_indexes[0]] = common_prefix;
                for (int l = 1; l < partition_indexes.size(); ++l) {
                    LL1_grammer.productions[i].RHS[partition_indexes[l]] = {};
                }
            }
        }
        for (int i1 = 0; i1 < LL1_grammer.productions[i].RHS.size(); ++i1) {
            if(LL1_grammer.productions[i].RHS[i1].size() == 0){
                vector<vector<Symbol>>::iterator it;
                it = LL1_grammer.productions[i].RHS.begin() + i1;
                LL1_grammer.productions[i].RHS.erase(it);
                i1--;
            }
        }
    }
    return LL1_grammer;
}