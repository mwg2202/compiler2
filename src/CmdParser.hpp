#pragma once
#include <stdlib.h>
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

    private:
        inline void Parse(std::vector<std::string>&);
        inline void PrintHelpScreen();
        inline void PrintVersion();
        inline void PrintError(ErrorCode, std::string&);
};

enum ErrorCode {
    NO_INPUT_FILE,
    INVALID_FLAG,
    FLAG_REQUIRES_PARAMETER,
    INVALID_FILE,
    COMMENT_MUST_END,
    INVALID_DIRECTIVE
}
