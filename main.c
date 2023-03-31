#include "BinarySearchTree.h"
#include "matchesQueue.h"

int main(int argc, char *argv[])
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
    positionOfLastRequest = readTheRequests(&requestFiles, positionOfLastRequest, argv);
    readingData(positionOfLastRequest, &numberOfTeams, &teamsFiles, &listOfTeamsHead, argv);
    // eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams);
    if (positionOfLastRequest == 1)
    {
        openTheFile(&outputFile, "w", argv[3]);
        displayTheList(listOfTeamsHead, &outputFile);
        closeTheFile(&outputFile);
    }
    if (positionOfLastRequest == 2)
    {
        openTheFile(&outputFile, "w", argv[3]);
        eliminateTheTeamsUtil(&listOfTeamsHead, &numberOfTeams, &outputFile);
        displayTheList(listOfTeamsHead, &outputFile);
        closeTheFile(&outputFile);
    }
    if (positionOfLastRequest >= 3)
    {
        openTheFile(&outputFile, "w", argv[3]);
        eliminateTheTeamsUtil(&listOfTeamsHead, &numberOfTeams, &outputFile);
        displayTheList(listOfTeamsHead, &outputFile);
        queueOfMatches = createTheQueue();
        enqueueUtil(queueOfMatches, listOfTeamsHead, &outputFile);
        fprintf(outputFile, "\n");
        while (numberOfTeams > 2)
        {
            printf("%d \n", numberOfTeams);
            printf("where is the segmentation fault? \n");
            fprintf(outputFile, "--- ROUND NO:%d\n", numberOfRounds);
            while (!isQueueOfMatchesEmpty(queueOfMatches))
            {
                QMatch *currentMatch = dequeueOfMatches(queueOfMatches, &winnerStack, &loserStack);
                fprintf(outputFile, "%s", currentMatch->firstTeam);
                int index = strlen(currentMatch->firstTeam);
                while (index < 33)
                {
                    fprintf(outputFile, " ");
                    index++;
                }
                fprintf(outputFile, "-");
                while (index < 68 - strlen(currentMatch->secondTeam) - 2)
                {
                    fprintf(outputFile, " ");
                    index++;
                }
                fprintf(outputFile, "%s\n", currentMatch->secondTeam);
                // fprintf(outputFile, "%s                -              %s\n", currentMatch->firstTeam, currentMatch->secondTeam);
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
                int index = 0;
                fprintf(outputFile, "%s", currentWinner->nameOfTeam);
                index += strlen(currentWinner->nameOfTeam);
                while (index < 34)
                {
                    fputc(' ', outputFile);
                    index++;
                }
                fprintf(outputFile, "-  ");
                fprintf(outputFile, "%f\n", currentWinner->points);
                index = 0;
                fprintf(outputFile, "%s", currentWinnerOpponent->nameOfTeam);
                index += strlen(currentWinnerOpponent->nameOfTeam);
                while (index < 34)
                {
                    fputc(' ', outputFile);
                    index++;
                }
                fprintf(outputFile, "-");
                printf("aici este segfault?");
                fprintf(outputFile, "  %f\n", currentWinnerOpponent->points); 
                
              //  fprintf(outputFile, "%s        - %f \n", currentWinner->nameOfTeam, currentWinner->points);
              //  fprintf(outputFile, "%s        - %f \n", currentWinnerOpponent->nameOfTeam, currentWinnerOpponent->points);
                enqueueTheMatch(queueOfMatches, scheduledMatch, &outputFile);
            }

            numberOfRounds++;
            numberOfTeams /= 2;
            fprintf(outputFile, "\n");
        }
        finalMatch = dequeueOfMatches(queueOfMatches, &currentWinner, &currentWinnerOpponent);
        fprintf(outputFile, "--- ROUND NO:%d\n", numberOfRounds);
        int index = strlen(finalMatch->firstTeam);
        fprintf(outputFile, "%s", finalMatch->firstTeam);
        while (index < 33)
        {
            fputc(' ', outputFile);
            index++;
        }
        fprintf(outputFile, "-");
        while (index < 68 - strlen(finalMatch->secondTeam))
        {
            fputc(' ', outputFile);
            index++;
        }
        fprintf(outputFile, "%s\n", finalMatch->secondTeam);
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
        fprintf(outputFile, "\nWINNERS OF ROUND NO:%d\n", numberOfRounds);
        fprintf(outputFile, "%s", winnerOfTheGame->nameOfTeam);
        index = strlen(winnerOfTheGame->nameOfTeam);
        while (index < 34)
        {
            fputc(' ', outputFile);
            index++;
        }
        fprintf(outputFile, "-  ");
        fprintf(outputFile, "%f\n", winnerOfTheGame->points);
        if (positionOfLastRequest >= 4)
        {
            WinnersList *copy = gameWinners;
            while (copy != NULL)
            {
                binarySearchTreeRoot = addTeamInTree(binarySearchTreeRoot, copy->nameOfWinnersTeam, copy->points);
                copy = copy->next;
            }
            inorder(binarySearchTreeRoot, &outputFile);
        }
    }
    return 0;
}
