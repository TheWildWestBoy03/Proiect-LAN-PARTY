/*
    In this file, i defined the body of the most important functions for 
    manipulating the lists.
*/
#include "listOfTeams.h"

void addingAtBeginning(Team **listOfTeamHead, Data numberOfMembers, char *nameOfTeam){
    Team *current = (Team*)malloc(sizeof(Team));
    char bufferNameTeam[50];
    current -> next = NULL;
    current -> numberOfMembers = numberOfMembers;
    current -> nameOfTeam = (char*) malloc(sizeof(char)*strlen(nameOfTeam));
    if(*listOfTeamHead == NULL){
        *listOfTeamHead = current;
        return;   
    }
    else{
        current -> next = *listOfTeamHead;
        *listOfTeamHead = current;
        return;
    }
}
