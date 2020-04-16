#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer(const string &lexical_rules_path, const string &input_program_path) {
    RegularGrammar rg(lexical_rules_path);
    set<Symbol> alphabetWithoutEpsilon = rg.terminals;
    rg.terminals.insert(Symbol(special, "L"));
    InputParser parser(rg);
    vector<NFA> temp = parser.get_NFA();
    FinalNFA finalNfa(temp, rg.terminals);
    DFABuilder dfaBuilder;
    MinimizedDFA mDFA(dfaBuilder.basicConstruct(finalNfa));
    mDFA.printDFA(alphabetWithoutEpsilon);
    ProgramReader pr(input_program_path, mDFA);
    this->pr = pr;
}

vector<string> LexicalAnalyzer::getLogMessages() {
    return pr.getLogMessages();
}

bool LexicalAnalyzer::hasNextToken() {
    return pr.hasNextToken();
}

Token LexicalAnalyzer::getNextToken() {
    return pr.getNextToken();
}
