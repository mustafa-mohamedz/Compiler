cmake_minimum_required(VERSION 3.15)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(LexicalAnalyzer)

add_executable(Compiler
        LexicalAnalyzer/DFA.cpp
        LexicalAnalyzer/DFA.h
        LexicalAnalyzer/DFABuilder.cpp
        LexicalAnalyzer/DFABuilder.h
        LexicalAnalyzer/DFAState.cpp
        LexicalAnalyzer/DFAState.h
        LexicalAnalyzer/FinalNFA.cpp
        LexicalAnalyzer/FinalNFA.h
        LexicalAnalyzer/InputParser.cpp
        LexicalAnalyzer/InputParser.h
        LexicalAnalyzer/MinimizedDFA.cpp
        LexicalAnalyzer/MinimizedDFA.h
        LexicalAnalyzer/NFA.cpp
        LexicalAnalyzer/NFA.h
        LexicalAnalyzer/NFABuilder.cpp
        LexicalAnalyzer/NFABuilder.h
        LexicalAnalyzer/ProgramReader.cpp
        LexicalAnalyzer/ProgramReader.h
        LexicalAnalyzer/RegularGrammar.cpp
        LexicalAnalyzer/RegularGrammar.h
        LexicalAnalyzer/State.cpp
        LexicalAnalyzer/State.h
        main.cpp)
