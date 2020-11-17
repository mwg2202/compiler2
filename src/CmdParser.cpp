#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include "CmdParser.hpp"

CmdParser::CmdParser (int argc, char *argv[]) {
    std::vector<std::string> argList(argv, argv + argc);
    Parse(argList);
}

void CmdParser::Parse(const std::vector<std::string> &argList) {

    bool inputFileSpecified = false; 
    bool preprocessorOutputSpecified = false;
        

    for (int i = 1; i < argList.size(); i++) {
        if (argList[i][0] == '-') {

            switch (argList[i][1]) {
                
                case 'h':
                    PrintHelpScreen();
                    std::exit(1);
                
                case 'i':
                    if ((i < argList.size() - 1) && (argList[i+1][0] != '-')) 
                        cmdParserData.includeDir = argList[++i];
                    else PrintError(FLAG_REQUIRES_PARAMETER, argList[i]);
                    break;
                
                case 'o':
                    if ((i < argList.size() - 1) && (argList[i+1][0] != '-')) 
                        cmdParserData.outputFile = argList[++i];
                    else PrintError(FLAG_REQUIRES_PARAMETER, argList[i]);
                    break;
                
                case 'p':
                    preprocessorOutputSpecified = true;
                    if ((i < argList.size() - 1) && (argList[i+1][0] != '-')) 
                        cmdParserData.preprocessorOutput = argList[++i];
                    else PrintError(FLAG_REQUIRES_PARAMETER, argList[i]);
                    break;

                case 't':
                    if ((i < argList.size() - 1) && (argList[i+1][0] != '-')) 
                        cmdParserData.outputTokenStream = argList[++i];
                    else PrintError(FLAG_REQUIRES_PARAMETER, argList[i]);
                    break;

                case 'v':
                    PrintVersion();
                    std::exit(1);
                
                default:
                    PrintError(INVALID_FLAG, argList[i]);
            }

        } else {
            inputFileSpecified = true;
            cmdParserData.inputFile = argList[i];
        }
    }
    
    std::string trash = "Hello";
    if (!inputFileSpecified) PrintError(NO_INPUT_FILE, trash);

    // If thee preprocessor output file wasn't specified just use inputFile.tmp
    if (!preprocessorOutputSpecified)
        cmdParserData.preprocessorOutput = cmdParserData.inputFile + ".tmp";
}

// Print the help screen
void CmdParser::PrintHelpScreen() {
    printf(R"~(
Usage: ./a.out [options] file...
Compiles source code to an executable

Options:
    -h, --help                      Display this information
    -i, --includeDir <directory>    Sets the directory to include files
    -o, --output <file>             Sets the location of the output executable
    -p, --preprocessor <file>       Saves the preprocessed file
    -t, --token <file>              Prints the token stream to a file
    -v, --version                   Displays the compiler version

)~");
}

// Print the version information
void CmdParser::PrintVersion() {
    printf( R"~(
    Compiler Version: 0.03 (Nonfunctioning)
    Langugage Specification Version: 0

)~");
}

void CmdParser::PrintError(const ErrorCode errorCode, const std::string &errorString) {
    
    switch (errorCode) {

       // errorString can contain any string 
        case (NO_INPUT_FILE):
            std::cerr << "Error: no input file specified\n";
            exit(1);
        
        // errorString contains flag referenced
        case (INVALID_FLAG):
            std::cerr << "Error: invalid flag \'" << errorString << "\'\n";
            exit(1);
        
        // errorString contains flag referenced
        case (FLAG_REQUIRES_PARAMETER):
            std::cerr << "Error: flag requires a paramater \'" << errorString << "\'\n";
            exit(1);

        // errorString contains trash
        case (COMMENT_MUST_END):
            std::cerr << "Error: multi-line comment must end\n";
            exit(1);

        // errorString contains the directive
        case (INVALID_DIRECTIVE):
            std::cerr << "Error: invalid preprocessor directive \"" << errorString << "\"\n";
            exit(1);

        // errorString contains trash
        case (INCOMPLETE_ARRAY):
            std::cerr << "Error: file ended in the middle of a character array or string\n";
            exit(1);
        
        // errorString contains the filename
        case (UNABLE_TO_OPEN):
            std::cerr << "Error: unable to open file \"" << errorString << "\"\n";
            exit(1);

        // errorString contains the unrecognized char
        case (UNRECOGNIZED_CHAR):
            std::cerr << "Error: lexer can not recognize \"" << errorString << "\"\n";
            exit(1);
        case (MULTIPLE_PERIODS):
            std::cerr << "Error: multiple periods were found in one float\n";
            exit(1);
        // errorString contains error message
        default:
            std::cerr << "Error: " << errorString << std::endl;
            exit(1); 
    }
}
