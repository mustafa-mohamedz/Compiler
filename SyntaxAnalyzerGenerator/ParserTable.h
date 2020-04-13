//
// Created by OWNER on 4/13/2020.
//

#ifndef COMPILER_PARSERTABLE_H
#define COMPILER_PARSERTABLE_H

#include "SyntaxAnalyzerUtilities.h"
enum EntryType{
    production,sync,error
};
class ParserTable {
private:
    ContextFreeGrammar contextFreeGrammar;
    unordered_map<Symbol,unordered_map<Symbol,pair<int,int>,SymbolHF>,SymbolHF> production_entries;
    unordered_map<Symbol,unordered_set<Symbol,SymbolHF>,SymbolHF> epsilon_entries;
    unordered_map<Symbol,unordered_set<Symbol,SymbolHF>,SymbolHF> sync_entries;

public:
    //TODO check ambiguous grammar
    ParserTable(const ContextFreeGrammar&);
    EntryType get_entry_type(Symbol non_terminal,Symbol terminal);
    /**
     *
     * @param non_terminal
     * @param terminal
     * @return vector<Symbol> contains right hand side of entry production
     * @throw exception if the entry contains no production
     */
    vector<Symbol> get_entry(Symbol non_terminal,Symbol terminal);

};


#endif //COMPILER_PARSERTABLE_H
