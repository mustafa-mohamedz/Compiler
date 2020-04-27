//
// Created by Amr Geneidy on 4/22/20.
//

#ifndef COMPILER_LLPARSER_H
#define COMPILER_LLPARSER_H
#include "ParserTable.h"
#include "ContextFreeGrammar.h"
#include "../LexicalAnalyzer.h"
#include "ParserTable.h"
#include <stack>
class LLParser {
public:
    static vector<string> get_output(ContextFreeGrammar c, ParserTable t, LexicalAnalyzer la);
};
#endif //COMPILER_LLPARSER_H
