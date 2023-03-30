#include "BinarySearchTree.h"
#include "matchesQueue.h"

int main()
{
    int numberOfTeams, positionOfLastRequest = 0, numberOfRounds = 1;
    Team *listOfTeamsHead = NULL, *listOfWinners = NULL;
    WinnersList *gameWinners = NULL, *currentWinnerInList = NULL;
    FILE *teamsFiles, *requestFiles, *outputFile;
    Stack *winnerStack = NULL, *loserStack = NULL, *currentWinner, *currentWinnerOpponent, *winnerOfTheGame = NULL;
    Stack *currentLoser = NULL, *currentLoserOpponent = NULL;
    QueueOfMatches *queueOfMatches;
    QMatch *finalMatch = NULL, *scheduledMatch = NULL;
    WinnersTree *binarySearchTreeRoot = NULL;
    // printf("Insert the number of teams! \n");
    positionOfLastRequest = readTheRequests(&requestFiles, positionOfLastRequest);
    readingData(positionOfLastRequest, &numberOfTeams, &teamsFiles, &listOfTeamsHead);
    // eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams);
    if (positionOfLastRequest == 1)
    {
        openTheFile(&outputFile, "w", "r.out");
        displayTheList(listOfTeamsHead, &outputFile);
        closeTheFile(&outputFile);
    }
    if (positionOfLastRequest == 2)
    {
        openTheFile(&outputFile, "w", "r.out");
        eliminateTheTeamsUtil(&listOfTeamsHead, &numberOfTeams, &outputFile);
        displayTheList(listOfTeamsHead, &outputFile);
        closeTheFile(&outputFile);
    }
    if (positionOfLastRequest >= 3)
    {
        openTheFile(&outputFile, "w", "r.out");
        eliminateTheTeamsUtil(&listOfTeamsHead, &numberOfTeams, &outputFile);
        displayTheList(listOfTeamsHead, &outputFile);
        queueOfMatches = createTheQueue();
        enqueueUtil(queueOfMatches, listOfTeamsHead, &outputFile);
        while (numberOfTeams > 2)
        {
            fprintf(outputFile, "---Round no:%d\n", numberOfRounds);
            while (!isQueueOfMatchesEmpty(queueOfMatches))
            {
                QMatch *currentMatch = dequeueOfMatches(queueOfMatches, &winnerStack, &loserStack);
                fprintf(outputFile, "%s                -              %s\n", currentMatch->firstTeam, currentMatch->secondTeam);
            }
            fprintf(outputFile, "\nWINNERS OF ROUND NO:%d\n", numberOfRounds);
            queueOfMatches = createTheQueue();
            while (!isTheStackEmpty(winnerStack))
            {
                currentWinner = NULL, currentWinnerOpponent = NULL;
                scheduledMatch = (QMatch *)malloc(sizeof(QMatch));
                currentWinner = pop(&winnerStack);
                scheduledMatch->firstTeam = (char *)malloc(sizeof(char) * (strlen(currentWinner->nameOfTeam) + 1));
                strcpy(scheduledMatch->firstTeam, currentWinner->nameOfTeam);
                scheduledMatch->firstTeamScore = currentWinner->points;
                currentWinnerOpponent = pop(&winnerStack);
                if (numberOfTeams == 16)
                {
                    currentWinnerInList = (WinnersList *)malloc(sizeof(WinnersList));
                    currentWinnerInList->nameOfWinnersTeam = (char *)malloc(sizeof(char) * (strlen(currentWinner->nameOfTeam) + 1));
                    strcpy(currentWinnerInList->nameOfWinnersTeam, currentWinner->nameOfTeam);
                    currentWinnerInList->points = currentWinner->points;
                    addTheWinners(&gameWinners, currentWinnerInList);
                    currentWinnerInList = (WinnersList *)malloc(sizeof(WinnersList));
                    currentWinnerInList->points = currentWinnerOpponent->points;
                    currentWinnerInList->nameOfWinnersTeam = (char *)malloc(sizeof(char) * (strlen(currentWinnerOpponent->nameOfTeam) + 1));
                    strcpy(currentWinnerInList->nameOfWinnersTeam, currentWinnerOpponent->nameOfTeam);
                    addTheWinners(&gameWinners, currentWinnerInList);
                }
                scheduledMatch->secondTeam = (char *)malloc(sizeof(char) * (strlen(currentWinnerOpponent->nameOfTeam) + 1));
                strcpy(scheduledMatch->secondTeam, currentWinnerOpponent->nameOfTeam);
                scheduledMatch->secondTeamScore = currentWinnerOpponent->points;
                fprintf(outputFile, "%s        - %f \n", currentWinner->nameOfTeam, currentWinner->points);
                fprintf(outputFile, "%s        - %f \n", currentWinnerOpponent->nameOfTeam, currentWinnerOpponent->points);
                enqueueTheMatch(queueOfMatches, scheduledMatch, &outputFile);
            }
            numberOfRounds++;
            numberOfTeams /= 2;
            fprintf(outputFile, "\n");
        }
        finalMatch = dequeueOfMatches(queueOfMatches, &currentWinner, &currentWinnerOpponent);
        fprintf(outputFile, "Round no:%d\n", numberOfRounds);
        fprintf(outputFile, "%s          -              %s\n", finalMatch->firstTeam, finalMatch->secondTeam);
        winnerOfTheGame = (Stack *)malloc(sizeof(Stack));
        if (finalMatch->firstTeamScore > finalMatch->secondTeamScore)
        {
            winnerOfTheGame->next = NULL;
            winnerOfTheGame->nameOfTeam = (char *)malloc(strlen(finalMatch->firstTeam) + 1);
            strcpy(winnerOfTheGame->nameOfTeam, finalMatch->firstTeam);
            winnerOfTheGame->points = finalMatch->firstTeamScore + 1;
        }
        else
        {
            winnerOfTheGame->next = NULL;
            winnerOfTheGame->nameOfTeam = (char *)malloc(strlen(finalMatch->secondTeam) + 1);
            strcpy(winnerOfTheGame->nameOfTeam, finalMatch->secondTeam);
            winnerOfTheGame->points = finalMatch->secondTeamScore + 1;
        }
        fprintf(outputFile, "\nWINNERS OF ROUND NO:%d \n", numberOfRounds);
        fprintf(outputFile, "%s  - %f\n\n", winnerOfTheGame->nameOfTeam, winnerOfTheGame->points);

        WinnersList *copy = gameWinners;
        while (copy != NULL)
        {

            binarySearchTreeRoot = addTeamInTree(binarySearchTreeRoot, copy->nameOfWinnersTeam, copy->points);
            copy = copy->next;
        }
        inorder(binarySearchTreeRoot, &outputFile);
        printf("%p ", binarySearchTreeRoot);
    }
    return 0;
}
