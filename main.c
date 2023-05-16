#include "matchesQueue.h"

void solveTheFirstTask(Team *listOfTeamsHead, FILE **outputFile){
    displayTheList(listOfTeamsHead, outputFile);
    listOfTeamsHead = deleteTheList(listOfTeamsHead);
    return;
}

void solveTheSecondTask(Team *listOfTeamsHead, FILE **outputFile, int numberOfTeams){
    eliminateTheTeamsUtil(&listOfTeamsHead, &numberOfTeams, outputFile);
    displayTheList(listOfTeamsHead, outputFile);
    listOfTeamsHead = deleteTheList(listOfTeamsHead);
    return;
}

void solveTheThirdTaskPt1(Team **listOfTeamsHead, FILE **outputFile, int *numberOfTeams){
    eliminateTheTeamsUtil(listOfTeamsHead, numberOfTeams, outputFile);
    displayTheList(*listOfTeamsHead, outputFile);
    return;
}
void printQueueLine(FILE **outputFile, QMatch *currentMatch){
    fprintf(*outputFile, "%s", currentMatch->firstTeam);
    int index = strlen(currentMatch->firstTeam);
    while (index < 33)
    {
        fprintf(*outputFile, " ");
        index++;
    }
    fprintf(*outputFile, "-");
    while (index < 68 - strlen(currentMatch->secondTeam) - 2)
    {
        fprintf(*outputFile, " ");
        index++;
    }
    fprintf(*outputFile, "%s\n", currentMatch->secondTeam);
    return;
}
void printStackLine(FILE **outputFile, Stack *currentWinner, Stack *currentWinnerOpponent){
    int index = 0;
    fprintf(*outputFile, "%s", currentWinner->nameOfTeam);
    index += strlen(currentWinner->nameOfTeam);
    while (index < 34)
    {
        fputc(' ', *outputFile);
        index++;
    }
    fprintf(*outputFile, "-  %.2f\n", currentWinner->points);
    index = 0;
    fprintf(*outputFile, "%s", currentWinnerOpponent->nameOfTeam);
    index += strlen(currentWinnerOpponent->nameOfTeam);
    while (index < 34)
    {
        fputc(' ', *outputFile);
        index++;
    }
    fprintf(*outputFile, "-  %.2f\n", currentWinnerOpponent->points);
}

WinnersList *addTheWInnersUtil(WinnersList *gameWinners, Stack *currentWinner, Stack *currentWinnerOpponent){
    WinnersList *WinnerTeamToAdd = (WinnersList*)malloc(sizeof(WinnersList));
    WinnerTeamToAdd -> nameOfWinnersTeam = (char*)malloc(strlen(currentWinner -> nameOfTeam) + 1);
    strcpy(WinnerTeamToAdd -> nameOfWinnersTeam, currentWinner -> nameOfTeam);
    WinnerTeamToAdd -> points = currentWinner -> points;
    WinnerTeamToAdd -> next = NULL;
    addTheWinners(&gameWinners, WinnerTeamToAdd);
    WinnerTeamToAdd = (WinnersList*)malloc(sizeof(WinnersList));
    WinnerTeamToAdd -> nameOfWinnersTeam = (char*)malloc(strlen(currentWinnerOpponent -> nameOfTeam) + 1);
    strcpy(WinnerTeamToAdd -> nameOfWinnersTeam, currentWinnerOpponent -> nameOfTeam);
    WinnerTeamToAdd -> points = currentWinnerOpponent -> points;
    WinnerTeamToAdd -> next = NULL;
    addTheWinners(&gameWinners, WinnerTeamToAdd);
    return gameWinners;
}

QMatch *prepairTheScheduledMatch(Stack *currentWinner, Stack *currentWinnerOpponent){
    QMatch *scheduledMatch = NULL;
    scheduledMatch = (QMatch *)malloc(sizeof(QMatch));
    scheduledMatch->firstTeam = (char *)malloc(sizeof(char) * (strlen(currentWinner->nameOfTeam) + 1));
    strcpy(scheduledMatch->firstTeam, currentWinner->nameOfTeam);
    scheduledMatch->firstTeamScore = currentWinner->points;
    scheduledMatch->firstTeamPlayers = currentWinner -> playersList;
    scheduledMatch->secondTeam = (char *)malloc(sizeof(char) * (strlen(currentWinnerOpponent->nameOfTeam) + 10));
    strcpy(scheduledMatch->secondTeam, currentWinnerOpponent->nameOfTeam);
    scheduledMatch->secondTeamScore = currentWinnerOpponent->points;
    scheduledMatch -> secondTeamPlayers = currentWinnerOpponent -> playersList;
    scheduledMatch -> next = NULL;
    return scheduledMatch;
}

void simulateTheGame(QueueOfMatches *queueOfMatches, FILE **outputFile, Team *listOfTeamsHead, int numberOfTeams, WinnersList **gameOfficialWinners){
    Stack *currentWinner = NULL, *currentWinnerOpponent = NULL;
    Stack *winnerStack = NULL, *loserStack = NULL, *winnerOfTheGame = NULL;
    WinnersList *gameWinners = NULL;
    QMatch *scheduledMatch = NULL, *finalMatch = NULL;
    gameWinners = *gameOfficialWinners;
    int numberOfRounds = 1;
    queueOfMatches = NULL;
    queueOfMatches = createTheQueue();
    enqueueUtil(queueOfMatches, listOfTeamsHead, outputFile);
    fprintf(*outputFile, "\n");
    while (numberOfTeams > 2)
    {
        fprintf(*outputFile, "--- ROUND NO:%d\n", numberOfRounds);
        while (!isQueueOfMatchesEmpty(queueOfMatches))
        {
            QMatch *currentMatch = dequeueOfMatches(queueOfMatches, &winnerStack, &loserStack);
            printQueueLine(outputFile, currentMatch);
        }
        fprintf(*outputFile, "\nWINNERS OF ROUND NO:%d\n", numberOfRounds);
        queueOfMatches = createTheQueue();
        while (!isTheStackEmpty(winnerStack))
        {
            currentWinner = pop(&winnerStack);
            currentWinnerOpponent = pop(&winnerStack);
            scheduledMatch = prepairTheScheduledMatch(currentWinner, currentWinnerOpponent);
            if (numberOfTeams == 16)
            {
                gameWinners = addTheWInnersUtil(gameWinners, currentWinner, currentWinnerOpponent);
            }
            printStackLine(outputFile, currentWinner, currentWinnerOpponent);
            enqueueTheMatch(queueOfMatches, scheduledMatch, outputFile);
        }
        numberOfRounds++;
        numberOfTeams /= 2;
        fprintf(*outputFile, "\n");
    }
    //simulateTheFinalMatch();
    finalMatch = dequeueOfMatches(queueOfMatches, &currentWinner, &currentWinnerOpponent);
    fprintf(*outputFile, "--- ROUND NO:%d\n", numberOfRounds);
    int index = strlen(finalMatch->firstTeam);
    printQueueLine(outputFile, finalMatch);
    winnerOfTheGame = (Stack *)malloc(sizeof(Stack));
    if (finalMatch->firstTeamScore > finalMatch->secondTeamScore)
    {
        winnerOfTheGame->next = NULL;
        winnerOfTheGame->nameOfTeam = (char *)malloc(strlen(finalMatch->firstTeam) + 1);
        strcpy(winnerOfTheGame->nameOfTeam, finalMatch->firstTeam);
        winnerOfTheGame->points = finalMatch->firstTeamScore;
        winnerOfTheGame -> playersList = finalMatch -> firstTeamPlayers;
    }
    else
    {
        winnerOfTheGame->next = NULL;
        winnerOfTheGame->nameOfTeam = (char *)malloc(strlen(finalMatch->secondTeam) + 1);
        strcpy(winnerOfTheGame->nameOfTeam, finalMatch->secondTeam);
        winnerOfTheGame->points = finalMatch->secondTeamScore;
        winnerOfTheGame -> playersList = finalMatch -> secondTeamPlayers;
    }
    //printf("%.2f\n", winnerOfTheGame -> points);
    winnerOfTheGame -> points = updateTheScore(&(winnerOfTheGame -> playersList));
    winnerOfTheGame -> points --;
    fprintf(*outputFile, "\nWINNERS OF ROUND NO:%d\n", numberOfRounds);
    fprintf(*outputFile, "%s", winnerOfTheGame->nameOfTeam);
    index = strlen(winnerOfTheGame->nameOfTeam);
    while (index < 34)
    {
        fputc(' ', *outputFile);
        index++;
    }
    fprintf(*outputFile, "-  %.2lf\n", winnerOfTheGame->points);
    *gameOfficialWinners = gameWinners;
    return;
}

int main(int argc, char *argv[])
{
    int numberOfTeams, positionOfLastRequest = 0;
    Team *listOfTeamsHead = NULL;
    WinnersList *gameWinners = NULL, *leaderboard = NULL;
    FILE *teamsFiles, *requestFiles, *outputFile;
    QueueOfMatches *queueOfMatches = NULL;
    WinnersTree *binarySearchTreeRoot = NULL;
    AVLNode *avlRoot = NULL;
    openTheFile(&outputFile, "wt", argv[3]);
    positionOfLastRequest = readTheRequests(&requestFiles, positionOfLastRequest, argv);
    readingData(positionOfLastRequest, &numberOfTeams, &teamsFiles, &listOfTeamsHead, argv);
    if (positionOfLastRequest == 1)
    {
        solveTheFirstTask(listOfTeamsHead, &outputFile);
    }
    if (positionOfLastRequest == 2)
    {
        solveTheSecondTask(listOfTeamsHead, &outputFile, numberOfTeams);
    }
    if (positionOfLastRequest >= 3)
    {
        solveTheThirdTaskPt1(&listOfTeamsHead, &outputFile, &numberOfTeams);
        simulateTheGame(queueOfMatches, &outputFile, listOfTeamsHead, numberOfTeams, &gameWinners);
    }
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
    
    if(positionOfLastRequest >= 5)
    {
        createTheLeaderboard(&leaderboard, binarySearchTreeRoot);
        WinnersList *copyOfLeaderboard = leaderboard;
        while(copyOfLeaderboard != NULL){
            avlRoot = insertInAVL(avlRoot, copyOfLeaderboard -> nameOfWinnersTeam, copyOfLeaderboard -> points);
            copyOfLeaderboard = copyOfLeaderboard -> next;
        }
        
        fprintf(outputFile, "\nTHE LEVEL 2 TEAMS ARE: \n%s\n", avlRoot -> left -> left ->nameOfTeam);
        fprintf(outputFile,"%s\n", avlRoot -> left -> right ->nameOfTeam);
        fprintf(outputFile,"%s\n", avlRoot -> right -> left ->nameOfTeam);
        fprintf(outputFile,"%s", avlRoot -> right -> right ->nameOfTeam); 
        listOfTeamsHead = deleteTheList(listOfTeamsHead);
        deleteTheTree(&binarySearchTreeRoot);
        deleteAVLTree(avlRoot);
    } 
        
    closeTheFile(&outputFile);
    return 0;
}