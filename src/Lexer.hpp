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

// A list of the type names 
// Used in Lexer::PrintToFile
const std::string typeNames[] = {
    "NONE", "SC",
    "CHAR", "STRING", "INT",
    "LP", "RP", "LB", "RB", "L3", "R3",
    "NEWLINE", "OPERATOR"
};

struct Token {
    Type type = NONE;
    std::string matchedString;

    inline Token(Type type, std::string &matchedString): 
        type(type), matchedString(matchedString) {}
    
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
