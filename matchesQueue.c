#include "matchesQueue.h"

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
void enqueueUtil(QueueOfMatches *queueOfMatches, Team *listOfTeamsHead, FILE **outputFile)
{
    while (listOfTeamsHead != NULL)
    {
        QMatch *currentMatch = (QMatch *)malloc(sizeof(QMatch));
        currentMatch->firstTeam = (char *)malloc(1 + strlen(listOfTeamsHead->nameOfTeam));
        strcpy(currentMatch->firstTeam, listOfTeamsHead->nameOfTeam);
        currentMatch->firstTeamScore = listOfTeamsHead->medium;
        currentMatch->firstTeamPlayers = listOfTeamsHead->playersHead;
        if (listOfTeamsHead->next != NULL)
        {
            currentMatch->secondTeam = (char *)malloc(1 + strlen(listOfTeamsHead->next->nameOfTeam));
        }
        strcpy(currentMatch->secondTeam, listOfTeamsHead->next->nameOfTeam);
        currentMatch->secondTeamScore = listOfTeamsHead->next->medium;
        currentMatch->secondTeamPlayers = listOfTeamsHead->next->playersHead;
        currentMatch->next = NULL;
        enqueueTheMatch(queueOfMatches, currentMatch, &*outputFile);
        listOfTeamsHead = listOfTeamsHead->next->next;
    }
    return;
}
void enqueueTheMatch(QueueOfMatches *queueOfMatches, QMatch *currentMatch, FILE **outputFile)
{
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
    someMatch->firstTeamPlayers = aux->firstTeamPlayers;
    someMatch->secondTeamPlayers = aux->secondTeamPlayers;
    return someMatch;
}

QMatch *dequeueOfMatches(QueueOfMatches *queueOfMatches, Stack **winnerStack, Stack **loserStack)
{
    QMatch *aux = NULL, *matchToGet = malloc(sizeof(QMatch));
    aux = queueOfMatches->firstMatch;
    if (isQueueOfMatchesEmpty(queueOfMatches))
    {
        return NULL;
    }
    matchToGet = setTheMatch(matchToGet, aux);
    Stack *currentWinner = (Stack *)malloc(sizeof(Stack));
    Stack *currentLoser = (Stack *)malloc(sizeof(Stack));
    currentLoser->next = currentWinner->next = NULL;
    if (matchToGet->firstTeamScore > matchToGet->secondTeamScore)
    {
        currentWinner->nameOfTeam = (char *)malloc(strlen(matchToGet->firstTeam) + 1);
        strcpy(currentWinner->nameOfTeam, matchToGet->firstTeam);
        currentWinner -> playersList = matchToGet -> firstTeamPlayers;
        currentWinner -> points = updateTheScore(&(currentWinner -> playersList));
        pushTheWinner(&*winnerStack, currentWinner);
        currentLoser->nameOfTeam = (char *)malloc(strlen(matchToGet->secondTeam) + 1);
        strcpy(currentLoser->nameOfTeam, matchToGet->secondTeam);
        currentLoser->playersList = matchToGet -> secondTeamPlayers;
        currentLoser -> points = matchToGet -> secondTeamScore;
        pushTheWinner(&*loserStack, currentLoser);
    }
    else
    {
        currentWinner->nameOfTeam = (char *)malloc(strlen(matchToGet->secondTeam) + 1);
        strcpy(currentWinner->nameOfTeam, matchToGet->secondTeam);
        currentWinner -> playersList = matchToGet -> secondTeamPlayers;
        currentWinner -> points = updateTheScore(&(currentWinner -> playersList));
        currentLoser -> playersList = matchToGet -> firstTeamPlayers;
        currentLoser->points = (matchToGet->firstTeamScore);
        pushTheWinner(&*winnerStack, currentWinner);
        currentLoser->nameOfTeam = (char *)malloc(strlen(matchToGet->firstTeam) + 1);
        strcpy(currentLoser->nameOfTeam, matchToGet->firstTeam);
        pushTheWinner(&*loserStack, currentLoser);
    }
    queueOfMatches->firstMatch = (queueOfMatches->firstMatch)->next;
    free(aux->firstTeam);
    free(aux->secondTeam);
    aux -> firstTeamPlayers = NULL;
    aux -> secondTeamPlayers = NULL;
    free(aux);
    return matchToGet;
}

int isQueueOfMatchesEmpty(QueueOfMatches *queueOfMatches)
{
    return (queueOfMatches->firstMatch == NULL);
}