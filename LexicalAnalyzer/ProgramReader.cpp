//#include "ProgramReader.h"
//
//ProgramReader::ProgramReader(const std::string& programPath, const DFA& dfa) {
//    this->tokenIndex = 0;
//    std::string line;
//    std::ifstream myFile(programPath);
//    if (myFile.is_open()) {
//        while (getline(myFile, line)) {
//            trim(line);
//            vector<string> stringBlock = splitWithRegexDelimiter(line, "[^\\s]+");
//            for (vector<string>::size_type i = 0; i != stringBlock.size(); i++) {
//                vector<Token> someTokens = processStringBlock(stringBlock[i], dfa);
//                copy(someTokens.begin(), someTokens.end(), back_inserter(this->tokenList ));
//            }
//        }
//        myFile.close();
//    }
//}
//
//vector<Token> ProgramReader::processStringBlock(const std::string &stringBlock, const DFA &dfa) {
//    vector<Token> result;
//    std::string::size_type currentStart = 0, currentEnd = 0;
//    while(currentStart < stringBlock.size()){
//        State currentState = dfa.start_state;
//        stack <State> history;
//        history.push(currentState);
//        //parse the whole stringBlock to get the final state
//        for (std::string::size_type i = currentEnd; i < stringBlock.size(); i++, currentEnd++) {
//            currentState = (currentState.transitions.find(Symbol(terminal,std::string(1, stringBlock[i])))->second)[0];
//            history.push(currentState);
//        }
//        //get the maximal munch
//        while(! history.empty() && history.top().type != State::accept){
//            history.pop();
//            currentEnd--;
//        }
//        //could not accept any block
//        if(history.empty()){
//            stringBlock.substr(currentStart,stringBlock.size() - currentStart);
//            std::cout << "Error Can't process: "<< stringBlock.substr(currentStart,stringBlock.size() - currentStart) << std::endl;
//            //skip char and try to process again
//            currentEnd++;
//        }else{//block accepted
//            Production acceptedProduction = history.top().accepted_production;
//            result.push_back(Token(acceptedProduction.LHS.value,stringBlock.substr(currentStart,currentEnd - currentStart)));
//        }
//        currentStart = currentEnd;
//    }
//    return result;
//}
//
//vector<Token> ProgramReader::getTokens() {
//    return this->tokenList;
//}
//
//bool ProgramReader::hasNextToken() {
//    return this->tokenIndex < this->tokenList.size();
//}
//
//Token ProgramReader::getNextToken() {
//    if(this->tokenIndex >= this->tokenList.size()){
//        throw "No more Tokens";
//    }
//    return this->tokenList[this->tokenIndex++];
//}