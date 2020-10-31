#pragma once
#include "CmdParser.hpp"
#include <fstream>
#include <vector>

enum Type {
    NONE = 0, SC,
    CHAR, STRING, INT,
    LP, RP, LB, RB, L3, R3, 
    NEWLINE, OPERATOR 
};

struct Token {
    Type type = NONE;
    std::string stringValue;
    int intValue;

    inline Token(Type type, std::string stringValue): 
        type(type), stringValue(stringValue) {}
    
    inline Token(Type type, int intValue):
        type(type), intValue(intValue) {}
    
    inline Token() {}
};

class Lexer {
    public:
        std::vector<Token> tokens;
        CmdParserData cmdParserData; 
        CmdParser cmdParser;

        // Reads the file and turns the text into a stream of tokens
        Lexer(CmdParser);
        std::vector<Token> MakeTokenStream(std::ifstream &);
        Token MakeToken(std::ifstream &);
        
        void PrintToFile(std::vector<Token> &, std::ofstream &);
};

extern const char *typeName[];
