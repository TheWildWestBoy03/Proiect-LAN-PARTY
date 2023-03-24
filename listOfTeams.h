#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listOfTeams.c"
typedef int Data;
typedef struct Team{
    Data numberOfMembers;
    char *nameOfTeam;
    char **nameOfColleagues;
    struct Team *next;  
}Team;

void addingAtBeginning(Team **listOfTeamHead, Data numberOfMembers, char *nameOfTeam);

