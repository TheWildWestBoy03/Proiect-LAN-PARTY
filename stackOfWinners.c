#include "stackOfWinners.h"

Stack *top(Stack *theStack)
{
    Stack *returnIt = (Stack *)malloc(sizeof(Stack));
    returnIt->nameOfTeam = (char *)malloc(strlen(theStack->nameOfTeam) + 1);
    strcpy(returnIt->nameOfTeam, theStack->nameOfTeam);
    returnIt->points = theStack->points;
    returnIt->playersList = theStack->playersList;
    returnIt->next = NULL;
    return returnIt;
}

Stack *deleteWinner(Stack *winner)
{
    free(winner->nameOfTeam);
    winner->nameOfTeam = NULL;
    free(winner);
    winner = NULL;
    return winner;
}

Stack *pop(Stack **theStack)
{
    if (*theStack == NULL)
    {
        return NULL;
    }
    Stack *popTheTeam = (Stack *)malloc(sizeof(Stack)), *itemToDelete = *theStack;
    popTheTeam->nameOfTeam = (char *)malloc(strlen((*theStack)->nameOfTeam) + 1);
    strcpy(popTheTeam->nameOfTeam, (*theStack)->nameOfTeam);
    popTheTeam->points = (*theStack)->points;
    popTheTeam->next = NULL;
    popTheTeam->playersList = (*theStack)->playersList;
    (*theStack) = (*theStack)->next;
    deleteFromStack(&itemToDelete);
    return popTheTeam;
}

void deleteFromStack(Stack **itemToDelete)
{
    free((*itemToDelete)->nameOfTeam);
    (*itemToDelete)->nameOfTeam = NULL;
    (*itemToDelete)->playersList = NULL;
    free(*itemToDelete);
    *itemToDelete = NULL;
}
void pushTheWinner(Stack **theStack, Stack *Team)
{
    Team->next = *theStack;
    *theStack = Team;
}
int isTheStackEmpty(Stack *theStack)
{
    return (theStack == NULL);
}
void deleteStack(Stack **stackToDelete)
{
    while (isTheStackEmpty(*stackToDelete) == 0)
    {
        Stack *nodeToDelete = *stackToDelete;
        *stackToDelete = (*stackToDelete)->next;
        free(nodeToDelete->nameOfTeam);
        nodeToDelete->nameOfTeam = NULL;
        nodeToDelete->playersList = NULL;
        free(nodeToDelete);
        nodeToDelete = NULL;
    }
    return;
}
