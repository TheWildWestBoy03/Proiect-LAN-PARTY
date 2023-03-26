#include "listOfTeams.h"
void openTheFile(FILE **inputFile, char *mode, char *nameOfFile){
    if( (*inputFile = fopen(nameOfFile, mode) ) == NULL){
        printf("Can not open this file.");
        exit(1);
    }
}

void closeFile(FILE **inputFile){
    fclose(*inputFile);
}