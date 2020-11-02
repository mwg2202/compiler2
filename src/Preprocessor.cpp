#include <limits>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Preprocessor.hpp"

Preprocessor::Preprocessor(CmdParser cmdParser) 
    :cmdParserData(cmdParser.cmdParserData), cmdParser(cmdParser) {

    std::fstream inputFile(cmdParserData.inputFile);
    if (inputFile.fail()) cmdParser.PrintError(
            UNABLE_TO_OPEN, cmdParserData.inputFile);

    std::fstream outputFile(cmdParserData.preprocessorOutput,
            std::fstream::out);
    if (outputFile.fail()) cmdParser.PrintError(
            UNABLE_TO_OPEN, cmdParserData.preprocessorOutput);
    
    Parse(inputFile, outputFile);
    
    inputFile.close();
    outputFile.close();
    return;
}

void Preprocessor::Parse(std::fstream &inputFile, std::fstream &outputFile) {

    // Initiate variables
    char currChar = '\0';
    std::string directiveData;
    const std::string _include = "include";

    // Read each character
    while (inputFile.peek() != EOF) {
        inputFile.get(currChar);
        switch (currChar) {

            // Single Line Comments
            case '#':
                inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;

            // Multi-Line Comments
            case '~':
                inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '~');
                break;

            // Preprocessor Directive
            case '@':
                // Get the name of the directive
                getline(inputFile, directiveData, ' ');

                // If the name is include
                if (directiveData == "include") {
                    // Get the filename to include
                    inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '"');
                    getline(inputFile, directiveData, '"');
                    inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    // Open and parse the filename
                    std::fstream includeFile(directiveData);
                    Parse(includeFile, outputFile);

                } else cmdParser.PrintError(INVALID_DIRECTIVE, directiveData);
                break;

            default:
                outputFile << currChar;
                break;
        }
    }
}
