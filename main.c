#include "listOfTeams.h"

// void readingData();
int main()
{
    int numberOfTeams;
    Team *listOfTeamsHead = NULL;
    FILE *teamsFiles;
    printf("Insert the number of teams! \n");
    scanf("%d", &numberOfTeams);
    addTheTeams(&listOfTeamsHead, numberOfTeams);
    displayTheList(listOfTeamsHead);
    return 0;
}
