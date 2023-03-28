#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QMatch{
    char *firstTeam, *secondTeam;
    int firstTeamScore, secondTeamScore;
    struct QMatch *next;
}QMatch;
typedef struct QueueOfMatches{
    struct QMatch *firstMatch, *lastMatch;
}QueueOfMatches;

QueueOfMatches *createTheQueue();
void enqueueTheMatch(QueueOfMatches *QueueMatch, QMatch *currentMatch);
void deleteTheQueue(QueueOfMatches *QueueMatch);
QMatch *deQueueMatch(QueueOfMatches *QueueOfMatches);
int isQueueOfMatchesEmpty(QueueOfMatches *queueOfMatches);