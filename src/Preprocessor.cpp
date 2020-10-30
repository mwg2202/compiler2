#include <cstdio>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Preprocessor.hpp"

Preprocessor::Preprocessor(CmdParser cmdParser)
    :cmdParserData(cmdParser.cmdParserData) {

    fstream inputFile(cmdParserData.inputFile);
    if (inputFile.fail()) cmdParser.PrintError(
            UNABLE_TO_OPEN, cmdParserData.inputFile);

    fstream outputFile(cmdParserData.preprocessorOutput);
    if (outputFile.fail()) cmdParser.PrintError(
            UNABLE_TO_OPEN, cmdParserData.preprocessorOutput);
    
    Parse(inputFile, outputFile);
    return;
}

void Preprocessor::Parse(fstream inputFile, fstream outputFile) {

    // Initiate variables
    char currChar = '\0';
    std::string directiveData;
    const std::string _include = "include";

    // Read each character
    while (srcFile.get(currChar)) {

        switch (currChar) {

            // Single Line Comments
            case '#':
                srcFile.ignore(numeric_limits<streamsize>::max(), '\n');
                break;

            // Multi-Line Comments
            case '~':
                srcFile.ignore(numeric_limits<streamsize>::max(), '~');
                break;

            // Preprocessor Directive
            case '@':
                // Get the name of the directive
                srcFile.get(directiveData, ' ');

                // If the name is include
                if (directiveData == "include") {
                    // Get the filename to include
                    srcFile.ignore(numeric_limits<streamsize>::max(), '"');
                    srcFile.get(directiveData, '"');
                    srcFile.ignore(numeric_limits<streamsize>::max(), '\n');

                    // Open and parse the filename
                    fstream includeFile(directiveData);
                    Prase(includeFile, inputFile);

                } else cmdParser.PrintError(INVALID_DIRECTIVE, directiveData);
                break;

            default:
                preFile << currChar;
                break;
        }
    }
    srcFile.close();
    preFile.close();
}
