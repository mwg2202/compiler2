#include "Lexer.hpp"
#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#define NULL2 (void *) NULL

Lexer::Lexer(CmdParser cmdParser): cmdParserData(cmdParser.cmdParserData) {
    
    FILE *preFile = fopen(cmdParserData.preprocessorOutput, "r");
    char currChar = '\0';
    int numTokens = 0;
    int status = 0;

    while (true) {
        status = fscanf(preFile, "%c", &currChar);
        if (status = EOF) break;

        if (isdigit(currChar)) {
            MakeStringToken(preFile, INT, '\'');
            numTokens++;
            continue;
        }

        switch (currChar) {
            case '\'': MakeStringToken(preFile, CHAR, '\''); break;
            case '\"': MakeStringToken(preFile, STRING, '\"'); break;
            case '.': tokens.emplace_back(PERIOD, NULL2); break;
            case ',': tokens.emplace_back(COMMA, NULL2); break;
            case '?': tokens.emplace_back(QMARK, NULL2); break;
            case '@': tokens.emplace_back(AT, NULL2); break;
            case '(': tokens.emplace_back(LP, NULL2); break;
            case ')': tokens.emplace_back(RP, NULL2); break;
            case '[': tokens.emplace_back(LB, NULL2); break;
            case ']': tokens.emplace_back(RB, NULL2); break;
            case '{': tokens.emplace_back(L3, NULL2); break;
            case '}': tokens.emplace_back(R3, NULL2); break;
            case ';': tokens.emplace_back(SC, NULL2); break;
            case ':': tokens.emplace_back(COLON, NULL2); break;
            case '+': tokens.emplace_back(PLUS, NULL2); break;
            case '-': tokens.emplace_back(MINUS, NULL2); break;
            case '/': tokens.emplace_back(DIVISION, NULL2); break;
            case '%': tokens.emplace_back(MODULO, NULL2); break;
            case '*': tokens.emplace_back(TIMES, NULL2); break;
            case '\t': tokens.emplace_back(TAB, NULL2); break;
            case ' ': tokens.emplace_back(SPACE, NULL2); break;
            case '\n': tokens.emplace_back(NEWLINE, NULL2); break;
            default:
                printf("Character not recognized by Lexer");
                break;
        }
        numTokens++;
    }

    if (cmdParserData.outputTokenStream != NULL) PrintToFile();

}

void Lexer::MakeStringToken(FILE *preFile, Type type, char testChar) {
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

    if (type != INT) {
        // Add the token to token stream
        tokens.emplace_back(type, (void *) charArray);
    } else {
        // Convert charArray to integer
        int *integer = new int;
        *integer = atoi(charArray);

        // Add the token to Token stream
        tokens.emplace_back(type, (void *) integer);

        // Delete charArray
        delete(charArray);
    }
}



void Lexer::PrintToFile() {
    FILE *outFile = fopen(cmdParserData.outputTokenStream, "w");
    int i = 0;
    for (auto token : tokens) {
        fprintf(outFile, "Token #%d %s ", i, typeName[token.type]);
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
}

const char *typeName[] = {
    "NONE", "SC", "COLON",
    "CHAR", "STRING", "INT",
    "PERIOD", "COMMA", "QMARK", "AT",
    "LP", "RP", "LB", "RB", "L3", "R3",
    "PLUS", "MINUS", "DIVISION", "MODULO", "TIMES",
    "TAB", "SPACE", "NEWLINE",
    "IDENTIFIER"
};
