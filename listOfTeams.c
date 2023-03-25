/*
    In this file, i defined the body of the most important functions for 
    manipulating the lists.
*/
#include "listOfTeams.h"
#include <string.h>
void addingAtBeginning(Team **listOfTeamHead, Data numberOfMembers, char *nameOfTeam){
    Team *current = (Team*)malloc(sizeof(Team));
    char bufferNameTeam[50], bufferNameColleague[50];
    current -> next = NULL;
    current -> numberOfMembers = numberOfMembers;
    printf("%s \n", nameOfTeam);
    (*current).nameOfTeam = (char*) malloc(sizeof(char)*strlen(nameOfTeam));
    current -> nameOfTeam = nameOfTeam;
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

void addTheTeams(Team **listOfTeamHead, int numberOfTeams){
    char bufferNameOfTeam[50], *nameOfTeam, **listOfMembers;
    for (int i = 0; i < numberOfTeams; i++){
        int numberOfMembers;
        printf("How many students are in this team? \n");
        scanf("%d", &numberOfMembers);
        getchar();
        printf("What is the name of this team? ");
        scanf("%s", bufferNameOfTeam);
        getchar();
        nameOfTeam = (char*) malloc(strlen(bufferNameOfTeam));
        strcpy(nameOfTeam, bufferNameOfTeam);
        listOfMembers = (char**)malloc(sizeof(char*) * numberOfMembers);
        for(int j = 0; j < numberOfMembers; j++){
            printf("The name of the member %d is: ", j);
            char bufferNameOfMember[50];
            scanf("%s", bufferNameOfMember);
            getchar();
            listOfMembers[j] = (char*)malloc(strlen(bufferNameOfMember));
        }
        printf("\n");
        for(int j=0; j<numberOfMembers; j++){
            printf("%s \n", listOfMembers[j]);
        }
        addingAtBeginning(&*listOfTeamHead, numberOfMembers, nameOfTeam);
        free(nameOfTeam);
    }
}

void displayTheList(Team *listOfTeamHead){
    if(listOfTeamHead == NULL){
        return ;
    }
    while(listOfTeamHead != NULL){
        printf("The name of team is: ");
        printf("%s.\n", listOfTeamHead -> nameOfTeam);
        listOfTeamHead = listOfTeamHead -> next;
    }
    return;
}