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
Player *assetThePlayer(char *bufferFirstNameOfMember, char *bufferSecondNameOfMember, int bufferPoints){
    Player *currentPlayer = NULL;
    currentPlayer = (Player *)malloc(sizeof(Player));
    currentPlayer->next = NULL;
    currentPlayer->firstName = (char *)malloc(strlen(bufferFirstNameOfMember) + 1);
    currentPlayer->secondName = (char *)malloc(strlen(bufferSecondNameOfMember) + 1);
    currentPlayer->points = bufferPoints;
    strcpy(currentPlayer->firstName, bufferFirstNameOfMember);
    strcpy(currentPlayer->secondName, bufferSecondNameOfMember);
    return currentPlayer;
}

Team *initializeTheTeam(Team *current, char *nameOfTeam, int numberOfMembers){
    current->nameOfTeam = (char *)malloc(sizeof(char) * (strlen(nameOfTeam) + 1));
    strcpy(current->nameOfTeam, nameOfTeam);
    current->next = NULL;
    current->numberOfMembers = numberOfMembers;
    current->medium = 0;
    current -> playersHead = NULL;
    return current;
}
void displayThePlayers(Player *playerHead, FILE **outputFile)
{
    while (playerHead != NULL)
    {
        playerHead = playerHead->next;
    }
    return;
}

void addTheTeams(Team **listOfTeamHead, int numberOfTeams, FILE *teamsFile)
{
    char *nameOfTeam;
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
        while (nameOfTeam[strlen(nameOfTeam) - 1] == ' ')
        {
            nameOfTeam[strlen(nameOfTeam) - 1] = 0;
        }
        current = initializeTheTeam(current, nameOfTeam, numberOfMembers);
        Player *currentPlayer = NULL;
        for (int j = 0; j < numberOfMembers; j++)
        {
            char bufferFirstNameOfMember[50], bufferSecondNameOfMember[50];
            int bufferPoints;
            fscanf(teamsFile, "%s %s %d\n", bufferFirstNameOfMember, bufferSecondNameOfMember, &bufferPoints);
            currentPlayer = assetThePlayer(bufferFirstNameOfMember, bufferSecondNameOfMember, bufferPoints);
            current->medium += currentPlayer->points;
            addingPlayer(&(current->playersHead), currentPlayer);
        }
        fscanf(teamsFile, "\n");
        current->medium /= current->numberOfMembers;
        addingAtBeginning(&*listOfTeamHead, &current);
    }
}

double updateTheScore(Player **playerList)
{
    Player *playerListCopy = *playerList;
    double score = 0.000;
    int numberOfPlayers = 0;
    while (playerListCopy != NULL)
    {
        (playerListCopy->points)++;
        numberOfPlayers++;
        score += (playerListCopy->points) * 1.000;
        playerListCopy = playerListCopy->next;
    }
    score /= numberOfPlayers;
    int numeral = score * 1000;
    if (numeral % 100 == 25)
    {
        score = score - 0.001;
    }
    return score;
}
void displayTheList(Team *listOfTeamHead, FILE **outputFile)
{
    while (listOfTeamHead != NULL)
    {
        fprintf(*outputFile, "%s\n", listOfTeamHead->nameOfTeam);
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
        free(todelete);
    }
}
void eliminateTheTeams(Team **listOfTeamsHead)
{
    Team *copy = *listOfTeamsHead, *dummy;
    if (copy == NULL)
    {
        return;
    }
    double minimum = getTheMinimum(*listOfTeamsHead);
    dummy = (Team *)malloc(sizeof(Team));
    dummy->next = *listOfTeamsHead;
    dummy->medium = minimum + 10;
    copy = dummy;
    while (copy->next != NULL)
    {
        if (copy->next->medium == minimum)
        {
            Team *todelete = copy->next;
            deleteTheTeam(&todelete);
            todelete = NULL;
            if(copy -> next -> next == NULL){
                copy -> next = NULL;
            }
            else {
                copy -> next = copy -> next -> next;
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

void createTheLeaderboard(WinnersList **leaderboard, WinnersTree *BinarySearchTreeRoot)
{
    if (BinarySearchTreeRoot != NULL)
    {
        createTheLeaderboard(&*leaderboard, BinarySearchTreeRoot->right);
        WinnersList *winnerToAdd = NULL;
        winnerToAdd = (WinnersList *)malloc(sizeof(WinnersList));
        winnerToAdd->nameOfWinnersTeam = (char *)malloc((strlen(BinarySearchTreeRoot->nameOfTeam) + 1));
        strcpy(winnerToAdd->nameOfWinnersTeam, BinarySearchTreeRoot->nameOfTeam);
        winnerToAdd->points = BinarySearchTreeRoot->points;
        winnerToAdd->next = NULL;
        addTheWinners(&*leaderboard, winnerToAdd);
        createTheLeaderboard(&*leaderboard, BinarySearchTreeRoot->left);
    }
}

Team *deleteTheList(Team *listOfTeamsHead)
{
    while (listOfTeamsHead != NULL)
    {
        Team *teamToDelete = listOfTeamsHead;
        listOfTeamsHead = listOfTeamsHead->next;
        free(teamToDelete->nameOfTeam);
        teamToDelete->nameOfTeam = NULL;
        while (teamToDelete->playersHead != NULL)
        {
            Player *playerToDelete = teamToDelete->playersHead;
            teamToDelete->playersHead = teamToDelete->playersHead->next;
            free(playerToDelete->firstName);
            free(playerToDelete->secondName);
            playerToDelete->firstName = NULL;
            playerToDelete->secondName = NULL;
            free(playerToDelete);
            playerToDelete = NULL;
        }
        teamToDelete -> playersHead = NULL;
    }
    return listOfTeamsHead;
}

WinnersList *deleteWinners(WinnersList *winnersList){
    while(winnersList != NULL){
        WinnersList *winnerToDelete = winnersList;
        winnersList = winnersList -> next;
        free(winnerToDelete -> nameOfWinnersTeam);
        winnerToDelete -> nameOfWinnersTeam = NULL;
        free(winnerToDelete);
        winnerToDelete = NULL;
    }
    return winnersList;
}

double getTheMinimum(Team* listOfTeamsHead){
    Team *copy = listOfTeamsHead;
    double minimum = copy->medium;
    while (copy != NULL)
    {
        if (minimum > copy->medium)
        {
            minimum = copy->medium;
        }
        copy = copy->next;
    }
    return minimum;
}