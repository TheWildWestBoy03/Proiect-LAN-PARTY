#include "matchesQueue.h"

typedef struct StackofWinners{
    char *nameOfTeam;
    float points;
    struct StackofWinners *next;
}StackOfWinners;

StackOfWinners *top(StackOfWinners *stackOfWinners);
StackOfWinners *pop(StackOfWinners *stackOfWinners);
void pushTheWinner(StackOfWinners **stackofWinners, StackOfWinners *winnerTeam);
void isTheStackEmpty(StackOfWinners *StackOfWinners);
