#include "listOfTeams.h"
void openTheFile(FILE **inputFile, char *mode, char *nameOfFile)
{
    if ((*inputFile = fopen(nameOfFile, mode)) == NULL)
    {
        printf("Can not open this file.");
        exit(1);
    }
}

void closeFile(FILE **inputFile)
{
    fclose(*inputFile);
}
int readTheRequests(FILE **requestsFile, int positionOfTheLastRequest)
{
    int check;
    openTheFile(&*requestsFile, "wt", "c.in");
    while (feof(*requestsFile) == 0 && fscanf(*requestsFile, "%d ", &check))
    {
        if (check == 0)
        {
            break;
        }
        positionOfTheLastRequest++;
    }
    closeFile(&*requestsFile);
    return positionOfTheLastRequest;
}

void readingData(int lastRequest, int *numberOfTeams, FILE **teamsFile, Team **listOfTeamsHead)
{
    FILE *copyOfTheFile = *teamsFile;
    if (lastRequest == 0)
    {
        printf("You don't have any requests. Please change your input.");
        exit(1);
    }
    else
    {
        openTheFile(&copyOfTheFile, "wt", "d.in");
        printf("Please insert the number of teams: ");
        fscanf(*teamsFile, "%d", *numberOfTeams);
        addTheTeams(&*listOfTeamsHead, *numberOfTeams, *teamsFile);
    }
}
