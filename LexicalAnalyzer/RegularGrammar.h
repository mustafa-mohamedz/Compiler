#ifndef COMPILER_REGULARGRAMMAR_H
#define COMPILER_REGULARGRAMMAR_H

#include <string>
#include <vector>

enum Type {
    terminal, nonTerminal, special
};

class Symbol {
public:
    Type type;
    std::string value;
};

class Production {
public:
    Symbol LHS;
    std::vector<Symbol> RHS;
};

class RegularGrammar {
public:
    /*
    * Important Notes
    * 1- In definitions contain ranges like A-Z, it should be replaced by A|B|C|D ... |Z.
    * 2- The productions don't contain any non-terminals in RHS, substitute them by their RHS in Round brackets i.e. "(RHS)".
    * 3- non-terminals in RHS must end with white space or special symbol.
    * 4- remove the regular definitions and convert the Keywords and the punctuations to the same format as regular expression
    */
    std::vector<Symbol> terminal; //list contains all terminals in the grammar
    std::vector<Symbol> nonTerminal; //list contains all non-terminals in the grammar
    //The productions don't contain any non-terminals in RHS, substitute them by their RHS in Round brackets i.e. "(RHS)"
    std::vector<Production> regularExpression; //list contains all the productions in the grammar in the same format as regular expression

    //constructor
    RegularGrammar(std::string rulesPath);

};


#endif //COMPILER_REGULARGRAMMAR_H
