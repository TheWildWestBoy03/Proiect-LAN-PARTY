#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Player
{
    char *firstName;
    char *secondName;
    int points;
    struct Player *next;
} Player;