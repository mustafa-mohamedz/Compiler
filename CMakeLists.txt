cmake_minimum_required(VERSION 3.15)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(LexicalAnalyzer)

add_executable(Compiler
    LexicalAnalyzer/DFA.cpp
    LexicalAnalyzer/DFA.h
    LexicalAnalyzer/NFA.cpp
    LexicalAnalyzer/NFA.h
    LexicalAnalyzer/ProgramReader.cpp
    LexicalAnalyzer/ProgramReader.h
    LexicalAnalyzer/RegularGrammar.cpp
    LexicalAnalyzer/RegularGrammar.h
    main.cpp)
