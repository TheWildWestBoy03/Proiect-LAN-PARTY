#include "stackOfWinners.h"

Stack *top(Stack *theStack){
    Stack *returnIt = (Stack*)malloc(sizeof(Stack));
    returnIt -> nameOfTeam = theStack -> nameOfTeam;
    returnIt -> points = theStack -> points;
    returnIt -> next = NULL;
    return returnIt;
}

Stack *pop(Stack **theStack){
    if(*theStack == NULL){
        return NULL;
    }
    Stack *popTheTeam = (Stack*)malloc(sizeof(Stack));
    popTheTeam -> nameOfTeam = (*theStack) -> nameOfTeam;
    popTheTeam -> points = (*theStack) -> points;
    popTheTeam -> next = NULL;
    (*theStack) = (*theStack) -> next;
    return popTheTeam;
}

void pushTheWinner(Stack **theStack, Stack *Team){
     Team -> next = *theStack;
     *theStack = Team;
}
int isTheStackEmpty(Stack *theStack){
    return (theStack  == NULL);
}

