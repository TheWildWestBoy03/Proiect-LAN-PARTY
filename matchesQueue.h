#include "listOfTeams.h"

typedef struct QMatch{
    char *firstTeam, *secondTeam;
    int firstTeamScore, secondTeamScore;
    struct QMatch *next;
}QMatch;

typedef struct QueueOfMatches{
    struct QMatch *firstMatch, *lastMatch;
}QueueOfMatches;

QueueOfMatches *createTheQueue();
void enqueueTheMatch(QueueOfMatches *queueOfMatches, QMatch *currentMatch);
void enqueueUtil(QueueOfMatches *queueOfMatches, Team *listOfTeamsHead);
void deleteTheQueue(QueueOfMatches *queueOfMatches);
QMatch *dequeueOfMatches(QueueOfMatches *queueOfMatches);
int isQueueOfMatchesEmpty(QueueOfMatches *queueOfMatches);
QMatch *setTheMatch(QMatch *someMatch, QMatch *aux);
