//
// Created by OWNER on 4/13/2020.
//

#ifndef COMPILER_SYNTAXANALYZERUTILITIES_H
#define COMPILER_SYNTAXANALYZERUTILITIES_H


#include "ContextFreeGrammar.h"
#include <unordered_map>
class SyntaxAnalyzerUtilities {
private:
    ContextFreeGrammar contextFreeGrammar;
    unordered_map<Symbol,unordered_set<Symbol,SymbolHF>,SymbolHF> first_set_map;
    unordered_map<Symbol,unordered_set<Symbol,SymbolHF>,SymbolHF> follow_set_map;
    unordered_map<Symbol,int,SymbolHF> index_of_symbol_map;

    unordered_set<Symbol, SymbolHF> compute_first_set_of(const Symbol &symbol);
    unordered_set<Symbol, SymbolHF> compute_follow_set_of(const Symbol &symbol);
    void fill_index_of_symbol_map();
public:
    SyntaxAnalyzerUtilities(const ContextFreeGrammar& contextFreeGrammar);
    unordered_set<Symbol,SymbolHF> get_first_set_of(vector<Symbol>);
    unordered_set<Symbol,SymbolHF> get_follow_set_of(Symbol);
};


#endif //COMPILER_SYNTAXANALYZERUTILITIES_H
