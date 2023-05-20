#include "matchesQueue.h"

void solveTheFirstTask(Team *listOfTeamsHead, FILE **outputFile);
void solveTheSecondTask(Team *listOfTeamsHead, FILE **outputFile, int numberOfTeams);
void solveTheThirdTaskPt1(Team **listOfTeamsHead, FILE **outputFile, int *numberOfTeams);
void printQueueLine(FILE **outputFile, QMatch *currentMatch);
void printStackLine(FILE **outputFile, Stack *currentWinner, Stack *currentWinnerOpponent);
WinnersList *addTheWInnersUtil(WinnersList *gameWinners, Stack *currentWinner, Stack *currentWinnerOpponent);
QMatch *prepairTheScheduledMatch(Stack *currentWinner, Stack *currentWinnerOpponent);
Stack *getTheFinalWinner(QMatch *finalMatch);
void simulateFinalMatch(QueueOfMatches *queueOfMatches, Stack *currentWinner, Stack *currentWinnerOpponent, FILE **outputFile, int numberOfRounds);
void simulateTheGame(QueueOfMatches *queueOfMatches, FILE **outputFile, Team *listOfTeamsHead, int numberOfTeams, WinnersList **gameOfficialWinners, int positionOfLastRequest);
void solveTheFourthTask(WinnersList *gameWinners, FILE **outputFile, WinnersTree **binarySearchTreeRoot, int positionOfLastRequest);
void solveTheLastTask(WinnersTree *binarySearchTreeRoot, AVLNode **avlRoot, FILE **outputFile);
