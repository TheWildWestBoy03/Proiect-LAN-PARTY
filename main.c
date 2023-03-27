#include "listOfTeams.h"

// void readingData();
int main()
{
    int numberOfTeams, positionOfLastRequest = 0;
    Team *listOfTeamsHead = NULL;
    FILE *teamsFiles, *requestFiles, *outputFile;
   // printf("Insert the number of teams! \n");
    positionOfLastRequest = readTheRequests(&requestFiles, positionOfLastRequest);
    //scanf("%d", &numberOfTeams);
    printf("%d \n", positionOfLastRequest);
    readingData(positionOfLastRequest, &numberOfTeams, &teamsFiles, &listOfTeamsHead);
    printf("Sunt aici boss! \n");
    eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams);
    if(positionOfLastRequest >= 0){
        openTheFile(&outputFile, "w", "r.out");
        displayTheList(listOfTeamsHead, &outputFile);
        closeTheFile(&outputFile);
    }
    return 0;
}

