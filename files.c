#include "listOfTeams.h"
void openTheFile(FILE **inputFile, char *mode, char *nameOfFile)
{
    if ((*inputFile = fopen(nameOfFile, mode)) == NULL)
    {
        printf("Can not open this file.");
        exit(1);
    }
}

void closeTheFile(FILE **inputFile)
{
    fclose(*inputFile);
}
int readTheRequests(FILE **requestsFile, int positionOfTheLastRequest, char *argv[])
{
    int check;
    openTheFile(&*requestsFile, "r", argv[1]);
    while (feof(*requestsFile) == 0 && fscanf(*requestsFile, "%d ", &check))
    {
        if (check == 0)
        {
            break;
        }
        positionOfTheLastRequest++;
    }
    closeTheFile(&*requestsFile);
    return positionOfTheLastRequest;
}

void readingData(int lastRequest, int *numberOfTeams, FILE **teamsFile, Team **listOfTeamsHead, char *argv[])
{
    FILE *copyOfTheFile = *teamsFile;
    if (lastRequest == 0)
    {
        printf("You don't have any requests. Please change your input.");
        exit(1);
    }
    else
    {
        openTheFile(&copyOfTheFile, "rt", argv[2]);
        fscanf(copyOfTheFile, "%d\n", numberOfTeams);
        addTheTeams(&*listOfTeamsHead, *numberOfTeams, copyOfTheFile);
        closeTheFile(&copyOfTheFile);
    }
}
