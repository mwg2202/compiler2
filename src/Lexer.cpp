#include "Lexer.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

Lexer::Lexer(CmdParser cmdParser): 
    cmdParserData(cmdParser.cmdParserData), cmdParser(cmdParser) {
    
    // Open the preprocessor output file
    std::ifstream inputFile(cmdParserData.preprocessorOutput);
    if (inputFile.fail()) cmdParser.PrintError(UNABLE_TO_OPEN, 
            cmdParserData.preprocessorOutput);

    // Create the tokenstream
    tokens = MakeTokenStream(inputFile);

    // Create the outputFile
    std::ofstream outputFile(cmdParserData.outputTokenStream);
    if (outputFile.fail()) cmdParser.PrintError(UNABLE_TO_OPEN,
        cmdParserData.outputTokenStream);

    // Print the token stream to the file
    PrintToFile(tokens, outputFile);
    return;
}

// Returns a token stream created out of the inputFile
std::vector<Token> Lexer::MakeTokenStream(std::ifstream &inputFile) {
    std::vector<Token> tokenStream;
    while (inputFile.peek() != EOF) {
        tokenStream.emplace_back(MakeToken(inputFile));
    }
    return tokenStream;
}

// Returns the next token in the input file stream
// (Moves the file stream to the end of the token in the process)
Token Lexer::MakeToken(std::ifstream &inputFile) {
    char currChar;
    inputFile.get(currChar);

    // If it is a digit
    if (isdigit(currChar)) {
        // Create the token's value
        std::string digitString;
        while (isdigit(currChar)) {
            digitString += currChar;
            inputFile.get(currChar);
        }

        // Create the return token
        Token returnToken (INT, digitString); 
        return returnToken;
    }

    // If it is a string
    if (currChar == '\"') {
        // Create the token's value
        std::string tokenValue;
        std::getline(inputFile, tokenValue, '\"');

        // Create the return token
        Token returnToken(STRING, tokenValue);
        return returnToken;
    }

    // If it is a char array
    if (currChar == '\'') {
        // Create the token's value
        std::string tokenValue;
        std::getline(inputFile, tokenValue, '\'');
        
        // Create the return token
        Token returnToken(CHAR, tokenValue);
        return returnToken;
    }
    
    // Characters not allowed in identifiers
    const std::string BannedCharacters = "(){}[];\n\t\" \'";

    // If we do not find a banned character, assume its the start
    // of an identifier
    if (BannedCharacters.find(currChar) == std::string::npos) {
        std::string tokenValue; 
        // Gather characters until we find an invalid one
        while(BannedCharacters.find(currChar) == std::string::npos) {
            tokenValue += currChar;
            inputFile.get(currChar);
        }
        Token returnToken(OPERATOR, tokenValue);
        return returnToken;
    }

    // Else, create the token using the following
    Token returnToken;
    switch (currChar) {
        case '(': returnToken.type = LP;        return returnToken;
        case ')': returnToken.type = RP;        return returnToken;
        case '{': returnToken.type = L3;        return returnToken;
        case '}': returnToken.type = R3;        return returnToken;
        case '[': returnToken.type = LB;        return returnToken;
        case ']': returnToken.type = RB;        return returnToken;
        case ';': returnToken.type = SC;        return returnToken;
        case '\n': returnToken.type = NEWLINE;  return returnToken;
        case ' ': return MakeToken(inputFile); // skip spaces
        default:
            std::string currCharString(1, currChar);
            cmdParser.PrintError(UNRECOGNIZED_CHAR, currCharString);
    }
    return returnToken;
}

// Print the token stream to a file
void Lexer::PrintToFile(std::vector<Token> &tokenStream, std::ofstream &outFile) {
    int i = 0;

    // Print each token to the file
    for (Token& token : tokenStream) {

        // Print the token number and type
        outFile << "Token #" << i << ": " << typeNames[token.type] << " ";
        
        // Print the token value depending on token type
        // (An int can't be printed the same way as a string)
        switch (token.type) {
            case CHAR:
                outFile << "\'" << token.matchedString << "\'\n";
                break;
            case STRING:
                outFile << "\"" << token.matchedString << "\"\n";
                break;
            case INT:
            case OPERATOR:
                outFile << token.matchedString << std::endl;
                break;
            default:
                outFile << "VOID" << std::endl;
                break;
        }
        i++;
    }
    return;
}
