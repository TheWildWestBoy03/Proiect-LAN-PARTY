#include "listOfTeams.h"

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
    //eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams);
    if(positionOfLastRequest >= 1){
        openTheFile(&outputFile, "w", "r.out");
        displayTheList(listOfTeamsHead, &outputFile);
        /*
        if(positionOfLastRequest >= 2){
            fprintf(outputFile, "\n\n\n");
            eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams, &outputFile);
            displayTheList(listOfTeamsHead, &outputFile);
        }
        */
        closeTheFile(&outputFile);
    }
    
    return 0;
}

