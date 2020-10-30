#include "Lexer.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

#define NULL2 (void *) NULL

Lexer::Lexer(CmdParser cmdParser): cmdParserData(cmdParser.cmdParserData) {
    
    // Open the preprocessor output file
    ifstream inputFile(cmdParserData.preprocessorOutput);
    if (inputFile.fail()) cmdParserData.PrintError(UNABLE_TO_OPEN, 
            cmdParserData.preprocessorOutput);

    // Create the tokenstream
    tokens = MakeTokenStream(inputFile)

    // Print the token stream to a file if requested by user
    if (cmdParserData.outputTokenStream != NULL) 
    // Create the outputFile
    ofstream outputFile(cmdParserData.outputTokenStream);
    if (outputFile.fail()) cmdParserData.PrintError(UNABLE_TO_OPEN,
        cmdParserData.outputTokenStream);

    // Print the token stream to the file
    PrintTokenStreamToFile(tokens, outputFile);
    return;
}

// Returns a token stream created out of the inputFile
std::vector<Token> MakeTokenStream(ifstream &inputFile) {
    while (!inputFile.eof()) {
        std::vector<Token> tokenStream;
        tokenStream.emplace_back(MakeToken(inputFile, tokenStream))
    }
}

// Returns the next token in the input file stream
// (Moves the file stream to the end of the token in the process)
Token Lexer::MakeToken(ifstream &inputFile) {
    char currChar;
    inputFile.get(currChar);

    // If it is a digit
    if (isdigit(currChar)) {
        // Create the token's value
        std::string digitString;
        while (isdigit(currChar)) digitString += currChar;

        // Create the return token
        Token returnToken (INT, digitString.stoi()); 
        return returnToken;
    }

    // If it is a string
    if (currChar == "\"") {
        // Create the token's value
        std::string tokenValue;
        inputFile.get(tokenValue, "\"");

        // Create the return token
        Token returnToken(STRING, tokenValue);
        return returnToken;
    }

    // If it is a char array
    if (currChar == "\'") {
        // Create the token's value
        std::string tokenValue;
        inputFile.get(tokenValue, "\'");
        
        // Create the return token
        Token returnToken(CHAR, tokenValue);
        return returnToken;
    }
    
    // Else, create the token using the following
    Token returnToken;
    switch (currChar) {
        case '.': returnToken.type = PERIOD;    return returnToken;
        case ',': returnToken.type = COMMA;     return returnToken;
        case '?': returnToken.type = QMARK;     return returnToken;
        case '@': returnToken.type = AT;        return returnToken;
        case '(': returnToken.type = LP;        return returnToken;
        case ')': returnToken.type = RP;        return returnToken;
        case '{': returnToken.type = L3;        return returnToken;
        case '}': returnToken.type = R3;        return returnToken;
        case ';': returnToken.type = SC;        return returnToken;
        case ':': returnToken.type = COLON;     return returnToken;
        case '+': returnToken.type = PLUS;      return returnToken;
        case '-': returnToken.type = MINUS;     return returnToken;
        case '/': returnToken.type = DIVISION;  return returnToken;
        case '%': returnToken.type = MODULO;    return returnToken;
        case '*': returnToken.type = TIMES;     return returnToken;
        case '\t': returnToken.type = TAB;      return returnToken;
        case ' ' : returnToken.type = SPACE;    return returnToken;
        case '\n': returnToken.type = NEWLINE;  return returnToken;
        default:
            returnToken.type = IDENTIFIER;
            inputFile.get(returnToken.stringValue, '(', ')', ' ');
            return returnToken;
            cmdParser.PrintError(UNRECOGNIZED_CHAR);
    }
}

// Print the token stream to a file
void Lexer::PrintToFile(std::vector<Token> &tokenStream, ofstream &outFile) {
    int i = 0;

    // Print each token to the file
    for (Token& token : tokenStream) {

        // Print the token number and type
        outFile << "Token #" << i << ": " << typeName[token.type];
        
        // Print the token value depending on token type
        // (An int can't be printed the same way as a string)
        switch (token.type) {
            case INT:
                outFile << *((int *) token.value) << std::endl;
            case CHAR:
                outFile << (char *) token.value << std::endl;
            case STRING:
                outFile << (char *) token.value << std::endl;
            default:
                outFile << "VOID" << std::endl;
        }
        i++;
    }
    return;
}

// A list of the type names 
// Used in Lexer::PrintToFile
const char *typeName[] = {
    "NONE", "SC", "COLON",
    "CHAR", "STRING", "INT",
    "PERIOD", "COMMA", "QMARK", "AT",
    "LP", "RP", "L3", "R3",
    "PLUS", "MINUS", "DIVISION", "MODULO", "TIMES",
    "TAB", "SPACE", "NEWLINE",
    "LIST", "IDENTIFIER"
};
