#ifndef COMPILER_PROGRAMREADER_H
#define COMPILER_PROGRAMREADER_H

#include "DFA.h"

class ProgramReader {
public:
    //constructor
    ProgramReader(std::string programPath, DFA DeterministicAutomata);
};


#endif //COMPILER_PROGRAMREADER_H
