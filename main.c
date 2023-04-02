#include "BinarySearchTree.h"
#include "matchesQueue.h"

int main(int argc, char *argv[])
{
    /*
    if(strcmp(argv[2], "date/t8/c.in") == 0){
        return 0;
    }*/
    static int i = 1;
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
    openTheFile(&outputFile, "at", argv[3]);
    positionOfLastRequest = readTheRequests(&requestFiles, positionOfLastRequest, argv);
    readingData(positionOfLastRequest, &numberOfTeams, &teamsFiles, &listOfTeamsHead, argv);
    // eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams);
    if (positionOfLastRequest == 1)
    {
        displayTheList(listOfTeamsHead, &outputFile);
        // closeTheFile(&outputFile);
    }
    if (positionOfLastRequest == 2)
    {
        eliminateTheTeamsUtil(&listOfTeamsHead, &numberOfTeams, &outputFile);
        displayTheList(listOfTeamsHead, &outputFile);
        // closeTheFile(&outputFile);
    }
    if (positionOfLastRequest >= 3)
    {
        eliminateTheTeamsUtil(&listOfTeamsHead, &numberOfTeams, &outputFile);
        displayTheList(listOfTeamsHead, &outputFile);
        queueOfMatches = createTheQueue();
        enqueueUtil(queueOfMatches, listOfTeamsHead, &outputFile);
        fprintf(outputFile, "\n");
        while (numberOfTeams > 2)
        {
            printf("%d \n", numberOfTeams);
            // printf("where is the segmentation fault? \n");
            fprintf(outputFile, "--- ROUND NO:%d\n", numberOfRounds);
            while (!isQueueOfMatchesEmpty(queueOfMatches))
            {
                QMatch *currentMatch = dequeueOfMatches(queueOfMatches, &winnerStack, &loserStack);
                printf("%s %s\n", currentMatch->firstTeam, currentMatch->secondTeam);
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
            }
            fprintf(outputFile, "\nWINNERS OF ROUND NO:%d\n", numberOfRounds);
            // printf("Is the queue empty? %d \n", isQueueOfMatchesEmpty(queueOfMatches));
            queueOfMatches = createTheQueue();
            /*
            while(!isTheStackEmpty(winnerStack)){
                Stack *curr = pop(&winnerStack);
                printf("%s \n", curr -> nameOfTeam);
            }
            return 0; */
            while (!isTheStackEmpty(winnerStack))
            {
                Stack *currentWinner = NULL, *currentWinnerOpponent = NULL;
                scheduledMatch = (QMatch *)malloc(sizeof(QMatch));
                currentWinner = pop(&winnerStack);
                currentWinnerOpponent = pop(&winnerStack);
                printf("Segfault? \n");
                printf("%d\n", i++);
                scheduledMatch->firstTeam = (char *)malloc(sizeof(char) * 100);
                strcpy(scheduledMatch->firstTeam, currentWinner->nameOfTeam);
                scheduledMatch->firstTeamScore = currentWinner->points;
                if (numberOfTeams == 16)
                {
                    currentWinnerInList = (WinnersList *)malloc(sizeof(WinnersList));
                    currentWinnerInList->nameOfWinnersTeam = (char *)malloc(sizeof(char) * 100);
                    strcpy(currentWinnerInList->nameOfWinnersTeam, currentWinner->nameOfTeam);
                    currentWinnerInList->points = currentWinner->points;
                    addTheWinners(&gameWinners, currentWinnerInList);
                    currentWinnerInList = (WinnersList *)malloc(sizeof(WinnersList));
                    currentWinnerInList->points = currentWinnerOpponent->points;
                    currentWinnerInList->nameOfWinnersTeam = (char *)malloc(sizeof(char) * 100);
                    strcpy(currentWinnerInList->nameOfWinnersTeam, currentWinnerOpponent->nameOfTeam);
                    addTheWinners(&gameWinners, currentWinnerInList);
                }
                // printf("Segfault after here? \n");
                // printf("%s \n", currentWinnerOpponent -> nameOfTeam);
                scheduledMatch->secondTeam = (char *)malloc(sizeof(char) * 100);
                strcpy(scheduledMatch->secondTeam, currentWinnerOpponent->nameOfTeam);
                // printf("%s \n", scheduledMatch -> secondTeam);
                // printf("Segfault after here? \n");
                scheduledMatch->secondTeamScore = currentWinnerOpponent->points;
                //  printf("Segfault after here? \n");
                // printf("%s %s \n", currentWinner -> nameOfTeam, currentWinnerOpponent -> nameOfTeam);
                int index = 0;
                fprintf(outputFile, "%s", currentWinner->nameOfTeam);
                //  printf("Segfault after here? \n");
                index += strlen(currentWinner->nameOfTeam);
                while (index < 34)
                {
                    fputc(' ', outputFile);
                    index++;
                }
                fprintf(outputFile, "-  %.2f\n", currentWinner->points);
                index = 0;
                fprintf(outputFile, "%s", currentWinnerOpponent->nameOfTeam);
                index += strlen(currentWinnerOpponent->nameOfTeam);
                while (index < 34)
                {
                    fputc(' ', outputFile);
                    index++;
                }
                fprintf(outputFile, "-  %.2f\n", currentWinnerOpponent->points);
                printf("Segfault after here? \n");
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
        while (index < 68 - strlen(finalMatch->secondTeam) - 2)
        {
            fputc(' ', outputFile);
            index++;
        }
        fprintf(outputFile, "%s\n", finalMatch->secondTeam);
        winnerOfTheGame = (Stack *)malloc(sizeof(Stack));
        if (finalMatch->firstTeamScore > finalMatch->secondTeamScore)
        {
            winnerOfTheGame->next = NULL;
            winnerOfTheGame->nameOfTeam = (char *)malloc(sizeof(char) * 100);
            strcpy(winnerOfTheGame->nameOfTeam, finalMatch->firstTeam);
            winnerOfTheGame->points = finalMatch->firstTeamScore + 1;
        }
        else
        {
            winnerOfTheGame->next = NULL;
            winnerOfTheGame->nameOfTeam = (char *)malloc(sizeof(char) * 100);
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
        fprintf(outputFile, "-  %.2f\n", winnerOfTheGame->points);
        if (positionOfLastRequest >= 4)
        {
            WinnersList *copy = gameWinners;
            fprintf(outputFile, "\nTOP 8 TEAMS:\n");
            while (copy != NULL)
            {
                binarySearchTreeRoot = addTeamInTree(binarySearchTreeRoot, copy->nameOfWinnersTeam, copy->points);
                copy = copy->next;
            }
            inorder(binarySearchTreeRoot, &outputFile);
            // closeTheFile(&outputFile);
        }
        else
        {
            // closeTheFile(&outputFile);
        }
    }
    // closeTheFile(&outputFile);
    return 0;
}
