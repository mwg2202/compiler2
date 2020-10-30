#include "Lexer.hpp"
#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#define NULL2 (void *) NULL

Lexer::Lexer(CmdParser cmdParser): cmdParserData(cmdParser.cmdParserData) {
    
    // Open the preprocessor output file
    FILE *preFile = fopen(cmdParserData.preprocessorOutput, "r");
    char currChar = '\0';
    int status = 0;

    // Go through each character in the preprocessor output file
    while (true) {
        status = fscanf(preFile, "%c", &currChar);
        if (status = EOF) break;

        // Make the next token and put it on the token stream
        MakeToken(preFile, &tokens, currChar);
    }
    
    // Print the token stream to a file if requested by user
    if (cmdParserData.outputTokenStream != NULL) PrintToFile();
    return;
}


// Makes the token and puts it onto the tokensToEdit
void Lexer::MakeToken(FILE *preFile, std::vector<Token> *tokensToEdit, char currChar) {

    // If it is a digit, handle it
    if (isdigit(currChar)) {
        tokensToEdit->push_back(MakeStringToken(preFile, INT, '\''));
        return;
    }

    // If it is not a digit handle it
    switch (currChar) {
        // Special cases
        case '\'': tokensToEdit->push_back(MakeStringToken(preFile, CHAR, '\'')); break;
        case '\"': tokensToEdit->push_back(MakeStringToken(preFile, STRING, '\"')); break;
        case '[' : tokensToEdit->push_back(Lexer::ListToToken(preFile)); break;
        
        // Normal cases
        case '.': tokensToEdit->emplace_back(PERIOD, NULL2); break;
        case ',': tokensToEdit->emplace_back(COMMA, NULL2); break;
        case '?': tokensToEdit->emplace_back(QMARK, NULL2); break;
        case '@': tokensToEdit->emplace_back(AT, NULL2); break;
        case '(': tokensToEdit->emplace_back(LP, NULL2); break;
        case ')': tokensToEdit->emplace_back(RP, NULL2); break;
        case '{': tokensToEdit->emplace_back(L3, NULL2); break;
        case '}': tokensToEdit->emplace_back(R3, NULL2); break;
        case ';': tokensToEdit->emplace_back(SC, NULL2); break;
        case ':': tokensToEdit->emplace_back(COLON, NULL2); break;
        case '+': tokensToEdit->emplace_back(PLUS, NULL2); break;
        case '-': tokensToEdit->emplace_back(MINUS, NULL2); break;
        case '/': tokensToEdit->emplace_back(DIVISION, NULL2); break;
        case '%': tokensToEdit->emplace_back(MODULO, NULL2); break;
        case '*': tokensToEdit->emplace_back(TIMES, NULL2); break;
        case '\t': tokensToEdit->emplace_back(TAB, NULL2); break;
        case ' ' : tokensToEdit->emplace_back(SPACE, NULL2); break;
        case '\n': tokensToEdit->emplace_back(NEWLINE, NULL2); break;

        default:
            printf("Character not recognized by Lexer");
            break;
    }
}

// Turn list into a token
Token Lexer::ListToToken(FILE *preFile) {
    
    // Initialize variables
    char currChar = '\0';
    int status = 0;

    // Create a token vector that will be the value of the List
    std::vector<Token> *tokenVector = new std::vector<Token>;

    while (true) {
        status = fscanf(preFile, "%c", &currChar);

        if (currChar == ']') {
            Token *returnToken = new Token(LIST, tokenVector);
            return *returnToken;
        };

        MakeToken(preFile, tokenVector, currChar);
    }

    // Return a token with the information gathered
    Token *returnToken = new Token(LIST, (void *) tokenVector);
    return *returnToken;
}


// Makes the token for a string, char array, and integers once one of those is recognized
Token Lexer::MakeStringToken(FILE *preFile, Type type, char testChar) {
    
    // Define/Initialize needed variables
    char currChar = '\0';
    int status = 0;
    std::vector<char> charVector;
    
    while (true) {
        // Get a character
        status = fscanf(preFile, "%c", &currChar);

        // If the end of file is reached return an error
        if ((status == EOF) && (type != INT)) {
            printf("Error: File ended in the middle of a character array or string"); 
            exit(1);
        } else if (status == EOF) break;

        // If the closing character is reached, stop getting characters
        if (currChar == testChar ) break;

        if ((type == INT) && !isdigit(currChar)) break;

        // Add the character to the vector
        charVector.push_back(currChar);
    }

    // Create a char array to hold the token's value
    char * charArray = new char[charVector.size() + 1];

    // Copy over charVector to charArray
    int i = 0;
    for (auto x : charVector) {
        charArray[i] = x;
        i++;
    }
    charArray[i] = '\0';


    // Create the return token
    if (type != INT) {

        // Create the return token
        Token *returnToken = new Token(type, (void *) charArray);
        return *returnToken;

    } else {
        // Convert charArray to integer
        int *integer = new int;
        *integer = atoi(charArray);

        // Create the return token
        Token *returnToken = new Token(type, (void *) integer);

        // Delete charArray
        delete(charArray);
        return *returnToken;
    }

}


// Print the token stream to a file
void Lexer::PrintToFile() {

    // Open the output file
    FILE *outFile = fopen(cmdParserData.outputTokenStream, "w");
    int i = 0;

    // Print each token to the file
    for (auto token : tokens) {

        // Print the token number and type
        fprintf(outFile, "Token #%d %s ", i, typeName[token.type]);
        
        // Print the token value depending on token type
        // (An int can't be printed the same way as a string)
        switch (token.type) {
            case INT:
                fprintf(outFile, "%d", * ((int *) token.value));
            case CHAR:
                fprintf(outFile, "\'%s\'", (char *) token.value);
            case STRING:
                fprintf(outFile, "\"%s\"", (char *) token.value);
            default:
                fprintf(outFile, "VOID\n");
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
