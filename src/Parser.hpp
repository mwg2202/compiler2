#pragma once
#include "CmdParser.hpp"
#include "Lexer.hpp"
#include <vector>

struct Node {
    std::string *name;
    Node *parentNode;
    std::vector<Node> childNodes;
    Token *token;
    inline Node(std::string name, Node *parentNode, Token *token): 
        parentNode(parentNode), token(token), name(name) {}
    
    inline Node(std::string name, Node *parentNode): 
        parentNode(parentNode), token((Token *) NULL), name(name) {}
}

class Parser {
    public:
        Node baseNode((Node *) NULL, (Token *) NULL); // Top node of the tree
    private:
        void Parse(std::vector<Token> &tokens);
        std::vector<Token> tokens;
};
