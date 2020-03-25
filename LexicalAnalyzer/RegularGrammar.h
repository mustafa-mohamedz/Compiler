#ifndef COMPILER_REGULARGRAMMAR_H
#define COMPILER_REGULARGRAMMAR_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>

using namespace std;
enum Type {
    terminal, nonTerminal, special
};

class Symbol {

public:
    Symbol(Type t, string v) {
        value = v;
        type = t;
    }

    Symbol() {
    }

    bool operator<(const Symbol &x) const {
        return value < x.value || (x.value == value && type < x.type);
    }

    Type type;
    std::string value;
};

class Production {
public:
    Production(Symbol &LHS, vector<Symbol> &RHS, int priority) {
        this->LHS = LHS;
        this->RHS = RHS;
        this->priority = priority;
    }

    Symbol LHS;
    std::vector<Symbol> RHS;
    int priority;
};

class RegularGrammar {
private:
    void processKeywords(string &line);

    void processPunctuation(string &line);

    vector<Symbol> processRHS(string &rightSide);

    void processExpression(string &line, int i);

    void processRegularDefinition(string &line);

    vector<Symbol> processNonSpecial(const string &);

    vector<Symbol> processSpecial(const string &, int &);

    vector<Symbol> substituteRange(const string &, int &);
    set<Symbol> terminals; //set contains all terminals in the grammar
    set<Symbol> nonTerminals; //set contains all non-terminals in the grammar
    std::map<Symbol, std::vector<Symbol>> regularDefinition;
public:
    /*
    * Important Notes
    * 1- In definitions contain ranges like A-Z, it should be replaced by A|B|C|D ... |Z.
    * 2- The productions don't contain any non-terminals in RHS, substitute them by their RHS in Round brackets i.e. "(RHS)".
    * 3- non-terminals in RHS must end with white space or special symbol.
    * 4- remove the regular definitions and convert the Keywords and the punctuations to the same format as regular expression
    * 5- epsilon is symbol with type special and value = "L"
    */
    //The productions don't contain any non-terminals in RHS, substitute them by their RHS in Round brackets i.e. "(RHS)"
    std::vector<Production> regularExpression; //list contains all the productions in the grammar in the same format as regular expression


    //constructor
    RegularGrammar(const std::string &rulesPath);

};


#endif //COMPILER_REGULARGRAMMAR_H
