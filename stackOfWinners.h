#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listOfTeams.h"

typedef struct Stack
{
    char *nameOfTeam;
    float points;
    struct Stack *next;
    Player *playersList;
} Stack;

Stack *top(Stack *theStack);
Stack *pop(Stack **theStack);
void pushTheWinner(Stack **theStack, Stack *winnerOrLoserTeam);
int isTheStackEmpty(Stack *theStack);
void deleteFromStack(Stack **itemToDelete);
void deleteStack(Stack **stackToDelete);