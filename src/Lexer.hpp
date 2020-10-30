#pragma once
#include "CmdParser.hpp"
#include <cstdio>
#include <vector>

enum Type {
    NONE = 0, SC, COLON,
    CHAR, STRING, INT,
    PERIOD, COMMA, QMARK, AT,
    LP, RP, L3, R3, 
    PLUS, MINUS, DIVISION, MODULO, TIMES,
    TAB, SPACE, NEWLINE,
    LIST, IDENTIFIER
};

struct Token {
    Type type = NONE;
    union {
        std::string stringValue;
        int intValue;
    };

    inline Token(Type type, std::string stringValue): 
        type(type), stringValue(stringValue) {}
    
    inline Token(Type type, int intValue):
        type(type), intValue(intValue);
};

class Lexer {
    public:
        std::vector<Token> tokens;
        CmdParserData cmdParserData; 
        
        // Reads the file and turns the text into a stream of tokens
        Lexer(CmdParser);
        std::vector<Token> MakeTokenStream(ifstream &);
        Token MakeToken(ifstream &);
        
        void PrintToFile(std::vector<Token> &, ofstream &);
};

extern const char *typeName[];
