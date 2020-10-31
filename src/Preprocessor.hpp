#pragma once
#include "CmdParser.hpp"
#include "fstream"

class Preprocessor {
    public:
        CmdParserData cmdParserData;
        CmdParser cmdParser;
        // Reads the file and turns the text into a stream of tokens
        Preprocessor(CmdParser);
        void Parse(std::fstream &, std::fstream &);
};
