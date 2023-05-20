#include "cerinte.h"

int main(int argc, char *argv[])
{
    int numberOfTeams, positionOfLastRequest = 0;
    Team *listOfTeamsHead = NULL;
    WinnersList *gameWinners = NULL;
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
        simulateTheGame(queueOfMatches, &outputFile, listOfTeamsHead, numberOfTeams, &gameWinners, positionOfLastRequest);
        listOfTeamsHead = deleteTheList(listOfTeamsHead);
    }
    if (positionOfLastRequest >= 4)
    {
        solveTheFourthTask(gameWinners, &outputFile, &binarySearchTreeRoot, positionOfLastRequest);
    }
    if (positionOfLastRequest >= 5)
    {
        solveTheLastTask(binarySearchTreeRoot, &avlRoot, &outputFile);
        deleteTheTree(&binarySearchTreeRoot);
    }

    closeTheFile(&outputFile);
    return 0;
}