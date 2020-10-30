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
    REQUIRE(strcasecmp(cmdParser.cmdParserData.inputFile, "test.code") == 0);
    REQUIRE(strcasecmp(cmdParser.cmdParserData.outputFile, "test.out") == 0);
    REQUIRE(strcasecmp(cmdParser.cmdParserData.includeDir, "include") == 0);
    REQUIRE(strcasecmp(cmdParser.cmdParserData.outputTokenStream, "test.tokens") == 0);
    REQUIRE(strcasecmp(cmdParser.cmdParserData.preprocessorOutput, "processed.out") == 0);

}

/*
TEST_CASE ("Testing the Preprocessor") {
    Preprocessor preprocessor (cmdparser);
}

TEST_CASE ("Testing the Lexer") {
    Lexer lexer = (cmdparser);
}

*/
