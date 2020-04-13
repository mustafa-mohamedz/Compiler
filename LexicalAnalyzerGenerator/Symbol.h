//
// Created by OWNER on 4/13/2020.
//

#ifndef COMPILER_SYMBOL_H
#define COMPILER_SYMBOL_H


#include <string>

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

    bool operator ==(const Symbol &x) const {
        return x.value == value && type == x.type;
    }
    Type type;
    std::string value;
};

class SymbolHF {
public:
    size_t operator()(const Symbol& s) const{
        string str = to_string(s.type) + s.value;
        return (hash<string>()(str));
    }
};


#endif //COMPILER_SYMBOL_H
