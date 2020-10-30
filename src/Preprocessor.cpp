nclude <cstdio>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "Preprocessor.hpp"


Preprocessor::Preprocessor(CmdParser cmdParser)
    :cmdParserData(cmdParser.cmdParserData) {
   
    // Open the source file
    FILE *srcFile = fopen(cmdParserData.inputFile, "r");
    if (srcFile == NULL) {
        printf("Error: Unable to open file \"%s\"\n",cmdParserData.inputFile );
        std::exit(1);
    }

    // Open the preprocessor output file
    FILE *preFile = fopen(cmdParserData.preprocessorOutput, "w");

    // Initiate variables
    char currChar = '\0';
    char includeFile[255];
    unsigned long int currentLineNumber;
    char trash[31];
    char include[] = "include";

    // Read each character
    while (fscanf(srcFile, "%c", &currChar) != EOF) {
        
        switch (currChar) {

            // Single Line Comments
            case '#':
                while (fscanf(srcFile, "%c", &currChar) != EOF) {
                    if (currChar == '\n') break;
                }
                break;

            // Multi-Line Comments
            case '~':
                while (int notEOF = fscanf(srcFile, "%c", &currChar) != EOF) {
                    if (currChar == '~') break;
                    else if (!notEOF) {
                        printf("Error: Multi-line comment must end\n");
                        std::exit(1);
                    };
                }
                break;

            case '@':
                fscanf(srcFile, "%30s", trash);
                if (strcasecmp(trash, include) == 0) {
                    printf("Include was found for ");
                    if (fscanf(srcFile, "%s", includeFile) != 0) {
                        printf("%s\n", includeFile);
                    }
                }
                break;
            default:
                fprintf(preFile, "%c", currChar);
                break;
        }
    }
    fclose(srcFile);
    fclose(preFile);
}
