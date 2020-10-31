#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "CmdParser.hpp"
#include "Preprocessor.hpp"
#include "Lexer.hpp"

#include <cstring>

TEST_CASE ("Testing the Command Line Parser") {

    const int argcount = 10;
    const char *arguments[] = {"compile", "-t", "test.tokens", "-o", "test.out", "-p", "processed.out", "-i", "include", "test.code"};
    CmdParser cmdParser( argcount, (char **) arguments);
    REQUIRE(cmdParser.cmdParserData.inputFile == "test.code");
    REQUIRE(cmdParser.cmdParserData.outputFile == "test.out");
    REQUIRE(cmdParser.cmdParserData.includeDir == "include");
    REQUIRE(cmdParser.cmdParserData.outputTokenStream == "test.tokens");
    REQUIRE(cmdParser.cmdParserData.preprocessorOutput == "processed.out");

    SECTION("Testing the Preprocessor") {
        Preprocessor preprocessor(cmdParser);
        SECTION("Testing the Lexer") {
            Lexer lexer(cmdParser);
        }
    }
}
