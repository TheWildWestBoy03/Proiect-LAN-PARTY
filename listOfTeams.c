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
void addingPlayer(Player **playerHead, Player *currentPlayer)
{
    if (*playerHead == NULL)
    {
        *playerHead = currentPlayer;
        return;
    }

    currentPlayer->next = *playerHead;
    *playerHead = currentPlayer;
    return;
}
void displayThePlayers(Player *playerHead, FILE **outputFile)
{
    while (playerHead != NULL)
    {
        // fprintf(*outputFile, "%s %s %d\n", playerHead->firstName, playerHead->secondName, playerHead->points);
        //  printf("%s %s %d -----> ", playerHead->firstName, playerHead->secondName, playerHead->points);
        playerHead = playerHead->next;
    }
    return;
}

void addTheTeams(Team **listOfTeamHead, int numberOfTeams, FILE *teamsFile)
{
    Team *copy = *listOfTeamHead;
    char bufferNameOfTeam[50], *nameOfTeam;
    for (int i = 0; i < numberOfTeams; i++)
    {
        Team *current = (Team *)malloc(sizeof(Team));
        char buffer[100];
        int numberOfMembers = 0;
        fgets(buffer, 99, teamsFile);
        int numberOfDigits = 0, risingFactory = 1;
        while (buffer[numberOfDigits] >= '0' && buffer[numberOfDigits] <= '9')
        {
            numberOfMembers = numberOfMembers * 10 + (buffer[numberOfDigits] - 48);
            numberOfDigits++;
            risingFactory *= 10;
        }
        nameOfTeam = (char *)malloc(sizeof(char) * (strlen(buffer) - numberOfDigits));
        strcpy(nameOfTeam, buffer + numberOfDigits + 1);
        nameOfTeam[strlen(nameOfTeam) - 1] = 0;
        while(nameOfTeam[strlen(nameOfTeam) - 1] == ' '){
            nameOfTeam[strlen(nameOfTeam) - 1] = 0;
        }
        current->nameOfTeam = (char *)malloc(sizeof(char) * (strlen(nameOfTeam) + 1));
        current->next = NULL;
        current->numberOfMembers = numberOfMembers;
        strcpy(current->nameOfTeam, nameOfTeam);
        Player *currentPlayer = NULL;
        current->playersHead = NULL;
        Player *playersToDisplay = current->playersHead;
        current->medium = 0;
        for (int j = 0; j < numberOfMembers; j++)
        {
            currentPlayer = (Player *)malloc(sizeof(Player));
            currentPlayer->next = NULL;
            char bufferFirstNameOfMember[50], bufferSecondNameOfMember[50];
            int bufferPoints;
            fscanf(teamsFile, "%s %s %d\n", bufferFirstNameOfMember, bufferSecondNameOfMember, &bufferPoints);
            currentPlayer->firstName = (char *)malloc(strlen(bufferFirstNameOfMember) + 1);
            currentPlayer->secondName = (char *)malloc(strlen(bufferSecondNameOfMember) + 1);
            currentPlayer->points = bufferPoints;
            current->medium += currentPlayer->points;
            strcpy(currentPlayer->firstName, bufferFirstNameOfMember);
            strcpy(currentPlayer->secondName, bufferSecondNameOfMember);
            addingPlayer(&(current->playersHead), currentPlayer);
        }
        fscanf(teamsFile, "\n");
        current->medium /= current->numberOfMembers;
        addingAtBeginning(&*listOfTeamHead, &current);
    }
}
void displayTheList(Team *listOfTeamHead, FILE **outputFile)
{
    while (listOfTeamHead != NULL)
    {
        // fprintf(*outputFile, "%d ", listOfTeamHead->numberOfMembers);
        fprintf(*outputFile, "%s\n", listOfTeamHead->nameOfTeam);
        // fprintf(*outputFile, "%f \n", listOfTeamHead->medium);
        // fprintf(*outputFile, "--------------------- \n");
        // displayThePlayers(listOfTeamHead->playersHead, &*outputFile);
        // fprintf(*outputFile, "--------------------- \n");
        listOfTeamHead = listOfTeamHead->next;
    }
    return;
}
void eliminateTheTeamsUtil(Team **listOfTeamsHead, int *numberOfTeams, FILE **outputFile)
{
    int powerOfTwo = 1;
    while (powerOfTwo * 2 <= *numberOfTeams)
    {
        powerOfTwo = powerOfTwo * 2;
    }

    for (int i = powerOfTwo; i < *numberOfTeams; i++)
    {
        eliminateTheTeams(&*listOfTeamsHead);
    }
    *numberOfTeams = powerOfTwo;
    return;
}
void deleteTheTeam(Team **current)
{
    if (*current == NULL)
    {
        return;
    }
    Team *copy = *current;
    if (copy->playersHead == NULL)
    {
        return;
    }
    while (copy->playersHead != NULL)
    {
        Player *todelete = copy->playersHead;
        copy->playersHead = copy->playersHead->next;
        free(copy->playersHead);
    }
}
void eliminateTheTeams(Team **listOfTeamsHead)
{
    //  printf("In eliminating the teams.");
    Team *copy = *listOfTeamsHead, *dummy;
    if (copy == NULL)
    {
        return;
    }
    float minimum = copy->medium;
    while (copy != NULL)
    {
        if (minimum > copy->medium)
        {
            minimum = copy->medium;
        }
        copy = copy->next;
    }
    dummy = (Team *)malloc(sizeof(Team));
    dummy->next = *listOfTeamsHead;
    dummy->medium = minimum + 10;
    copy = dummy;
    while (copy->next != NULL)
    {
        if (copy->next->medium == minimum)
        {
            if (copy->next->next == NULL)
            {
                Team *todelete = copy->next;
                copy->next = NULL;
                deleteTheTeam(&todelete);
                todelete = NULL;
            }
            else
            {
                Team *todelete = copy->next;
                copy->next = copy->next->next;
                deleteTheTeam(&todelete);
                todelete = NULL;
            }
            break;
        }
        copy = copy->next;
    }
    *listOfTeamsHead = dummy->next;
    free(dummy);
    dummy = NULL;
    return;
}

void addTheWinners(WinnersList **winnersListHead, WinnersList *currentTeam)
{
    currentTeam->next = *winnersListHead;
    *winnersListHead = currentTeam;
    return;
}