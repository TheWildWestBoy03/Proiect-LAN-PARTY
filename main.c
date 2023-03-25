#include "listOfTeams.h"

// void readingData();
int main()
{
    int numberOfTeams;
    Team *listOfTeamsHead = NULL;
    FILE *teamsFiles;
    printf("Insert the number of teams! \n");
    scanf("%d", &numberOfTeams);
    getchar();
    addTheTeams(&listOfTeamsHead, numberOfTeams);
    printf("Sunt aici boss! \n");
    displayTheList(listOfTeamsHead);
    return 0;
}
