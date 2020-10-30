#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include "CmdParser.hpp"

CmdParser::CmdParser (int argc, char *argv[]) {
    std::vector<std::string> argList(argv, argv + argc);
    Parse(argList);
}

CmdParser::Parse(std::vector<std::string> &argList) {

    bool inputFileSpecified = false; 
    bool preprocessorOutputSpecified = false;
        

    for (int i = 1; i < argc; i++) {
        if (argList[i][0] == '-') {

            switch (argList[i][1]) {
                
                case 'h':
                    PrintHelpScreen();
                    std::exit(1);
                
                case 'i':
                    if ((i < argc-1) && (argList[i+1][0] != '-')) 
                        cmdParserData.includeDir = argList[++i];
                    else PrintError(FLAG_REQUIRES_PARAMETER, argList[i]);
                    break;
                
                case 'o':
                    if ((i < argc - 1) && (argList [i+1][0] != '-')) 
                        cmdParserData.outputFile = argList[++i];
                    else PrintError(FLAG_REQUIRES_PARAMETER, argList[i]);
                    break;
                
                case 'p':
                    preprocessorOutputSpecified = true;
                    if ((i < argc-1) && (argList[i+1][0] != '-')) 
                        cmdParserData.preprocessorOutput = argList[++i];
                    else PrintError(FLAG_REQUIRES_PARAMETER, argList[i]);
                    break;

                case 't':
                    if ((i < argc-1) && (argList[i+1][0] != '-')) 
                        cmdParserData.outputTokenStream = argv[++i];
                    else PrintError(FLAG_REQUIRES_PARAMETER, argList[i]);
                    break;

                case 'v':
                    PrintVersion();
                    std::exit(1);
                
                default:
                    PrintError(CMDPARSER, ArgList[i]);
            }

        } else {
            inputFileSpecified = true;
            cmdParserData.inputFile = argList[i];
        }
    }

    if (!inputFileSpecified) PrintError(NO_INPUT_FILE);

    // If thee preprocessor output file wasn't specified just use inputFile.tmp
    if (!preprocessorOutputSpecified)
        cmdParserData.preprocessorOutput = cmdParserData.inputFile << ".tmp";
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
    Compiler Version: 0.02 (Nonfunctioning)
    Langugage Specification Version: 0

)~");
}

void PrintError(ErrorCode errorCode, std::string& errorString = "") {
    
    switch ErrorCode {

       // errorString can contain any string 
        case (NO_INPUT_FILE):
            std::cerr << "Error: no input file specified\n";
            std::exit(1);
        
        // errorString contains flag referenced
        case (FLAG_REQUIRES_PARAMETER):
            std::cerr << "Error: flag requires a paramater \'" << errorString << "\'\n";
            std::exit(1);
        
        // errorString contains flag referenced
        case (INVALID_FLAG):
            std::cerr << "Error: invalid flag \'" << errorString << "\'\n";
            std::exit(1);

        // errorString contains the filename
        case (UNABLE_TO_OPEN):
            std::cerr << "Error: unable to open file \"" << errorString << "\"\n";
            std::exit(1);
        case (INVALID_DIRECTIVE):
            std::cerr << "Error: invalid preprocessor directive \"" << errorString << "\"\n";
            std::exit(1);
        // errorString contains error message
        default:
            std::cerr << "Error: " << errorString << std::endl;
            break;
    
    }
}
