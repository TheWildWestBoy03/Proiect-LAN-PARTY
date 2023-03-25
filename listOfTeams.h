#include <stdio.h>
#include <stdlib.h>

typedef int Data;
typedef struct Team{
    Data numberOfMembers;
    char *nameOfTeam;
    char **nameOfColleagues;
    struct Team *next; 
    struct Player *player;
}Team
typedef struct Player{
    char *firstName;
    char *secondName;
    int punctaj;
}Player;
void addingAtBeginning(Team **listOfTeamHead, Data numberOfMembers, char *nameOfTeam, Team *current);
void addTheTeams(Team **listOfTeamHead, int numberOfTeams);
void displayTheList(Team *listOfTeamHead);
