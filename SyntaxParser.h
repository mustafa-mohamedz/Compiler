//
// Created by OWNER on 4/13/2020.
//

#ifndef COMPILER_SYNTAXPARSER_H
#define COMPILER_SYNTAXPARSER_H


#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzerGenerator/ParserTable.h"
class SyntaxParser {
public:
    SyntaxParser(const LexicalAnalyzer&,const string& CFG_path);
};


#endif //COMPILER_SYNTAXPARSER_H
