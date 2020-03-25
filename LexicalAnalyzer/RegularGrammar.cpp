#include "RegularGrammar.h"



bool isDelimiter(char x) {
    return x == '+' || x == '-' || x == '\\' || x == '*' || x == '|' || x == '(' || x == ')' || x == ' ' || x == '\t';
}

RegularGrammar::RegularGrammar(const std::string &rulesPath) {
    std::string line;
    int priorityCounter = 1;
    std::ifstream myfile(rulesPath);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            trim(line);
            if (line[0] == '{') {
                processKeywords(line);
            } else if (line[0] == '[') {
                processPunctuation(line);
            } else if (line.find(":") != std::string::npos || line.find("=") != std::string::npos) {
                if (line.find(":") < line.find("=")) {
                    processExpression(line, priorityCounter);
                    priorityCounter++;
                } else {
                    processRegularDefinition(line);
                }
            } else {
                std::cout << "error in rules file";
            }
        }
        myfile.close();
    }
    clearSpecialSymbolsFromTerminals();
}

void RegularGrammar::processKeywords(string &line) {
    line = line.substr(1, line.find_last_of("}") - 1);
    trim(line);
    vector<string> tokens = splitWithRegexDelimiter(line, "[^\\s]+");
    for (vector<string>::size_type i = 0; i != tokens.size(); i++) {
        Symbol lhs(nonTerminal, tokens[i]);
        vector<Symbol> rhs;
        for (string::size_type j = 0; j < tokens[i].size(); j++) {
            Symbol x(terminal, tokens[i].substr(j, 1));
            rhs.push_back(x);
            terminals.insert(x);
        }
        nonTerminals.insert(lhs);
        Production production(lhs, rhs, 0);
        regularExpression.push_back(production);
    }
}

void RegularGrammar::processPunctuation(string &line) {
    line = line.substr(1, line.find_last_of("]") - 1);
    vector<string> tokens = splitWithRegexDelimiter(line, "[^\\s]+");
    for (vector<string>::size_type i = 0; i != tokens.size(); i++) {
        string leftSide;
        vector<Symbol> rhs;
        for (string::size_type j = 0; j < tokens[i].size(); j++) {
            if (tokens[i][j] == '\\') {
                j++;
            }
            leftSide += tokens[i][j];
            Symbol x(terminal, tokens[i].substr(j, 1));
            rhs.push_back(x);
            terminals.insert(x);
        }
        Symbol lhs(nonTerminal, leftSide);
        nonTerminals.insert(lhs);
        Production production(lhs, rhs, 0);
        regularExpression.push_back(production);
    }
}

vector<Symbol> RegularGrammar::processNonSpecial(const string &str) {
    Symbol temp(nonTerminal, str);
    vector<Symbol> ans;
    if (nonTerminals.find(temp) != nonTerminals.end()) {
        vector<Symbol> nonTerminalValue = (*regularDefinition.find(temp)).second;
        ans.push_back(Symbol(special, "("));
        copy(nonTerminalValue.begin(), nonTerminalValue.end(), back_inserter(ans));
        ans.push_back(Symbol(special, ")"));
    } else {
        for (int i = 0; i < str.size(); ++i) {
            Symbol currentSymbol(terminal, str.substr(i, 1));
            ans.push_back(currentSymbol);
        }
    }
    return ans;
}

///
/// \param index  change it to the last processed character
/// \return
vector<Symbol> RegularGrammar::processSpecial(const string &str, int &index) {
    vector<Symbol> result;
    if (str[index] == ' ' || str[index] == '\t') {
        //skip white spaces
    } else if (str[index] == '+' || str[index] == '*' || str[index] == '(' || str[index] == ')' || str[index] == '|') {
        result.push_back(Symbol(special, string(1, str[index])));
    } else if (str[index] == '-') {
        result = substituteRange(str, index);
    } else if (str[index] == '\\') {
        if (str[index + 1] == 'L') {
            result.push_back(Symbol(special, "L"));
        } else {
            result.push_back(Symbol(terminal, string(1, str[index + 1])));
        }
        index++;
    }
    return result;
}

vector<Symbol> RegularGrammar::substituteRange(const string &str, int &index) {
    vector<Symbol> result;
    char start, end;
    int startIndex = index - 1;
    while (str[startIndex] == ' ')
        startIndex--;
    start = str[startIndex] + 1;
    int endIndex = index + 1;
    while (str[endIndex] == ' ')
        endIndex++;
    end = str[endIndex];
    for (; start < end; ++start) {
        result.push_back(Symbol(special, "|"));

        result.push_back(Symbol(terminal, string(1, start)));
    }
    result.push_back(Symbol(special, "|"));
    return result;
}

void RegularGrammar::processRegularDefinition(string &line) {
    string leftSide = line.substr(0, line.find("="));
    trim(leftSide);
    Symbol lhs(nonTerminal, leftSide);
    nonTerminals.insert(lhs);
    string rightSide = line.substr(line.find_first_of("=") + 1);
    vector<Symbol> rhs = processRHS(rightSide);
    copy(rhs.begin(), rhs.end(), std::inserter(terminals, terminals.end()));
    regularDefinition.insert(pair<Symbol, vector<Symbol>>(lhs, rhs));
}

void RegularGrammar::processExpression(string &line, int priority) {
    string leftSide = line.substr(0, line.find(":"));
    trim(leftSide);
    Symbol lhs(nonTerminal, leftSide);
    nonTerminals.insert(lhs);
    string rightSide = line.substr(line.find_first_of(":") + 1);
    vector<Symbol> rhs = processRHS(rightSide);
    copy(rhs.begin(), rhs.end(), std::inserter(terminals, terminals.end()));
    regularExpression.push_back(Production(lhs, rhs, priority));
}

vector<Symbol> RegularGrammar::processRHS(string &rightSide) {
    trim(rightSide);
    vector<Symbol> rhs;
    int symbolStart = 0, index = 0;  //loop on right hand side
    while (index < rightSide.size()) {
        if (isDelimiter(rightSide[index])) {
            vector<Symbol> symbols = processNonSpecial(rightSide.substr(symbolStart, index - symbolStart));
            copy(symbols.begin(), symbols.end(), back_inserter(rhs));
            symbols = processSpecial(rightSide, index);
            copy(symbols.begin(), symbols.end(), back_inserter(rhs));
            symbolStart = index + 1;
        }
        index++;
    }
    vector<Symbol> symbols = processNonSpecial(rightSide.substr(symbolStart));
    copy(symbols.begin(), symbols.end(), back_inserter(rhs));
    return rhs;
}

void RegularGrammar::clearSpecialSymbolsFromTerminals() {
    for(auto f : terminals) {
        if(f.type == terminal){
            terminals.erase(f);
        }
    }
}
