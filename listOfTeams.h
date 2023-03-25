#include <stdio.h>
#include <stdlib.h>

typedef int Data;
typedef struct Team{
    Data numberOfMembers;
    char *nameOfTeam;
    struct Team *next; 
    struct Player *playersInTeam;
}Team

typedef struct Player{
    char *firstName;
    char *secondName;
    int points;
}Player;
void addingAtBeginning(Team **listOfTeamHead, Data numberOfMembers, char *nameOfTeam, Team *current);
void addTheTeams(Team **listOfTeamHead, int numberOfTeams);
void displayTheList(Team *listOfTeamHead);
