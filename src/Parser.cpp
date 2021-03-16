#include "Parser.hpp"
#include <iostream>

Parser::Parser(std::vector<Token> &tokens): tokens(tokens) {
    std::cout << "Parser Running\n";
    Parse(tokens, 0, baseNode);
}

// Simple Top-down parser
void Parser::Parse(std::vector<Token> &tokens, int i, Node &parentNode) {

    if (i >= tokens.size()) return;
    // Analyze the current token
    switch (tokens[i].type) {


        // Adds a semicolon terminal to the parent node's children
        case SC:
        case NEWLINE:
            parentNode.childNodes.emplace_back(typeNames[tokens[i].type], 
                    &parentNode);
            Parse(tokens, ++i, parentNode);
            return;


        // Creates an intermediary node with the name "expression".
        // It has no associated token and it's first child node is the
        // left curly-brackets/parenthesis
        case LP:
        case L3:

            // Create the Expression node
            parentNode.childNodes.emplace_back(
                    nodeNames[EXPRESSION],
                    &parentNode
            );

            // Create the first node under the expression node (LP or L3)
            // Note the expression node is "parentNode.childNodes.back()"
            parentNode.childNodes.back().childNodes.emplace_back(
                    typeNames[tokens[i].type],
                    &(parentNode.childNodes.back())
            );

            // Parse the next piece of the expression
            Parse(tokens, ++i, parentNode.childNodes.back());
            return;


        // Adds a RP or R3 terminal and backs out of the expression
        // if the current node wasn't in an expression return an error
        case RP:
        case R3:
            parentNode.childNodes.emplace_back(
                typeNames[tokens[i].type], 
                &parentNode
            );
            if (parentNode.childNodes[0].name != &typeNames[tokens[i].type]) {
                std::cerr << "Error: Unmatched right curly-bracket or parenthesis in expression \n";
                std::exit(1);
            }
            Parse(tokens, ++i, *parentNode.parentNode);
            return;

        case IDENTIFIER:
            // Create the Expression node
            parentNode.childNodes.emplace_back(
                nodeNames[EXPRESSION],
                &parentNode
            );

            // Create the first node under the expression node (IDENTIFIER)
            parentNode.childNodes.emplace_back(
                typeNames[tokens[i].type],
                &(parentNode.childNodes.back());
            );
        
        
        // Creates an intermediary node with the name "expression".
        // It has no associated token and it's first child node is the
        // left bracket
        case LB:
            // Create the List node
            parentNode.childNodes.emplace_back(
                    nodeNames[LIST],
                    &parentNode
            );

            // Create the first node under the expression node (LP or L3)
            // Note the expression node is "parentNode.childNodes.back()"
            parentNode.childNodes.back().childNodes.emplace_back(
                    typeNames[tokens[i].type],
                    &(parentNode.childNodes.back())
            );

            // Parse the next piece of the expression
            Parse(tokens, ++i, parentNode.childNodes.back());
            return;


        // Adds a RB terminal and backs out of the list
        // if the current node wasn't in an list return an error
        case RB:
            parentNode.childNodes.emplace_back(
                typeNames[tokens[i].type], 
                &parentNode
            );
            if (parentNode.name != nodeNames[LIST]) {
                std::cerr << "Error: Unmatched right bracket in list\n";
                std::exit(1);
            }
            Parse(tokens, ++i, *parentNode.parentNode);
            return;

        case FLOAT:
        case STRING:
        case CHAR:
        case INT:
            parentNode.childNodes.emplace_back(
                nodeNames[DATA],
                &parentNode
            );

            parentNode.childNodes.back().childNodes.emplace_back(
                typeNames[tokens[i].type],
                &parentNode.childNodes.back())
            );
            if (parentNode.name != nodeNames[ARGUMENT]) {
                std::cerr << "Error: Unexpected non-terminal \"DATA\"\n";
                std::exit(1);
            }
            Parse(tokens,++i, *parentNode.parentNode)

        // If it's not one of the above, it must be invalid
        default:
            std::cerr << "Error: Invalid token type: " 
                << typeNames[tokens[i].type] << "\n";
            std::exit(1);
    }
}


