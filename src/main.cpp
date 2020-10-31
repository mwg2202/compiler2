#include "CmdParser.hpp"
#include "Preprocessor.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int main(int argc, char *argv[]) {
    CmdParser cmdParser(argc, argv);
    Preprocessor preprocessor(cmdParser);
    Lexer lexer(cmdParser);
    return 0;
}
