#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include "CmdParser.hpp"

CmdParser::CmdParser( const int argc, char *argv[]) {
    
    char *currArg = NULL;
    bool inputFileSpecified = false; 
    bool preprocessorOutputSpecified = false;
        
    for (int i = 1; i < argc; i++) {
        currArg = argv[i];
        if (currArg[0] == '-') {

            switch (currArg[1]) {
                case 'h':
                    printHelpScreen();
                    std::exit(1);
                case 'i':
                    if (i < argc - 1) cmdParserData.includeDir = argv[i+1];
                    else {
                        printf("Error: \"-%c\" flag requires a parameter\n", currArg[1]);
                        std::exit(1);
                    };
                    break;
                case 'o':
                    if (i < argc - 1) cmdParserData.outputFile = argv[i+1];
                    else {
                        printf("Error: \"-%c\" flag requires a parameter\n", currArg[1]);
                        exit(1);
                    };
                    break;
                case 'p':
                    preprocessorOutputSpecified = true;
                    if (i < argc - 1) cmdParserData.preprocessorOutput = argv[++i];
                    else {
                        printf("Error: \"-%c\" flag requires a parameter\n", currArg[1]);
                        exit(1);
                    }
                    break;
                case 't':
                    if (i < argc - 1) cmdParserData.outputTokenStream = argv[++i];
                    else {
                        printf("Error: \"-%c\" flag requires a parameter\n", currArg[1]);
                        exit(1);
                    }
                    break;

                case 'v':
                    printVersion();
                    std::exit(1);
                default:
                    printf("Error: \"-%c\" invalid flag\n", currArg[1]);
                    std::exit(1);
            }

        } else {
            inputFileSpecified = true;
            cmdParserData.inputFile = argv[i];
        }
    }

    if (!inputFileSpecified) {
        printf("Error: no input file specified\n");
        exit(1);
    }

    if (!preprocessorOutputSpecified) {
        char ending[] = ".tmp";
        cmdParserData.preprocessorOutput = new char[strlen(cmdParserData.inputFile) + 4];
        strcpy(cmdParserData.preprocessorOutput, cmdParserData.inputFile);
        strcat(cmdParserData.preprocessorOutput, ending);
    }
}

void CmdParser::printHelpScreen() {
    printf(R"~(
Usage: ./a.out [options] file...
Compiles source code to an executable

Options:
    -h, --help                      Display this information
    -i, --includeDir <directory>    Sets the directory to include files
    -o, --output <file>             Sets the location of the output executable
    -p, --preprocessor <file>       Saves the preprocessed file
    -v, --version                   Displays the compiler version
    -t, --token <file>              Prints the token stream to a file

)~");
}

void CmdParser::printVersion() {
    printf( R"~(
    Compiler Version: 0.01 (Nonfunctioning)
    Langugage Specification Version: 0

)~");
}
