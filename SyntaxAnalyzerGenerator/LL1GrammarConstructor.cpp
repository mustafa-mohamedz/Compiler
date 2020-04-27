//
// Created by Ahmed on 4/19/2020.
//

#include "LL1GrammarConstructor.h"
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int counter = 0;

LL1GrammarConstructor::LL1GrammarConstructor(const string &rulesPath) {
    ContextFreeGrammar contextFreeGrammar;
    vector<CFProduction> productions;
    unordered_set<Symbol, SymbolHF> terminals;

    string line;
    ifstream rulesFile(rulesPath);
    vector<string> all_productions;
    string str((std::istreambuf_iterator<char>(rulesFile)),
               std::istreambuf_iterator<char>());
    rulesFile.close();

    string delimiter = "# ";
    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        all_productions.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    all_productions.erase(all_productions.begin());
    all_productions.push_back(str);

    map<string, vector<string>> initial_productions;
    vector<string> lhss;
    vector<vector<string>> rhss;
    string delimiter1 = " = ";
    for (int i = 0; i < all_productions.size(); ++i) {
        size_t pos = 0;
        pos = all_productions[i].find(delimiter1);
        token = all_productions[i].substr(0, pos);
        all_productions[i].erase(0, pos + delimiter1.length());
        //erase new line
        string del = "\n";
        size_t po = 0;
        while ((po = all_productions[i].find(del)) != std::string::npos) {
            po = all_productions[i].find(del);
            all_productions[i].erase(po, 1);
        }
        //values
        vector<string> p;
        string delimiter = "|";
        size_t pos1 = 0;
        std::string token1;
        bool single = true;
        while ((pos1 = all_productions[i].find(delimiter)) != std::string::npos) {
            single = false;
            token1 = all_productions[i].substr(0, pos1);
            if (token1 != "") p.push_back(token1);
            all_productions[i].erase(0, pos1 + delimiter.length());
        }
        p.push_back(all_productions[i]);
        initial_productions.insert({token, p});
        lhss.push_back(token);
        rhss.push_back(p);
    }

    vector<CFProduction> ordered_grammar;
    for (int j = 0; j < lhss.size(); ++j) {
        CFProduction rule;
        Symbol lhs(nonTerminal, lhss[j]);
        rule.LHS = lhs;
        vector<vector<Symbol>> rhs;

        for (int i = 0; i < rhss[j].size(); ++i) {
            int found = 0;
            string s = rhss[j][i];
            vector<Symbol> production;
            int counter = 0;
            int size = s.size();
            while (counter < size) {
                char c = s[0];
                if (c == ' ') {
                    s.erase(0, 1);
                    counter++;
                } else if (c == '\\' && s[1] == 'L') {
                    Symbol pp(special, "L");
                    production.push_back(pp);
                    terminals.insert(pp);
                    break;
                } else if (c == '\'') {
                    size_t p;
                    p = s.find("'", 1);
                    s.erase(0, 1);
                    //terminal
                    string temp = s.substr(0, p - 1);
                    s.erase(0, temp.size() + 1);
                    counter += (temp.size() + 2);
                    Symbol pp(terminal, temp);
                    production.push_back(pp);
                    terminals.insert(pp);
                } else {
                    size_t p = s.find("'", 0);
                    if (p != std::string::npos) {
                        string temp = s.substr(0, p - 1);
                        s.erase(0, temp.size());
                        counter += (temp.size());
                        Symbol pp(nonTerminal, temp);
                        production.push_back(pp);
                    } else {
                        size_t p = s.find(" ", 0);
                        if (p != std::string::npos) {
                            string temp = s.substr(0, p);
                            s.erase(0, temp.size() + 1);
                            counter += (temp.size() + 1);
                            Symbol pp(nonTerminal, temp);
                            production.push_back(pp);
                        } else {
                            string temp = s.substr(0, s.size());
                            counter += (temp.size());
                            Symbol pp(nonTerminal, temp);
                            production.push_back(pp);
                        }
                    }

                }
            }
            rhs.push_back(production);
        }
        rule.RHS = rhs;
        productions.push_back(rule);
        ordered_grammar.push_back(rule);
    }
    this->LL1_grammer.terminals = terminals;
    this->LL1_grammer.productions = productions;
}

ContextFreeGrammar LL1GrammarConstructor::eliminate_left_recursion() {
    input_grammer = LL1_grammer;
    LL1_grammer.productions.clear();
    for (int i = 0; i < input_grammer.productions.size(); ++i) {
        CFProduction current_p = input_grammer.productions[i];
        for (int j = 0; j < i; ++j) {
            CFProduction prev_p = input_grammer.productions[j];
            for (int m = 0; m < LL1_grammer.productions.size(); ++m) {
                if (LL1_grammer.productions[m].LHS.value == prev_p.LHS.value) {
                    prev_p = LL1_grammer.productions[m];
                    break;
                }
            }
            Symbol prev_symbol = prev_p.LHS;
            vector<vector<Symbol>> new_RHS;
            for (vector<Symbol> p : current_p.RHS) {
                bool found = false;
                Symbol s = p[0];
                if (s.value == prev_symbol.value && s.type == prev_symbol.type) {
                    //replace algorithm temp_RHS is filled
                    for (int g = 0; g < prev_p.RHS.size(); ++g) {
                        vector<Symbol> temp;
                        //non terminal position
                        for (int k = 0; k < prev_p.RHS[g].size(); ++k) {
                            temp.push_back(prev_p.RHS[g][k]);
                        }
                        //after non terminal
                        for (int l = 1; l < p.size(); ++l) {
                            temp.push_back(p[l]);
                        }
                        new_RHS.push_back(temp);
                    }
                    found = true;
                }

                if (!found) {
                    new_RHS.push_back(p);
                }
            }
            current_p.RHS = new_RHS;
            input_grammer.productions[i] = current_p;
        }
        LL1_grammer.productions.push_back(input_grammer.productions[i]);
        eliminate_immediate_left_recursion(i);
    }
    return LL1_grammer;
}

void LL1GrammarConstructor::eliminate_immediate_left_recursion(int position) {
    vector<vector<Symbol>> with_LL;
    vector<vector<Symbol>> without_LL;
    string temp = input_grammer.productions[position].LHS.value + "'";
    bool found = false;
    for (vector<Symbol> v : input_grammer.productions[position].RHS) {
        if (v[0].type == input_grammer.productions[position].LHS.type &&
            v[0].value == input_grammer.productions[position].LHS.value) {
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
    if (found) {
        LL1_grammer.productions[LL1_grammer.productions.size() - 1].RHS = without_LL;
        //Create new rule
        with_LL.push_back({Symbol(special, "L")});
        CFProduction new_rule(Symbol(nonTerminal, temp), with_LL);
        LL1_grammer.productions.push_back(new_rule);
    }
}

ContextFreeGrammar LL1GrammarConstructor::left_factor() {
    for (int i = 0; i < LL1_grammer.productions.size(); ++i) {
        counter = 0;
        string temp_LHS = LL1_grammer.productions[i].LHS.value + "*";
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
                    temp_LHS.append("*");
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
                    if (!empty) {
                        new_RHS.push_back(new_p);
                    } else {
                        add_epsilon = true;
                    }
                }
                if (add_epsilon) {
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
            if (LL1_grammer.productions[i].RHS[i1].size() == 0) {
                vector<vector<Symbol>>::iterator it;
                it = LL1_grammer.productions[i].RHS.begin() + i1;
                LL1_grammer.productions[i].RHS.erase(it);
                i1--;
            }
        }
    }
    return LL1_grammer;
}