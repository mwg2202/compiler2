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
    void *value = NULL;

    inline Token(Type type, void *value): 
        type(type), value(value) {}
};

class Lexer {
    public:
        std::vector<Token> tokens;
        CmdParserData cmdParserData; 
        
        // Reads the file and turns the text into a stream of tokens
        Lexer(CmdParser);
        void MakeToken(FILE*, std::vector<Token> &, char);
        Token ListToToken(FILE*);
        Token MakeStringToken(FILE*, Type, char);
        void PrintToFile();
};

extern const char *typeName[];
