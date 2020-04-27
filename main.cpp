#include "LexicalAnalyzer.h"
#include "SyntaxParser.h"


using namespace std;

int main() {
    LexicalAnalyzer lexicalAnalyzer("..//LexicalRules.txt" , "..//program sample 1.txt");
    SyntaxParser syntax_parser(lexicalAnalyzer,"..//inputGrammar.txt");

    return 0;
}

