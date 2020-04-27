//
// Created by OWNER on 4/13/2020.
//

#ifndef COMPILER_CONTEXTFREEGRAMMAR_H
#define COMPILER_CONTEXTFREEGRAMMAR_H

#include <string>
#include <vector>
#include <unordered_set>
#include "../LexicalAnalyzerGenerator/Symbol.h"

class CFProduction{
public:
    Symbol LHS;
    vector<vector<Symbol>> RHS;
    CFProduction(Symbol LHS,vector<vector<Symbol>> RHS){
        this->LHS = LHS;
        this->RHS = RHS;
    };
    CFProduction(){};
};

class ContextFreeGrammar {

public:
    ContextFreeGrammar(const string &CFG_path);
    ContextFreeGrammar(){};
    void print();
    unordered_set<Symbol,SymbolHF> terminals;
    //startSymbol's production is productions[0]
    vector<CFProduction> productions;
};


#endif //COMPILER_CONTEXTFREEGRAMMAR_H
