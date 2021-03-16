#include "CmdParser.hpp"
#include "Preprocessor.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "CodeGenerator.hpp"

int main(int argc, char *argv[]) {
    auto cmdParser = CmdParser(argc, argv);
    auto lexer = Lexer(cmdParser);
    auto parser = Parser(lexer.tokens);
    // auto codeGenerator = CodeGenerator();
    return 0;
}
