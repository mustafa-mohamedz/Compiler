#include "ProgramReader.h"

ProgramReader::ProgramReader(const std::string& programPath, const MinimizedDFA& dfa) {
    this->tokenIndex = 0;
    std::string line;
    std::ifstream myFile(programPath);
    if (myFile.is_open()) {
        while (getline(myFile, line)) {
            trim(line);
            vector<string> stringBlock = splitWithRegexDelimiter(line, "[^\\s]+");
            for (vector<string>::size_type i = 0; i != stringBlock.size(); i++) {
                vector<Token> someTokens = processStringBlock(stringBlock[i], dfa);
                copy(someTokens.begin(), someTokens.end(), back_inserter(this->tokenList));
            }
        }
        myFile.close();
    }
}

vector<Token> ProgramReader::processStringBlock(const std::string &stringBlock, const MinimizedDFA &dfa) {
    vector<Token> result;
    std::string::size_type currentStart = 0, nextStart = 0;
    while(currentStart < stringBlock.size()){
        int currentStateId = dfa.startState;
        stack <int> history;
        history.push(currentStateId);
        //parse the whole stringBlock to get the final state
        for (std::string::size_type i = nextStart; i < stringBlock.size(); i++, nextStart++) {
            auto nextState = dfa.states[currentStateId].transitions.find(Symbol(terminal, std::string(1, stringBlock[i])));
            if(nextState == dfa.states[currentStateId].transitions.end()){
                break;
            }
            currentStateId = nextState->second;
            history.push(currentStateId);
        }
        //get the maximal munch
        int numOfUndoChars = 0;
        while(! history.empty() && !dfa.states[history.top()].is_accept){
            history.pop();
            numOfUndoChars++;
        }
        nextStart -= numOfUndoChars;

        std::string message;
        if(history.empty()){//could not accept any block
            nextStart = currentStart;//restart the nextStart pointer
            stringBlock.substr(currentStart,stringBlock.size() - currentStart);
            message = std::string("Error Can't process: ") + stringBlock.substr(currentStart,stringBlock.size() - currentStart) + " ,Skip the next character: " + stringBlock[nextStart] + "\n";
            //skip char and try to process again
            nextStart++;
        }else{//block accepted
            Production acceptedProduction = dfa.states[history.top()].accepted_production;
            result.push_back(Token(acceptedProduction.LHS.value,stringBlock.substr(currentStart,nextStart - currentStart)));
            message = acceptedProduction.LHS.value + " : " + stringBlock.substr(currentStart,nextStart - currentStart) + "\n";
        }
        logList.push_back(message);
        currentStart = nextStart;
    }
    return result;
}

vector<Token> ProgramReader::getTokens() {
    return this->tokenList;
}

bool ProgramReader::hasNextToken() {
    return this->tokenIndex < this->tokenList.size();
}

Token ProgramReader::getNextToken() {
    if(this->tokenIndex >= this->tokenList.size()){
        throw "No more Tokens";
    }
    return this->tokenList[this->tokenIndex++];
}

vector<string> ProgramReader::getLogMessages() {
    return logList;
}
