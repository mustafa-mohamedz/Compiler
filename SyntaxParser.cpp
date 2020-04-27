//
// Created by OWNER on 4/13/2020.
//

#include "SyntaxParser.h"

SyntaxParser::SyntaxParser(const LexicalAnalyzer &lexicalAnalyzer, const string &CFG_path) {
    ContextFreeGrammar cfg(CFG_path);
//    ParserTable parsing_table(cfg);
}
