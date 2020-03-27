#include <iostream>
#include <NFABuilder.h>
#include <State.h>
#include <InputParser.h>
#include "LexicalAnalyzer/ProgramReader.h"

using namespace std;
//struct Node {
//    char data;
//    Node *left, *right;
//};
//
//void preOrder(Node* node)
//{
//    if (node == NULL)
//        return;
//    cout << node->data << endl;
//    preOrder(node->left);
//    preOrder(node->right);
//}
//int findIndex(string str, int si, int ei)
//{
//    if (si > ei)
//        return -1;
//
//    // Inbuilt stack
//    stack<char> s;
//
//    for (int i = si; i <= ei; i++) {
//
//        // if open parenthesis, push it
//        if (str[i] == '(')
//            s.push(str[i]);
//
//            // if close parenthesis
//        else if (str[i] == ')') {
//            if (s.top() == '(') {
//                s.pop();
//
//                // if stack is empty, this is
//                // the required index
//                if (s.empty())
//                    return i;
//            }
//        }
//    }
//    // if not found return -1
//    return -1;
//}
//
//// function to construct tree from string
//Node* getTree(string str, int si, int ei)
//{
//    //Base case
//    if (si > ei)
//        return NULL;
//
//    // root
//    Node* root = (Node*)malloc(sizeof(Node));
//    root->left = root->right = NULL;
//
//
//    int index = -1;
//
//    //Find index of root
//    if (si <= ei && str[si] == '(')
//        index = findIndex(str, si, ei) + 1;
//
//
//    // if index found
//    if (index != -1) {
//
//        root->data = str[index];
//
//        // call for left subtree
//        root->left = getTree(str, si + 1, index - 2);
//
//        // call for right subtree
//        root->right = getTree(str, index + 2, ei - 1);
//    }
//    else{
//        root->data = str[si];
//    }
//    return root;
//}

int main() {

    std::cout << "starting!!" << std::endl;
    RegularGrammar rg("..//Compiler//input sample 1.txt");
    InputParser parser(rg);

//    NFA result = parser.get_NFA();
//    DFA dfa(result);
//    ProgramReader pr("",dfa);


//    string str = "((a)|(b))|(c)";


//    Node* root = getTree(str, 0, str.length() - 1);
//    preOrder(root);




    set<Symbol> symbols = {Symbol(terminal, "a"), Symbol(terminal, "b"), Symbol(special, "L")};
    /*vector<Symbol> input = {Symbol(special, "("), Symbol(terminal, "a"),Symbol(special, "*"),
                            Symbol(special, "|"), Symbol(terminal, "b"),
                            Symbol(special, ")"), Symbol(special, "|"),
                            Symbol(terminal, "c"), Symbol(special, "*")};
*/
    vector<Symbol> input = {Symbol(terminal, "a"),Symbol(special, "+")};
    RegularGrammar r;
    Production p;
    Symbol lhs (nonTerminal, "test");
    p.LHS = lhs;
    p.RHS = input;

    r.regularExpression.push_back(p);
    r.terminals = symbols;
    InputParser parser1(r);
    vector<Production> v1 = parser1.postfix_productions;

    vector<NFA> result = parser1.get_NFA();

    result[0].printNFA(symbols);

    string str = "((a)|(b))|(c)";








    return 0;
}

