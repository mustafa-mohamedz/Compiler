#ifndef COMPILER_PROGRAMREADER_H
#define COMPILER_PROGRAMREADER_H

#include "DFA.h"

class Token {
public:
    /**
     * constructor
     * @param type the LHS of the accepted production
     * @param value the real value of the accepted production
     */
    Token(std::string type, std::string value) {
        this->type = type;
        this->value = value;
    }
    std::string type;
    std::string value;
};

class ProgramReader {
private:
    vector<Token>::size_type tokenIndex;
    vector<Token> tokenList;
    /**
      * convert string without spaces to vector of tokens
      * @param stringBlock string without spaces to be divided into tokens
      * @param dfa used in tokenizing stringBlock
      * @return vector of processed tokens
      */
    vector<Token> processStringBlock(const std::string &stringBlock, const DFA &dfa);
public:
    /**
     * constructor
     * @param programPath the path of the program that will be tokenized
     * @param dfa the deterministic finite automate used to tokenize the input program
     */
    ProgramReader(const string &programPath, const DFA &dfa);
    vector<Token> getTokens();
    bool hasNextToken();
    Token getNextToken();
};


#endif //COMPILER_PROGRAMREADER_H
