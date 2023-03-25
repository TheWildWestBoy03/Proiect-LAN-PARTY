/*
    In this file, i defined the body of the most important functions for 
    manipulating the lists.
*/
#include "listOfTeams.h"
#include <string.h>
void addingAtBeginning(Team **listOfTeamHead, Data numberOfMembers, char *nameOfTeam, Team *current){
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
    Team *current = (Team*) malloc(sizeof(Team));
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
            strcpy(listOfMembers[j], bufferNameOfMember);
        }
        current -> next = NULL;
        current -> numberOfMembers = numberOfMembers;
        (*current).nameOfTeam = (char*) malloc(sizeof(char)*strlen(nameOfTeam));
        strcpy(current -> nameOfTeam, nameOfTeam);
        (*current).nameOfColleagues = (char**)malloc(sizeof(char*) * numberOfMembers);
        for(int j = 0; j < numberOfMembers; j++){
            current->nameOfColleagues[j] = (char*)malloc(strlen(listOfMembers[j]));
            strcpy(current -> nameOfColleagues[j], listOfMembers[j]);
        }
        addingAtBeginning(&*listOfTeamHead, numberOfMembers, nameOfTeam, current);
    }
}

void displayTheList(Team *listOfTeamHead){
    if(listOfTeamHead == NULL){
        return ;
    }
    while(listOfTeamHead != NULL){
        printf("The name of team is: ");
        printf("%s.\n", listOfTeamHead -> nameOfTeam);
        printf("--------------------- \n");
        for(int i=0; i<listOfTeamHead -> numberOfMembers; i++){
            printf("%s \n", listOfTeamHead -> nameOfColleagues[i]);
        }
        printf("--------------------- \n");
        printf("%d \n", listOfTeamHead -> numberOfMembers);
        listOfTeamHead = listOfTeamHead -> next;
    }
    return;
}