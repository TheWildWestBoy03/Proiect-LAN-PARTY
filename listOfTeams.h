#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
typedef int Data;

typedef struct Team{
    Data numberOfMembers;
    char *nameOfTeam;
    struct Team *next; 
    Player *playersInTeam;
}Team;

void addingAtBeginning(Team **listOfTeamHead, Data numberOfMembers, char *nameOfTeam, Team *current);
void addTheTeams(Team **listOfTeamHead, int numberOfTeams);
void displayTheList(Team *listOfTeamHead);
