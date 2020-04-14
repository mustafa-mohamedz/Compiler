//
// Created by OWNER on 4/13/2020.
//

#include "SyntaxAnalyzerUtilities.h"

SyntaxAnalyzerUtilities::SyntaxAnalyzerUtilities(const ContextFreeGrammar &contextFreeGrammar) {
    this->contextFreeGrammar = contextFreeGrammar;
    fill_index_of_symbol_map();
    for (int i = 0; i < contextFreeGrammar.productions.size(); ++i) {
        first_set_map.insert({contextFreeGrammar.productions[i].LHS,compute_first_set_of(contextFreeGrammar.productions[i].LHS)});
        follow_set_map.insert({contextFreeGrammar.productions[i].LHS,compute_follow_set_of(contextFreeGrammar.productions[i].LHS)});
    }
}

unordered_set<Symbol, SymbolHF> SyntaxAnalyzerUtilities::get_first_set_of(vector<Symbol> rhs) {
    unordered_set<Symbol, SymbolHF> result;
    if(rhs[0].type == nonTerminal){
        result.insert(rhs[0]);
    }else if(rhs[0].type == special && rhs[0].value == "L"){
        result.insert(rhs[0]);
    }else{
        Symbol epsilon(special,"L");
        for (int i = 0; i < rhs.size(); ++i) {
            auto temp = get_first_set_of(rhs);
            if(temp.find(epsilon) == temp.end()){
                result.insert(temp.begin(),temp.end());
                return result;
            }
            temp.erase(epsilon);
            result.insert(temp.begin(),temp.end());
        }
        result.insert(epsilon);
    }
    return result;
}

unordered_set<Symbol, SymbolHF> SyntaxAnalyzerUtilities::compute_first_set_of(const Symbol &symbol) {
    unordered_set<Symbol, SymbolHF> result;
    if(symbol.type == nonTerminal){
        result.insert(symbol);
    }else if(symbol.type == special && symbol.value == "L"){
        result.insert(symbol);
    }else{
        auto itr = first_set_map.find(symbol);
        if(itr !=first_set_map.end()) {
            result.insert(itr->second.begin(),itr->second.end());
        }else{
            int index_of_symbol = index_of_symbol_map.find(symbol)->second;
            CFProduction production = contextFreeGrammar.productions[index_of_symbol];
            for (int i = 0; i < production.RHS.size(); ++i) {
                auto temp = get_first_set_of(production.RHS[i]);
                result.insert(temp.begin(),temp.end());
            }
        }
    }
    return result;
}

unordered_set<Symbol, SymbolHF> SyntaxAnalyzerUtilities::compute_follow_set_of(const Symbol& symbol) {
    return unordered_set<Symbol, SymbolHF>();
}

void SyntaxAnalyzerUtilities::fill_index_of_symbol_map() {
    for (int i = 0; i < contextFreeGrammar.productions.size(); ++i) {
        index_of_symbol_map.insert({contextFreeGrammar.productions[i].LHS,i});
    }
}
