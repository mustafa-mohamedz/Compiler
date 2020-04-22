//
// Created by Amr Geneidy on 4/22/20.
//
#include "LLParser.h"

vector<string> LLParser::get_output(ContextFreeGrammar cfg, ParserTable pt, LexicalAnalyzer la) {
    vector<string> res;
    Symbol start_symbol = cfg.productions[0].LHS;
    res.push_back(start_symbol.value);
    vector<Symbol> start_transaction = cfg.productions[0].RHS[0];
    vector<Symbol> s;
    s.push_back(start_symbol);
    vector<string> matched_symbols;
    Symbol current_input = Symbol(special, "");
    while (!s.empty()) {
        Symbol curr_symbol = s[s.size() - 1];
        s.pop_back();
        if (current_input.type == special && current_input.value.empty()) {
            if (la.hasNextToken()) {
                current_input = Symbol(terminal, la.getNextToken().type);
            } else {
                current_input = Symbol(special, "$");
            }
        }
        if (curr_symbol.type == terminal) {
            matched_symbols.push_back(curr_symbol.value);
            // match with input
            if (curr_symbol.value == current_input.value) {
                current_input = Symbol(special, "");
            } else {
                res.push_back("Error: missing " + curr_symbol.value + ", inserted");
            }
        } else if (curr_symbol.type == nonTerminal) {
            EntryType e_type = pt.get_entry_type(curr_symbol, current_input);
            // check for next transaction
            if (e_type == production) {
                // update stack
                vector<Symbol> rhs_symbols = pt.get_entry(curr_symbol, current_input);
                // skipping epsilon case
                if (rhs_symbols.size() != 1 || rhs_symbols[0].type != special || rhs_symbols[0].value != "L") {
                    for (int i = rhs_symbols.size() - 1; i >= 0; i--) {
                        s.push_back(rhs_symbols[i]);
                    }
                }
                // print current output line
                string curr_line;
                for (int i = 0; i < matched_symbols.size(); i++) {
                    curr_line += matched_symbols[i] + " ";
                }
                for (int i = s.size() - 1; i >= 0; i--) {
                    curr_line += s[i].value + " ";
                }
                res.push_back(curr_line);
            } else if (e_type == error) {
                res.push_back("Error:(illegal " + curr_symbol.value + ") – discard " + current_input.value);
                current_input = Symbol(special, "");
                s.push_back(curr_symbol);
            } else {
                // sync
                res.push_back("Sync:(illegal " + curr_symbol.value + ") – discard " + curr_symbol.value);
            }
        }
    }
    if (current_input.type != special || (current_input.value != "" && current_input.value != "$")) {
        res.push_back("Error: expected end of file – discard " + current_input.value);
    }
    while (la.hasNextToken()) {
        res.push_back("Error: expected end of file – discard " + la.getNextToken().value);
    }
    return res;
}