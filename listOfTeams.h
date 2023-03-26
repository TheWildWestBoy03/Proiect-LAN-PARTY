#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
typedef int Data;

typedef struct Team{
    Data numberOfMembers;
    char *nameOfTeam;
    struct Team *next; 
    Player *playersInTeam;
    float medium;
}Team;

void addingAtBeginning(Team **listOfTeamHead, Team **current);
void addTheTeams(Team **listOfTeamHead, int numberOfTeams);
void displayTheList(Team *listOfTeamHead);
void eliminateTheTeamsUtil(Team **listOfTeamsHead, int numberOfTeams);
void eliminateTheTeams(Team **ListOfTeamsHead);
void openTheFile(FILE **input, char *mode, char *nameOfFile);
void closeTheFile(FILE **input);