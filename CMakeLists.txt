cmake_minimum_required(VERSION 3.15)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(LexicalAnalyzerGenerator)

add_executable(Compiler
        LexicalAnalyzerGenerator/DFA.cpp
        LexicalAnalyzerGenerator/DFA.h
        LexicalAnalyzerGenerator/DFABuilder.cpp
        LexicalAnalyzerGenerator/DFABuilder.h
        LexicalAnalyzerGenerator/DFAState.h
        LexicalAnalyzerGenerator/FinalNFA.cpp
        LexicalAnalyzerGenerator/FinalNFA.h
        LexicalAnalyzerGenerator/InputParser.cpp
        LexicalAnalyzerGenerator/InputParser.h
        LexicalAnalyzerGenerator/MinimizedDFA.cpp
        LexicalAnalyzerGenerator/MinimizedDFA.h
        LexicalAnalyzerGenerator/NFA.cpp
        LexicalAnalyzerGenerator/NFA.h
        LexicalAnalyzerGenerator/NFABuilder.cpp
        LexicalAnalyzerGenerator/NFABuilder.h
        LexicalAnalyzerGenerator/ProgramReader.cpp
        LexicalAnalyzerGenerator/ProgramReader.h
        LexicalAnalyzerGenerator/RegularGrammar.cpp
        LexicalAnalyzerGenerator/RegularGrammar.h
        LexicalAnalyzerGenerator/State.cpp
        LexicalAnalyzerGenerator/State.h
        main.cpp LexicalAnalyzer.cpp LexicalAnalyzer.h SyntaxAnalyzerGenerator/ContextFreeGrammar.cpp SyntaxAnalyzerGenerator/ContextFreeGrammar.h SyntaxAnalyzerGenerator/SyntaxAnalyzerUtilities.cpp SyntaxAnalyzerGenerator/SyntaxAnalyzerUtilities.h SyntaxAnalyzerGenerator/ParserTable.cpp SyntaxAnalyzerGenerator/ParserTable.h SyntaxParser.cpp SyntaxParser.h LexicalAnalyzerGenerator/Symbol.cpp LexicalAnalyzerGenerator/Symbol.h SyntaxAnalyzerGenerator/LL1GrammarConstructor.cpp SyntaxAnalyzerGenerator/LL1GrammarConstructor.h SyntaxAnalyzerGenerator/LLParser.cpp SyntaxAnalyzerGenerator/LLParser.h)
