#include "matchesQueue.h"

int main(int argc, char *argv[])
{
    int numberOfTeams, positionOfLastRequest = 0, numberOfRounds = 1;
    Team *listOfTeamsHead = NULL;
    WinnersList *gameWinners = NULL, *currentWinnerInList = NULL, *leaderboard = NULL;
    FILE *teamsFiles, *requestFiles, *outputFile;
    Stack *winnerStack = NULL, *loserStack = NULL, *winnerOfTheGame = NULL;
    QueueOfMatches *queueOfMatches;
    QMatch *finalMatch = NULL, *scheduledMatch = NULL;
    WinnersTree *binarySearchTreeRoot = NULL;
    Stack *currentWinner = NULL, *currentWinnerOpponent = NULL;
    AVLNode *avlRoot = NULL;
    openTheFile(&outputFile, "wt", argv[3]);
    positionOfLastRequest = readTheRequests(&requestFiles, positionOfLastRequest, argv);
    readingData(positionOfLastRequest, &numberOfTeams, &teamsFiles, &listOfTeamsHead, argv);
    // eliminateTheTeamsUtil(&listOfTeamsHead, numberOfTeams);
    if (positionOfLastRequest == 1)
    {
        solveFirstTask(&listOfTeamsHead, &outputFile);
    }
    if (positionOfLastRequest == 2)
    {
        solveSecondTask(&listOfTeamsHead, &outputFile, numberOfTeams);
    }
    if (positionOfLastRequest >= 3)
    {
        solveSecondTask(&listOfTeamsHead, &outputFile, numberOfTeams);
        queueOfMatches = createTheQueue();
        enqueueUtil(queueOfMatches, listOfTeamsHead, &outputFile);
        fprintf(outputFile, "\n");
        //listOfTeamsHead = deleteList(listOfTeamsHead);
        while (numberOfTeams > 2)
        {
            fprintf(outputFile, "--- ROUND NO:%d\n", numberOfRounds);
            while (!isQueueOfMatchesEmpty(queueOfMatches))
            {
                QMatch *currentMatch = dequeueOfMatches(queueOfMatches, &winnerStack, &loserStack);
                outputFile = printQueueLine(outputFile, currentMatch);
            }
            fprintf(outputFile, "\nWINNERS OF ROUND NO:%d\n", numberOfRounds);
            queueOfMatches = createTheQueue();
            while (!isTheStackEmpty(winnerStack))
            {
                printf("Sunt aici bro! \n");
                scheduledMatch = (QMatch *)malloc(sizeof(QMatch));
                currentWinner = pop(&winnerStack);
                currentWinnerOpponent = pop(&winnerStack);
                scheduledMatch->firstTeam = (char *)malloc(sizeof(char) * (strlen(currentWinner->nameOfTeam) + 1));
                strcpy(scheduledMatch->firstTeam, currentWinner->nameOfTeam);
                scheduledMatch->firstTeamScore = currentWinner->points;
                scheduledMatch->firstTeamPlayers = currentWinner->playersList;
                if (numberOfTeams == 16)
                {
                    printf("Sunt la 16 echipe ramase! \n");
                    //gameWinners = getTheWinners(gameWinners, currentWinner, currentWinnerOpponent); 
                    currentWinnerInList = (WinnersList *)malloc(sizeof(WinnersList));
                    currentWinnerInList->nameOfWinnersTeam = (char *)malloc(sizeof(char) * (strlen(currentWinner->nameOfTeam) + 1));
                    strcpy(currentWinnerInList->nameOfWinnersTeam, currentWinner->nameOfTeam);
                    currentWinnerInList->points = currentWinner->points;
                    currentWinnerInList->next = NULL;
                    addTheWinners(&gameWinners, currentWinnerInList);
                    currentWinnerInList = (WinnersList *)malloc(sizeof(WinnersList));
                    currentWinnerInList->points = currentWinnerOpponent->points;
                    currentWinnerInList->nameOfWinnersTeam = (char *)malloc(sizeof(char) * (strlen(currentWinnerOpponent->nameOfTeam) + 1));
                    currentWinnerInList->next = NULL;
                    strcpy(currentWinnerInList->nameOfWinnersTeam, currentWinnerOpponent->nameOfTeam);
                    addTheWinners(&gameWinners, currentWinnerInList);
                }
                scheduledMatch->secondTeam = (char *)malloc(sizeof(char) * (strlen(currentWinnerOpponent->nameOfTeam) + 1));
                strcpy(scheduledMatch->secondTeam, currentWinnerOpponent->nameOfTeam);
                scheduledMatch->secondTeamScore = currentWinnerOpponent->points;
                scheduledMatch->secondTeamPlayers = currentWinnerOpponent->playersList;
                scheduledMatch->next = NULL;
                outputFile = printStackLine(outputFile, currentWinner, currentWinnerOpponent);
                enqueueTheMatch(queueOfMatches, scheduledMatch, &outputFile);
            }
            numberOfRounds++;
            numberOfTeams /= 2;
            fprintf(outputFile, "\n");
        }
        finalMatch = dequeueOfMatches(queueOfMatches, &currentWinner, &currentWinnerOpponent);
        fprintf(outputFile, "--- ROUND NO:%d\n", numberOfRounds);
        outputFile = printQueueLine(outputFile, finalMatch);
        winnerOfTheGame = (Stack *)malloc(sizeof(Stack));
        if (finalMatch->firstTeamScore > finalMatch->secondTeamScore)
        {
            winnerOfTheGame->next = NULL;
            winnerOfTheGame->nameOfTeam = (char *)malloc(strlen(finalMatch->firstTeam) + 1);
            strcpy(winnerOfTheGame->nameOfTeam, finalMatch->firstTeam);
            winnerOfTheGame->points = finalMatch->firstTeamScore;
            winnerOfTheGame->playersList = finalMatch->firstTeamPlayers;
        }
        else
        {
            winnerOfTheGame->next = NULL;
            winnerOfTheGame->nameOfTeam = (char *)malloc(strlen(finalMatch->secondTeam) + 1);
            strcpy(winnerOfTheGame->nameOfTeam, finalMatch->secondTeam);
            winnerOfTheGame->points = finalMatch->secondTeamScore;
            winnerOfTheGame->playersList = finalMatch->secondTeamPlayers;
        }

        winnerOfTheGame->points = updateTheScore(&(winnerOfTheGame->playersList));
        winnerOfTheGame->points--;
        fprintf(outputFile, "\nWINNERS OF ROUND NO:%d\n", numberOfRounds);
        fprintf(outputFile, "%s", winnerOfTheGame->nameOfTeam);
        int index = strlen(winnerOfTheGame->nameOfTeam);
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
        }
        
        if(positionOfLastRequest >= 5){
            createTheLeaderboard(&leaderboard, binarySearchTreeRoot);
            WinnersList *copyOfLeaderboard = leaderboard;
            while (copyOfLeaderboard != NULL)
            {
                avlRoot = insertInAVL(avlRoot, copyOfLeaderboard->nameOfWinnersTeam, copyOfLeaderboard->points);
                copyOfLeaderboard = copyOfLeaderboard->next;
            }

            fprintf(outputFile, "\nTHE LEVEL 2 TEAMS ARE: \n%s\n", avlRoot->left->left->nameOfTeam);
            fprintf(outputFile, "%s\n", avlRoot->left->right->nameOfTeam);
            fprintf(outputFile, "%s\n", avlRoot->right->left->nameOfTeam);
            fprintf(outputFile, "%s", avlRoot->right->right->nameOfTeam);
        }
    }
    closeTheFile(&outputFile);
    return 0;
}
