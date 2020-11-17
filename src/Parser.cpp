#include "Parser.hpp"
#include <stdio>

// If the node is a terminal node, the name is the token's appropriate value
// e.g. the stringValue for a STRING, the intValue converted to a string for an INT
enum NodeName {
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


// Parses the given tokens
Parser::Parser(std::vector<Token> tokens): tokens(tokens) {
    Parse(tokens, 0, baseNode);
}

// Simple Top-down parser
void Parser::Parse(std::vector<Token> &tokens, int i, Node &parentNode) {
    
    // Analyze the current token
    switch (tokens[i].type) {


        // Adds a semicolon terminal to the parent node's children
        case SC:
            parentNode.childNode.emplace_back(typeNames[currToken.Type], 
                    &parentNode, &tokens[i]);
            return Parse(tokens, i++, (Token *) NULL);


        // Creates an intermediary node with the name "expression".
        // It has no associated token and it's first child node is the
        // left bracket/parenthesis
        case LP:
        case LB:
            parentNode.childNode.emplace_back(
                    nodeNames[EXPRESSION],
                    &parentNode
            );
            return Parse(tokens, i++, childNode);


        // Adds a RP or RB terminal and backs out of the expression
        // if the current node wasn't in an expression return an error
        case RP:
        case RB:
            parentNode.childNode.emplace_back(
                typeNames[currToken.type], 
                &parentNode
            );
            if (tokens[i].parentNode->childNode[0].name!=typeNames[currToken.type]) {
                std::cerr << "Error: Unmatched right bracket or parenthesis\n";
                std::exit(1);
            }
            return Parse(tokens, i++, token[i].parentNode->parentNode)

        // 

        // If it's not one of the above, it must be invalid
        default:
            std::cerr << "Error: Invalid token type\n";
    }
}
