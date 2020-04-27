//
// Created by OWNER on 4/13/2020.
//

#include "SyntaxParser.h"

SyntaxParser::SyntaxParser(const LexicalAnalyzer &lexicalAnalyzer, const string &CFG_path) {
    LL1GrammarConstructor l(CFG_path);
    l.eliminate_left_recursion();
    ContextFreeGrammar grammar = l.left_factor();
    grammar.print();
    ParserTable table(grammar);
    vector<string> output = LLParser::get_output(grammar, table, lexicalAnalyzer);
    for (int i = 0; i < output.size(); ++i) {
        cout << output[i] << endl;
    }
}
