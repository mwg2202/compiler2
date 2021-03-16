#pragma once
#include "CmdParser.hpp"
#include "Lexer.hpp"
#include "ParseTree.hpp"
#include <vector>

// If the node is a terminal node, the name is the token's appropriate value
// e.g. the stringValue for a STRING, the intValue converted to a string for an INT
enum class NodeName {
    EXPRESSION = 0,
    ARGUMENT,
    DATA,
    LIST
};

const std::string nodeNames[] = {
    "expression",
    "argument",
    "data",
    "list"
};


struct Node {
    
    inline Node(Node parentNode): 
        parentNode(parentNode) {std::cout << "Parsed: " << name << "\n";}
    inline Node(){}
};

class Parser {
    public:
        Parser(std::vector<Token>&);
        Node baseNode; // Top node of the tree
        std::vector<Token> tokens;

        void Parse(std::vector<Token> &tokens, int i, Node &parentNode);
};
