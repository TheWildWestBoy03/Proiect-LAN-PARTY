#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack{
    char *nameOfTeam;
    float points;
    struct Stack *next;
}Stack;

Stack *top(Stack *theStack);
Stack *pop(Stack *theStack);
void pushTheWinner(Stack **theStack, Stack *winnerOrLoserTeam);
int isTheStackEmpty(Stack *theStack);
