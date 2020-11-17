#pragma once
#include <iostream>
#include <vector>
#include <string>

enum ErrorCode {
    NO_INPUT_FILE,
    INVALID_FLAG,
    FLAG_REQUIRES_PARAMETER,
    COMMENT_MUST_END,
    INVALID_DIRECTIVE,
    INCOMPLETE_ARRAY,
    UNABLE_TO_OPEN,
    UNRECOGNIZED_CHAR,
    MULTIPLE_PERIODS
};

struct CmdParserData {
    std::string inputFile;
    std::string outputFile;
    std::string includeDir;
    std::string outputTokenStream;
    std::string preprocessorOutput;
};

class CmdParser {
    public:
        CmdParserData cmdParserData;
        CmdParser(int argc, char *argv[]);

        void Parse(const std::vector<std::string> &);
        void PrintHelpScreen();
        void PrintVersion();
        void PrintError(const ErrorCode, const std::string &);
};

