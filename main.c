#include "listOfTeams.h"

// void readingData();
int main()
{
    int numberOfTeams, positionOfLastRequest = 0;
    Team *listOfTeamsHead = NULL;
    FILE *teamsFiles, *requestFiles;
    printf("Insert the number of teams! \n");
    positionOfLastRequest = readTheRequests(&requestFiles, positionOfLastRequest);
    //scanf("%d", &numberOfTeams);
    readingData(positionOfLastRequest, &numberOfTeams, &teamsFiles, &listOfTeamsHead);
    printf("Sunt aici boss! \n");
    eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams);
    displayTheList(listOfTeamsHead);
    return 0;
}

