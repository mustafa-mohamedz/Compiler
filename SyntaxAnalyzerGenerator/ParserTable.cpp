#include <iostream>
#include <fstream>
#include <iomanip>
#include "ParserTable.h"
using namespace std;

ParserTable::ParserTable(const ContextFreeGrammar &contextFreeGrammar) {
    this->cfg = contextFreeGrammar;
    SyntaxAnalyzerUtilities util(this->cfg);
    vector<CFProduction> production_list = this->cfg.productions;
    for (int i = 0; i < production_list.size(); ++i) {
        this->production_entries.insert({production_list[i].LHS, build_production_row(i, util)});
        this->sync_entries.insert({production_list[i].LHS, build_sync_row(i, util)});
    }
    print();
}

unordered_map<Symbol, pair<int, int>, SymbolHF>
ParserTable::build_production_row(int production_index, SyntaxAnalyzerUtilities util) {
    unordered_map<Symbol, pair<int, int>, SymbolHF> production_row;
    CFProduction prod = this->cfg.productions[production_index];
    Symbol epsilon(special, "L");
    for (int i = 0; i < prod.RHS.size(); ++i) {
        vector<Symbol> sub_prod = prod.RHS[i];
        auto first_set = util.get_first_set_of(sub_prod);
        if (first_set.find(epsilon) != first_set.end()) {//add follow
            first_set.erase(epsilon);
            auto follow_set = util.get_follow_set_of(prod.LHS);
            for (const Symbol &terminal : follow_set) {
                if (production_row.find(terminal) != production_row.end()) {
                    cout << "ambiguous grammar !!" << endl;
                } else {
                    production_row.insert({terminal, {production_index, i}});
                }
            }
        }
        for (const Symbol &terminal : first_set) {//add first
            if (production_row.find(terminal) != production_row.end()) {
                cout << "ambiguous grammar !!" << endl;
            } else {
                production_row.insert({terminal, {production_index, i}});
            }
        }
    }
    return production_row;
}

unordered_set<Symbol, SymbolHF> ParserTable::build_sync_row(int production_index, SyntaxAnalyzerUtilities util) {
    unordered_set<Symbol, SymbolHF> sync_row;
    CFProduction prod = this->cfg.productions[production_index];
    Symbol epsilon(special, "L");
    auto first_set = util.get_first_set_of({prod.LHS});
    if (first_set.find(epsilon) == first_set.end()) {
        auto follow_set = util.get_follow_set_of(prod.LHS);
        for (const Symbol &terminal : follow_set) {
            if (production_entries.find(prod.LHS)->second.find(terminal) ==
                production_entries.find(prod.LHS)->second.end()) {
                sync_row.insert(terminal);
            }
        }
    }
    return sync_row;
}

EntryType ParserTable::get_entry_type(const Symbol &non_terminal, const Symbol &terminal) {
    validate_input(non_terminal, terminal);
    unordered_map<Symbol, pair<int, int>, SymbolHF> production_entries_row = production_entries.find(
            non_terminal)->second;
    unordered_set<Symbol, SymbolHF> sync_entries_row = sync_entries.find(non_terminal)->second;
    if (production_entries_row.find(terminal) != production_entries_row.end()) {
        return production;
    } else if (sync_entries_row.find(terminal) != sync_entries_row.end()) {
        return sync;
    } else {
        return error;
    }
}

vector<Symbol> ParserTable::get_entry(const Symbol &non_terminal, const Symbol &terminal) {
    validate_input(non_terminal, terminal);
    unordered_map<Symbol, pair<int, int>, SymbolHF> production_entries_row = production_entries.find(
            non_terminal)->second;
    if (production_entries_row.find(terminal) != production_entries_row.end()) {//production in grammar
        pair<int, int> production_pos = production_entries_row.find(terminal)->second;
        return this->cfg.productions[production_pos.first].RHS[production_pos.second];
    } else {//not a production
        throw runtime_error("not a production entry");
    }
}

void ParserTable::validate_input(const Symbol &non_terminal, const Symbol &terminal) {
    Symbol end_of_line(special, "$");
    if (cfg.terminals.find(terminal) == cfg.terminals.end() && !(terminal == end_of_line))
        throw runtime_error("terminal is not in the grammar");
    if (production_entries.find(non_terminal) == production_entries.end())
        throw runtime_error("non_terminal is not in the grammar");
}


void ParserTable::print() {
    ofstream file("..//parser_table.txt");
    vector<vector<string>> table = table_to_string();
    vector<int> width_list = get_entries_widths(table);
    for (int i = 0; i < table.size(); ++i) {
        file << "| ";
        for (int j = 0; j < table[i].size(); ++j) {
            file << left << setw(width_list[j]) << setfill(' ') << table[i][j] << " | ";
        }
        file << endl;
    }
}

vector<vector<string>> ParserTable::table_to_string() {
    vector<vector<string>> table;
    vector<string> row;
    //first row
    row.push_back("Parser Table");
    for (Symbol terminal : cfg.terminals) {
        row.push_back(terminal.value);
    }
    row.push_back("$");
    table.push_back(row);
    //table cell
    row.clear();
    Symbol epsilon(special, "L");
    for (CFProduction prod : cfg.productions) {
        row.push_back(prod.LHS.value);
        for (Symbol terminal : cfg.terminals) {
            EntryType type = get_entry_type(prod.LHS, terminal);
            if (type == production) {
                vector<Symbol> cell = get_entry(prod.LHS, terminal);
                string cell_string = symbol_vector_to_string(cell);
                if (cell.size() > 0 && cell[0] == epsilon && cell_string == "L") {
                    row.push_back("{epsilon}");
                } else {
                    row.push_back(cell_string);
                }
            } else if (type == sync) {
                row.push_back("{sync}");
            } else if (type == error) {
                row.push_back("{error}");
            }
        }
        //$ column
        Symbol input_end(special, "$");
        EntryType type = get_entry_type(prod.LHS, input_end);
        if (type == production) {
            vector<Symbol> cell = get_entry(prod.LHS, input_end);
            string cell_string = symbol_vector_to_string(cell);
            if (cell.size() > 0 && cell[0] == epsilon && cell_string == "L") {
                row.push_back("{epsilon}");
            } else {
                row.push_back(cell_string);
            }
        } else if (type == sync) {
            row.push_back("{sync}");
        } else if (type == error) {
            row.push_back("{error}");
        }
        table.push_back(row);
        row.clear();
    }
    return table;
}

vector<int> ParserTable::get_entries_widths(const vector<vector<string>> &table) {
    vector<int> width_list;
    for (int j = 0; j < table[0].size(); ++j) {
        unsigned int max_length = 0;
        for (int i = 0; i < table.size(); ++i) {
            max_length = max_length > table[i][j].size() ? max_length : table[i][j].size();
        }
        width_list.push_back(max_length);
    }
    return width_list;
}

string ParserTable::symbol_vector_to_string(const vector<Symbol> &list) {
    string result;
    for (int i = 0; i < list.size(); ++i) {
        result += list[i].value;
        if (i < list.size() - 1) {
            result += " ";
        }
    }
    return result;
}
