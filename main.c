#include "matchesQueue.h"

int main()
{
    int numberOfTeams, positionOfLastRequest = 0, numberOfRounds = 1;
    Team *listOfTeamsHead = NULL, *listOfWinners = NULL;
    FILE *teamsFiles, *requestFiles, *outputFile;
    Stack *winnerStack = NULL, *loserStack = NULL;
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
    if(positionOfLastRequest == 2){
        openTheFile(&outputFile, "w", "r.out");
        eliminateTheTeamsUtil(&listOfTeamsHead, &numberOfTeams, &outputFile);
        displayTheList(listOfTeamsHead, &outputFile);
        closeTheFile(&outputFile);
    }
    if(positionOfLastRequest == 3){
        openTheFile(&outputFile, "w", "r.out");
        eliminateTheTeamsUtil(&listOfTeamsHead, &numberOfTeams, &outputFile);
        displayTheList(listOfTeamsHead, &outputFile);
        queueOfMatches = createTheQueue();
        enqueueUtil(queueOfMatches, listOfTeamsHead, &outputFile); 
        while(numberOfTeams > 1){
            if(numberOfTeams == 2){
                printf("Still in while duh....\n");
            }
            fprintf(outputFile, "---Round no:%d\n", numberOfRounds);  
            while(!isQueueOfMatchesEmpty(queueOfMatches)){
                QMatch *currentMatch = dequeueOfMatches(queueOfMatches, &winnerStack, &loserStack);
                fprintf(outputFile, "%s                -              %s\n", currentMatch -> firstTeam, currentMatch -> secondTeam);
            }
            if(numberOfTeams == 2){
                printf("Not yet...\n");
            }
            fprintf(outputFile, "\nWINNERS OF ROUND NO:%d\n", numberOfRounds);
            int counter = 1;
            queueOfMatches = createTheQueue();
            if(numberOfTeams == 2){
                printf("Duh...");
            }
            while(!isTheStackEmpty(winnerStack)){
                Stack *currentWinner = NULL, *currentWinnerOpponent = NULL;
                QMatch *scheduledMatch = (QMatch*)malloc(sizeof(QMatch));
                currentWinner = pop(&winnerStack);
                scheduledMatch -> firstTeam = (char*)malloc(sizeof(char) * (strlen(currentWinner -> nameOfTeam)+1));
                strcpy(scheduledMatch -> firstTeam, currentWinner -> nameOfTeam);
                if(!isTheStackEmpty(winnerStack)){
                    scheduledMatch -> firstTeamScore = currentWinner -> points;
                    currentWinnerOpponent = pop(&winnerStack);
                    scheduledMatch -> secondTeam = (char*)malloc(sizeof(char)*(strlen(currentWinnerOpponent -> nameOfTeam)+1));
                    strcpy(scheduledMatch -> secondTeam, currentWinnerOpponent -> nameOfTeam);
                    strcpy(scheduledMatch -> secondTeam, currentWinnerOpponent -> nameOfTeam);
                    scheduledMatch -> secondTeamScore = currentWinnerOpponent -> points;
                }
                //scheduledMatch -> secondTeam = (char*)malloc(sizeof(char)*(strlen(currentWinnerOpponent -> nameOfTeam)+1));
                //strcpy(scheduledMatch -> secondTeam, currentWinnerOpponent -> nameOfTeam);
                //scheduledMatch -> secondTeamScore = currentWinnerOpponent -> points;
                if(numberOfTeams >= 2){
                    fprintf(outputFile, "%s        - %f \n", currentWinner -> nameOfTeam, currentWinner -> points);
                    fprintf(outputFile, "%s        - %f \n", currentWinnerOpponent -> nameOfTeam, currentWinnerOpponent -> points);
                    enqueueTheMatch(queueOfMatches, scheduledMatch, &outputFile);
                }
                else{
                    fprintf(outputFile, "%s        - %f \n", currentWinner -> nameOfTeam, currentWinner -> points);
                }
            }
            printf("%d \n", numberOfTeams);
            numberOfRounds ++;
            numberOfTeams /= 2;
            fprintf(outputFile, "\n");
        }
    }
    return 0;
}

