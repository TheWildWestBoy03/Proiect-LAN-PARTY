/*
    In this file, i defined the body of the most important functions for
    manipulating the lists.
*/
#include "listOfTeams.h"
#include <string.h>

void addingAtBeginning(Team **listOfTeamHead, Team **current)
{
    if (*listOfTeamHead == NULL)
    {
        *listOfTeamHead = *current;
        return;
    }
    (*current)->next = *listOfTeamHead;
    *listOfTeamHead = *current;
}

void addTheTeams(Team **listOfTeamHead, int numberOfTeams)
{
    Team *copy = *listOfTeamHead;
    char bufferNameOfTeam[50], *nameOfTeam;
    Player *playersInTheTeam;
    for (int i = 0; i < numberOfTeams; i++)
    {
        Team *current = (Team *)malloc(sizeof(Team));
        int numberOfMembers;
        printf("How many students are in this team? \n");
        scanf("%d", &numberOfMembers);
        getchar();
        printf("What is the name of this team? ");
        gets(bufferNameOfTeam);
        nameOfTeam = (char *)malloc(strlen(bufferNameOfTeam));
        strcpy(nameOfTeam, bufferNameOfTeam);
        playersInTheTeam = (Player *)malloc(sizeof(Player) * numberOfMembers);
        for (int j = 0; j < numberOfMembers; j++)
        {
            printf("The first name of the member %d is: ", j);
            char bufferFirstNameOfMember[50], bufferSecondNameOfMember[50];
            int bufferPoints;
            gets(bufferFirstNameOfMember);
            printf("The second name of the member %d is: ", j);
            gets(bufferSecondNameOfMember);
            printf("The number of points obtained by this member is: ");
            scanf("%d", &bufferPoints);
            getchar();
            playersInTheTeam[j].firstName = (char *)malloc(sizeof(bufferFirstNameOfMember));
            playersInTheTeam[j].secondName = (char *)malloc(sizeof(bufferSecondNameOfMember));
            playersInTheTeam[j].points = bufferPoints;

            strcpy(playersInTheTeam[j].firstName, bufferFirstNameOfMember);
            strcpy(playersInTheTeam[j].secondName, bufferSecondNameOfMember);
            //  printf("%s %s %d \n", playersInTheTeam[j].firstName, playersInTheTeam[j].secondName, playersInTheTeam[j].points);
        }

        current->next = NULL;
        current->numberOfMembers = numberOfMembers;
        current->nameOfTeam = (char *)malloc(sizeof(char) * strlen(nameOfTeam));
        strcpy(current->nameOfTeam, nameOfTeam);
        current->playersInTeam = (Player *)malloc(sizeof(Player) * numberOfMembers);
        for (int j = 0; j < numberOfMembers; j++)
        {
            //  printf("%s %s %d \n", playersInTheTeam[j] . firstName, playersInTheTeam[j] . secondName, playersInTheTeam[j] . points);
            current->playersInTeam[j].points = playersInTheTeam[j].points;
            printf("%d ", current->playersInTeam[j].points);
            current->playersInTeam[j].firstName = (char *)malloc(sizeof(char) * (strlen(playersInTheTeam[j].firstName) + 1));
            printf("Sunt aici! \n");
            current->playersInTeam[j].secondName = (char *)malloc(sizeof(char) * (strlen(playersInTheTeam[j].secondName) + 1));
            strcpy(current->playersInTeam[j].firstName, playersInTheTeam[j].firstName);
            strcpy(current->playersInTeam[j].secondName, playersInTheTeam[j].secondName);
            puts(current->playersInTeam[j].firstName);
            puts(current->playersInTeam[j].secondName);
        }
        addingAtBeginning(&*listOfTeamHead, &current);
    }
}

void displayTheList(Team *listOfTeamHead)
{
    while (listOfTeamHead != NULL)
    {
        printf("The name of team is: ");
        printf("%s \n", listOfTeamHead->nameOfTeam);
        printf("--------------------- \n");
        for (int i = 0; i < listOfTeamHead->numberOfMembers; i++)
        {
            printf("%s ", listOfTeamHead->playersInTeam[i].firstName);
            printf("%s ", listOfTeamHead->playersInTeam[i].secondName);
            printf("%d \n", listOfTeamHead->playersInTeam[i].points);
        }
        printf("--------------------- \n");
        printf("%d \n", listOfTeamHead->numberOfMembers);
        listOfTeamHead = listOfTeamHead->next;
    }
    return;
}
