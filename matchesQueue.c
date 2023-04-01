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
    // printf("In enqueueUtil \n");
    while (listOfTeamsHead != NULL)
    {
        QMatch *currentMatch = (QMatch *)malloc(sizeof(QMatch));
        currentMatch->firstTeam = (char *)malloc(1 + strlen(listOfTeamsHead->nameOfTeam));
        strcpy(currentMatch->firstTeam, listOfTeamsHead->nameOfTeam);
        //   printf("Where tf is that seg fault/\n");
        currentMatch->firstTeamScore = listOfTeamsHead->medium;
        //   printf("Where tf is that seg fault/\n");
        if (listOfTeamsHead->next != NULL)
        {
            currentMatch->secondTeam = (char *)malloc(1 + strlen(listOfTeamsHead->next->nameOfTeam));
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
    printf("%s   -    %s\n", queueOfMatches -> lastMatch -> firstTeam, queueOfMatches -> lastMatch -> secondTeam);
    return;
}

QMatch *setTheMatch(QMatch *someMatch, QMatch *aux)
{
    //printf("In setthematch: \n");
    someMatch->next = NULL;
    someMatch->firstTeam = (char *)malloc(strlen(aux->firstTeam) + 1);
    strcpy(someMatch->firstTeam, aux->firstTeam);
    someMatch->secondTeam = (char *)malloc(strlen(aux->secondTeam) + 1);
    strcpy(someMatch->secondTeam, aux->secondTeam);
    someMatch->firstTeamScore = aux->firstTeamScore;
    someMatch->secondTeamScore = aux->secondTeamScore;
    return someMatch;
}

QMatch *dequeueOfMatches(QueueOfMatches *queueOfMatches, Stack **winnerStack, Stack **loserStack)
{
    QMatch *aux = NULL, *matchToGet = malloc(sizeof(QMatch));
    aux = queueOfMatches->firstMatch;
    if(isQueueOfMatchesEmpty(queueOfMatches)){
        return NULL;
    }
    matchToGet = setTheMatch(matchToGet, aux);
    Stack *currentWinner = (Stack*)malloc(sizeof(Stack));
    Stack *currentLoser = (Stack*)malloc(sizeof(Stack));
    currentLoser -> next = currentWinner -> next = NULL;
    if(matchToGet -> firstTeamScore > matchToGet -> secondTeamScore){
        currentWinner -> nameOfTeam = (char*)malloc(strlen(matchToGet -> firstTeam) + 1);
        strcpy(currentWinner -> nameOfTeam, matchToGet -> firstTeam);
        currentWinner -> points = (matchToGet ->firstTeamScore + 1);
        currentLoser -> points = (matchToGet -> secondTeamScore);
        pushTheWinner(&*winnerStack, currentWinner);
        currentLoser -> nameOfTeam = (char*)malloc(strlen(matchToGet -> secondTeam) + 1);
        strcpy(currentLoser -> nameOfTeam, matchToGet -> secondTeam);
        pushTheWinner(&*loserStack, currentLoser);
    }
    else {
        currentWinner -> nameOfTeam = (char*)malloc(strlen(matchToGet -> secondTeam) + 1);
        strcpy(currentWinner -> nameOfTeam, matchToGet -> secondTeam);
        currentWinner -> points = (matchToGet ->secondTeamScore + 1);
        currentLoser -> points = (matchToGet -> firstTeamScore);
        pushTheWinner(&*winnerStack, currentWinner);
        currentLoser -> nameOfTeam = (char*)malloc(strlen(matchToGet -> firstTeam) + 1);
        strcpy(currentLoser -> nameOfTeam, matchToGet -> firstTeam);
        pushTheWinner(&*loserStack, currentLoser);
    }
    queueOfMatches->firstMatch = (queueOfMatches->firstMatch)->next;
    free(aux -> firstTeam);
    free(aux);
    return matchToGet;
}

int isQueueOfMatchesEmpty(QueueOfMatches *queueOfMatches)
{
  //  printf("In isqueueempty \n");
    return (queueOfMatches -> firstMatch == NULL);
}
