#ifndef COMPILER_PARSERTABLE_H
#define COMPILER_PARSERTABLE_H

#include "SyntaxAnalyzerUtilities.h"

enum EntryType {
    production, sync, error
};

class ParserTable {
private:
    ContextFreeGrammar cfg;
    unordered_map<Symbol, unordered_map<Symbol, pair<int, int>, SymbolHF>, SymbolHF> production_entries;
    unordered_map<Symbol, unordered_set<Symbol, SymbolHF>, SymbolHF> sync_entries;

    void validate_input(const Symbol &non_terminal, const Symbol &terminal);

    unordered_map<Symbol, pair<int, int>, SymbolHF> build_production_row(int, SyntaxAnalyzerUtilities);

    unordered_set<Symbol, SymbolHF> build_sync_row(int, SyntaxAnalyzerUtilities);

    vector<vector<string>> table_to_string();

    vector<int> get_entries_widths(const vector<vector<string>> &);

    string symbol_vector_to_string(const vector<Symbol> &list);

public:

    ParserTable(const ContextFreeGrammar &);

    /**
     * This function is used to check the type of the entry before using get_entry function.
     * @param non_terminal The Symbol which determines the row in the table.
     * @param terminal The Symbol which determines the column in the table.
     * @return Return the type of the entry in the table i.e.(production, sync, error).
     * @throw Throw exception if the input is invalid.
     */
    EntryType get_entry_type(const Symbol &non_terminal, const Symbol &terminal);

    /**
     * This function is used to locate a production in the table.
     * @warning This function is only used if the type of the entry is production (check entry type using get_entry_type function).
     * @param non_terminal The Symbol which determines the row in the table.
     * @param terminal The Symbol which determines the column in the table.
     * @return vector<Symbol> contains right hand side of entry production.
     * @throw Throw exception if the entry contains no production or invalid input.
     */
    vector<Symbol> get_entry(const Symbol &non_terminal, const Symbol &terminal);

    void print();

};


#endif //COMPILER_PARSERTABLE_H
