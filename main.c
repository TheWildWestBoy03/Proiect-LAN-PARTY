#include "listOfTeams.h"

int main()
{
    int numberOfTeams, positionOfLastRequest = 0;
    Team *listOfTeamsHead = NULL;
    FILE *teamsFiles, *requestFiles, *outputFile;
   // printf("Insert the number of teams! \n");
    positionOfLastRequest = readTheRequests(&requestFiles, positionOfLastRequest);
    readingData(positionOfLastRequest, &numberOfTeams, &teamsFiles, &listOfTeamsHead);
    //eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams);
    if(positionOfLastRequest == 1){
        openTheFile(&outputFile, "w", "r.out");
        displayTheList(listOfTeamsHead, &outputFile);
        closeTheFile(&outputFile);
    }
    if(positionOfLastRequest == 2){
        openTheFile(&outputFile, "w", "r.out");
        eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams, &outputFile);
        displayTheList(listOfTeamsHead, &outputFile);
        closeTheFile(&outputFile);
    }
    if(positionOfLastRequest == 3){
        openTheFile(&outputFile, "w", "r.out");
        eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams, &outputFile);
        displayTheList(listOfTeamsHead, &outputFile);
        createTheQueue();
    }
    
    return 0;
}

