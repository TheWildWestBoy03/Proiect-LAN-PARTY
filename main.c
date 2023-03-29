#include "matchesQueue.h"

int main()
{
    int numberOfTeams, positionOfLastRequest = 0, numberOfRounds = 1;
    Team *listOfTeamsHead = NULL;
    FILE *teamsFiles, *requestFiles, *outputFile;
    QueueOfMatches *queueOfMatches;
   // printf("Insert the number of teams! \n");
    positionOfLastRequest = readTheRequests(&requestFiles, positionOfLastRequest);
    readingData(positionOfLastRequest, &numberOfTeams, &teamsFiles, &listOfTeamsHead);
    //eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams);
    if(positionOfLastRequest == 1){
        openTheFile(&outputFile, "w", "r.out");
        displayTheList(listOfTeamsHead, &outputFile);
        closeTheFile(&outputFile);
    }
    if(positionOfLastRequest >= 2){
        openTheFile(&outputFile, "w", "r.out");
        eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams, &outputFile);
        displayTheList(listOfTeamsHead, &outputFile);
        closeTheFile(&outputFile);
    }
    if(positionOfLastRequest == 3){
        openTheFile(&outputFile, "w", "r.out");
        eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams, &outputFile);
        displayTheList(listOfTeamsHead, &outputFile);
        queueOfMatches = createTheQueue(queueOfMatches);
        enqueueUtil(queueOfMatches, listOfTeamsHead);
        fprintf(outputFile, "---Round no:%d", numberOfRounds); /*
        while(!isQueueOfMatchesEmpty(queueOfMatches)){
            QMatch *currentMatch = dequeueOfMatches(queueOfMatches);
            fprintf(outputFile, "%s                   -                %s \n", currentMatch -> firstTeam, currentMatch -> secondTeam);
        } 
        */
    }
    return 0;
}

