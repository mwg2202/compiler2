#pragma once
#include <stdlib.h>
struct CmdParserData {
    const char *inputFile = NULL;
    const char *outputFile = NULL;
    const char *includeDir = NULL;
    const char *outputTokenStream = NULL;
    char *preprocessorOutput = NULL;
};

class CmdParser {
    public:
        CmdParserData cmdParserData;

        // Parses the command line arguments and sets up cmdParserData
        CmdParser(const int, char *[]);
        inline void printHelpScreen();
        inline void printVersion();
};
