#include "cerinte.h"

void solveTheFirstTask(Team *listOfTeamsHead, FILE **outputFile)
{
    displayTheList(listOfTeamsHead, outputFile);
    listOfTeamsHead = deleteTheList(listOfTeamsHead);
    return;
}

void solveTheSecondTask(Team *listOfTeamsHead, FILE **outputFile, int numberOfTeams)
{
    eliminateTheTeamsUtil(&listOfTeamsHead, &numberOfTeams, outputFile);
    displayTheList(listOfTeamsHead, outputFile);
    listOfTeamsHead = deleteTheList(listOfTeamsHead);
    return;
}

void solveTheThirdTaskPt1(Team **listOfTeamsHead, FILE **outputFile, int *numberOfTeams)
{
    eliminateTheTeamsUtil(listOfTeamsHead, numberOfTeams, outputFile);
    displayTheList(*listOfTeamsHead, outputFile);
    return;
}
void printQueueLine(FILE **outputFile, QMatch *currentMatch)
{
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
void printStackLine(FILE **outputFile, Stack *currentWinner, Stack *currentWinnerOpponent)
{
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

WinnersList *addTheWInnersUtil(WinnersList *gameWinners, Stack *currentWinner, Stack *currentWinnerOpponent)
{
    WinnersList *WinnerTeamToAdd = (WinnersList *)malloc(sizeof(WinnersList));
    WinnerTeamToAdd->nameOfWinnersTeam = (char *)malloc(strlen(currentWinner->nameOfTeam) + 1);
    strcpy(WinnerTeamToAdd->nameOfWinnersTeam, currentWinner->nameOfTeam);
    WinnerTeamToAdd->points = currentWinner->points;
    WinnerTeamToAdd->next = NULL;
    addTheWinners(&gameWinners, WinnerTeamToAdd);
    WinnerTeamToAdd = (WinnersList *)malloc(sizeof(WinnersList));
    WinnerTeamToAdd->nameOfWinnersTeam = (char *)malloc(strlen(currentWinnerOpponent->nameOfTeam) + 1);
    strcpy(WinnerTeamToAdd->nameOfWinnersTeam, currentWinnerOpponent->nameOfTeam);
    WinnerTeamToAdd->points = currentWinnerOpponent->points;
    WinnerTeamToAdd->next = NULL;
    addTheWinners(&gameWinners, WinnerTeamToAdd);
    return gameWinners;
}

QMatch *prepairTheScheduledMatch(Stack *currentWinner, Stack *currentWinnerOpponent)
{
    QMatch *scheduledMatch = NULL;
    scheduledMatch = (QMatch *)malloc(sizeof(QMatch));
    scheduledMatch->firstTeam = (char *)malloc(sizeof(char) * (strlen(currentWinner->nameOfTeam) + 1));
    strcpy(scheduledMatch->firstTeam, currentWinner->nameOfTeam);
    scheduledMatch->firstTeamScore = currentWinner->points;
    scheduledMatch->firstTeamPlayers = currentWinner->playersList;
    scheduledMatch->secondTeam = (char *)malloc(sizeof(char) * (strlen(currentWinnerOpponent->nameOfTeam) + 10));
    strcpy(scheduledMatch->secondTeam, currentWinnerOpponent->nameOfTeam);
    scheduledMatch->secondTeamScore = currentWinnerOpponent->points;
    scheduledMatch->secondTeamPlayers = currentWinnerOpponent->playersList;
    scheduledMatch->next = NULL;
    return scheduledMatch;
}

void simulateFinalMatch(QueueOfMatches *queueOfMatches, Stack *currentWinner, Stack *currentWinnerOpponent, FILE **outputFile, int numberOfRounds)
{
    Stack *winnerOfTheGame = NULL, *theSecondBestTeam = NULL;
    QMatch *finalMatch = dequeueOfMatches(queueOfMatches, &winnerOfTheGame, &theSecondBestTeam);
    fprintf(*outputFile, "--- ROUND NO:%d\n", numberOfRounds);
    printQueueLine(outputFile, finalMatch);
    fprintf(*outputFile, "\nWINNERS OF ROUND NO:%d\n", numberOfRounds);
    fprintf(*outputFile, "%s", winnerOfTheGame->nameOfTeam);
    int index = strlen(winnerOfTheGame->nameOfTeam);
    while (index < 34)
    {
        fputc(' ', *outputFile);
        index++;
    }
    fprintf(*outputFile, "-  %.2lf\n", winnerOfTheGame->points);
    winnerOfTheGame = deleteWinner(winnerOfTheGame);
    theSecondBestTeam = deleteWinner(theSecondBestTeam);
    return;
}
void simulateTheGame(QueueOfMatches *queueOfMatches, FILE **outputFile, Team *listOfTeamsHead, int numberOfTeams, WinnersList **gameOfficialWinners, int positionOfLastRequest)
{
    Stack *currentWinner = NULL, *currentWinnerOpponent = NULL;
    Stack *winnerStack = NULL, *loserStack = NULL;
    WinnersList *gameWinners = NULL;
    QMatch *scheduledMatch = NULL;
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
        deleteTheMatchesQueue(queueOfMatches);
        deleteStack(&loserStack);
        fprintf(*outputFile, "\nWINNERS OF ROUND NO:%d\n", numberOfRounds);
        queueOfMatches = createTheQueue();
        while (!isTheStackEmpty(winnerStack))
        {
            currentWinner = pop(&winnerStack);
            currentWinnerOpponent = pop(&winnerStack);
            scheduledMatch = prepairTheScheduledMatch(currentWinner, currentWinnerOpponent);
            if (numberOfTeams == 16 && positionOfLastRequest >= 4)
            {
                gameWinners = addTheWInnersUtil(gameWinners, currentWinner, currentWinnerOpponent);
            }
            printStackLine(outputFile, currentWinner, currentWinnerOpponent);
            enqueueTheMatch(queueOfMatches, scheduledMatch, outputFile);
            currentWinner = deleteWinner(currentWinner);
            currentWinnerOpponent = deleteWinner(currentWinnerOpponent);
        }
        numberOfRounds++;
        numberOfTeams /= 2;
        fprintf(*outputFile, "\n");
    }
    simulateFinalMatch(queueOfMatches, currentWinner, currentWinnerOpponent, outputFile, numberOfRounds);
    *gameOfficialWinners = gameWinners;
    return;
}

void solveTheFourthTask(WinnersList *gameWinners, FILE **outputFile, WinnersTree **binarySearchTreeRoot, int positionOfLastRequest)
{
    WinnersTree *copy = *binarySearchTreeRoot;
    fprintf(*outputFile, "\nTOP 8 TEAMS:\n");
    while (gameWinners != NULL)
    {
        copy = addTeamInTree(copy, gameWinners->nameOfWinnersTeam, gameWinners->points);
        gameWinners = gameWinners->next;
    }
    inorder(copy, outputFile);
    *binarySearchTreeRoot = copy;
    if (positionOfLastRequest < 5)
    {
        deleteTheTree(binarySearchTreeRoot);
    }
    gameWinners = deleteWinners(gameWinners);
    return;
}

void solveTheLastTask(WinnersTree *binarySearchTreeRoot, AVLNode **avlRoot, FILE **outputFile)
{
    AVLNode *copyAVL = *avlRoot;
    WinnersList *leaderboard = NULL;
    createTheLeaderboard(&leaderboard, binarySearchTreeRoot);
    WinnersList *copyOfLeaderboard = leaderboard;
    while (copyOfLeaderboard != NULL)
    {
        copyAVL = insertInAVL(copyAVL, copyOfLeaderboard->nameOfWinnersTeam, copyOfLeaderboard->points);
        copyOfLeaderboard = copyOfLeaderboard->next;
    }
    leaderboard = deleteWinners(leaderboard);
    fprintf(*outputFile, "\nTHE LEVEL 2 TEAMS ARE: \n%s\n", copyAVL->left->left->nameOfTeam);
    fprintf(*outputFile, "%s\n", copyAVL->left->right->nameOfTeam);
    fprintf(*outputFile, "%s\n", copyAVL->right->left->nameOfTeam);
    fprintf(*outputFile, "%s", copyAVL->right->right->nameOfTeam);
    *avlRoot = copyAVL;
    deleteAVLTree(avlRoot);
    return;
}