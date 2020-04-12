#ifndef COMPILER_LEXICALANALYZER_H
#define COMPILER_LEXICALANALYZER_H

#include <InputParser.h>
#include <DFABuilder.h>
#include "LexicalAnalyzer/ProgramReader.h"

class LexicalAnalyzer {
private:
    ProgramReader pr;
public:
    LexicalAnalyzer(const string& input_program_path, const string& lexical_rules_path);
    vector<string> getLogMessages();
    bool hasNextToken();
    Token getNextToken();
};


#endif //COMPILER_LEXICALANALYZER_H
