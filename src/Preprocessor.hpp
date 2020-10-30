#pragma once
#include "CmdParser.hpp"

class Preprocessor {
    public:
        CmdParserData cmdParserData;

        // Reads the file and turns the text into a stream of tokens
        Preprocessor(CmdParser);
        void Parse(fstream, fstream);
};
