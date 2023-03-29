#include "stackOfWinners.h"
#include "listOfTeams.h"

typedef struct QMatch{
    char *firstTeam, *secondTeam;
    float firstTeamScore, secondTeamScore;
    struct QMatch *next;
}QMatch;

typedef struct QueueOfMatches{
    struct QMatch *firstMatch, *lastMatch;
}QueueOfMatches;

QueueOfMatches *createTheQueue();
void enqueueTheMatch(QueueOfMatches *queueOfMatches, QMatch *currentMatch, FILE **outputFile);
void enqueueUtil(QueueOfMatches *queueOfMatches, Team *listOfTeamsHead, FILE **outputFile);
void deleteTheQueue(QueueOfMatches *queueOfMatches);
QMatch *dequeueOfMatches(QueueOfMatches *queueOfMatches, Stack **winnerStack, Stack **loserStack);
int isQueueOfMatchesEmpty(QueueOfMatches *queueOfMatches);
QMatch *setTheMatch(QMatch *someMatch, QMatch *aux);
