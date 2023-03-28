#include "matchesQueue.h"
#include "listOfTeams.h"

QueueOfMatches *createTheQueue()
{
    QueueOfMatches *newQueue = (QueueOfMatches *)malloc(sizeof(QueueOfMatches));
    if (newQueue == NULL)
    {
        return NULL;
    }
    newQueue->firstMatch = newQueue->lastMatch = NULL;
    return newQueue;
}
void enqueueUtil(QueueOfMatches *queueOfMatches, Team *listOfTeamsHead)
{
    queueOfMatches = createTheQueue();
    QMatch *currentMatch = (QMatch *)malloc(sizeof(QMatch));
    while (listOfTeamsHead != NULL)
    {
        currentMatch->firstTeam = (char *)malloc(1 + strlen(listOfTeamsHead->nameOfTeam));
        currentMatch->firstTeamScore = listOfTeamHead->points;
        currentMatch->secondTeam = (char *)malloc(1 + strlen(listOfTeamsHead->next->nameOfTeam));
        currentMatch->secondTeamScore = listOfTeamHead->next->points;
        currentMatch->next = NULL;
        enqueueTheMatch(queueOfMatches, currentMatch);
    }
    return;
}
void enqueueTheMatch(QueueOfMatches *queueOfMatches, QMatch *currentMatch)
{
    if (queueOfMatche->lastMatch == NULL)
    {
        queueOfMatches->lastMatch = currentMatch;
    }
    else
    {
        (queueOfMatches->lastMatch)->next = currentMatch;
        queueOfMatches->lastMatch = currentMatch;
    }
    if (queueOfMatches->firstMatch == NULL)
    {
        queueOfMatches->firstMatch = queueOfMatches->lastMatch;
    }
    return;
}
QMatch *setTheMatch(QMatch *someMatch, QMatch *aux)
{
    someMatch->next = NULL;
    someMatch->firstTeam = aux->firstTeam;
    someMatch->secondTeam = aux->secondTeam;
    someMatch->firstTeamScore = aux->firstTeamScore;
    someMatch->secondTeamScore = aux->secondTeamScore;
    return someMatch;
}

QMatch *dequeueOfMatches(QueueOfMatches *QueueOfMatches)
{
    QMatch *aux = NULL, *matchToGet = malloc(sizeof(QMatch));
    aux = QueueOfMatches->front;
    matchToGet = setTheMatch(matchToGet);
    QueueOfMatches->front = QueueOfMatches->front->next;
    free(aux);
    return matchToGet;
}

int isQueueOfMatchesEmpty(QueueOfMatches *queueOfMatches)
{
    if (queueOfMatches->firstMatch == queue->lastMatch && queueOfMatches->lastMatch == NULL)
    {
        return 1;
    }
    return 0;
}