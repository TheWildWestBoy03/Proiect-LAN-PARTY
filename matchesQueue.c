#include "matchesQueue.h"

QueueOfMatches *createTheQueue()
{
    printf("In create the queue!\n");
    QueueOfMatches *newQueue = (QueueOfMatches *)malloc(sizeof(QueueOfMatches));
    if (newQueue == NULL)
    {
        return NULL;
    }
    newQueue->firstMatch = newQueue->lastMatch = NULL;
    return newQueue;
}
void enqueueUtil(QueueOfMatches *queueOfMatches, Team *listOfTeamsHead, FILE **outputFile)
{
    // printf("In enqueueUtil \n");
    while (listOfTeamsHead != NULL)
    {
        QMatch *currentMatch = (QMatch *)malloc(sizeof(QMatch));
        currentMatch->firstTeam = (char *)malloc(2 + strlen(listOfTeamsHead->nameOfTeam));
        strcpy(currentMatch->firstTeam, listOfTeamsHead->nameOfTeam);
        //   printf("Where tf is that seg fault/\n");
        currentMatch->firstTeamScore = listOfTeamsHead->medium;
        //   printf("Where tf is that seg fault/\n");
        if (listOfTeamsHead->next != NULL)
        {
            currentMatch->secondTeam = (char *)malloc(2 + strlen(listOfTeamsHead->next->nameOfTeam));
        }
        //  printf("Where tf is that seg fault/\n");
        strcpy(currentMatch->secondTeam, listOfTeamsHead->next->nameOfTeam);
        // printf("%s %s", currentMatch->firstTeam, currentMatch->secondTeam);
        currentMatch->secondTeamScore = listOfTeamsHead->next->medium;
        currentMatch->next = NULL;
        enqueueTheMatch(queueOfMatches, currentMatch, &*outputFile);
        listOfTeamsHead = listOfTeamsHead->next->next;
    }
    return;
}
void enqueueTheMatch(QueueOfMatches *queueOfMatches, QMatch *currentMatch, FILE **outputFile)
{
    static int i = 0;
    fprintf(*outputFile, "%s                  -                 %s \n", currentMatch->firstTeam, currentMatch->secondTeam);
    if (queueOfMatches->lastMatch == NULL)
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
    // printf("%d \n", ++i);
    return;
}

QMatch *setTheMatch(QMatch *someMatch, QMatch *aux)
{
    someMatch->next = NULL;
    someMatch->firstTeam = (char *)malloc(strlen(aux->firstTeam) + 1);
    strcpy(someMatch->firstTeam, aux->firstTeam);
    someMatch->secondTeam = (char *)malloc(strlen(aux->secondTeam) + 1);
    strcpy(someMatch->secondTeam, aux->secondTeam);
    someMatch->firstTeamScore = aux->firstTeamScore;
    someMatch->secondTeamScore = aux->secondTeamScore;
    return someMatch;
}

QMatch *dequeueOfMatches(QueueOfMatches *queueOfMatches)
{
    printf("In dequeueOfMatches \n");
    QMatch *aux = NULL, *matchToGet = malloc(sizeof(QMatch));
    aux = queueOfMatches->firstMatch;
    aux->next = NULL;
    matchToGet = setTheMatch(matchToGet, aux);
    // printf("%s %s \n", matchToGet -> firstTeam, matchToGet -> secondTeam);
    if (isQueueOfMatchesEmpty(queueOfMatches) == 0)
    {
        queueOfMatches->firstMatch = (queueOfMatches->firstMatch)->next;
    }
    else
        queueOfMatches->firstMatch = NULL;
    free(aux);
    return matchToGet;
}

int isQueueOfMatchesEmpty(QueueOfMatches *queueOfMatches)
{
    printf("In isqueueempty \n");
    if (queueOfMatches->firstMatch == queueOfMatches->lastMatch && queueOfMatches->lastMatch == NULL)
    {
        return 1;
    }
    return 0;
}
