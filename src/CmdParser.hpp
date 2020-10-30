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

        CmdParser(int argc, char *argv[]);

        inline void Parse(int argc, char *argv[]);
        inline void PrintHelpScreen();
        inline void PrintVersion();
};
