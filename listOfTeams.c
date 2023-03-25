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
    char bufferNameOfTeam[50], *nameOfTeam;
    Player *playersInTheTeam;
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
        playersInTheTeam = (Player*) malloc(sizeof(Player) * numberOfMembers);
        for(int j = 0; j < numberOfMembers; j++){
            printf("The first name of the member %d is: ", j);
            char bufferFirstNameOfMember[50], bufferSecondNameOfMember[50];
            int bufferPoints;
            scanf("%s", bufferFirstNameOfMember);
            getchar();
            printf("The second name of the member %d is: ", j);
            scanf("%s", bufferSecondNameOfMember);
            getchar();
            printf("The number of points obtained by this member is: ");
            scanf("%d", &bufferPoints);
            getchar();
            playersInTheTeam[j] . firstName = (char*) malloc(sizeof(bufferFirstNameOfMember));
            playersInTheTeam[j] . secondName = (char*) malloc(sizeof(bufferSecondNameOfMember));
            playersInTheTeam[j] . points = bufferPoints;
            
            strcpy(playersInTheTeam[j] . firstName, bufferFirstNameOfMember);
            strcpy(playersInTheTeam[j] . secondName, bufferSecondNameOfMember);
            printf("%s %s %d \n", playersInTheTeam[j] . firstName, playersInTheTeam[j] . secondName, playersInTheTeam[j] . points);
        }


        current -> next = NULL;
        current -> numberOfMembers = numberOfMembers;
        (*current).nameOfTeam = (char*) malloc(sizeof(char)*strlen(nameOfTeam));
        strcpy(current -> nameOfTeam, nameOfTeam);
        current -> playersInTeam = (Player*)malloc(sizeof(Player) * numberOfMembers);
        for(int j = 0; j < numberOfMembers; j++){
           // printf("%s %s %d \n", playersInTheTeam[j] . firstName, playersInTheTeam[j] . secondName, playersInTheTeam[j] . points);
            current -> playersInTeam[j] . points = playersInTheTeam[j] . points;
            printf("%d ", current -> playersInTeam[j].points);
            current -> playersInTeam[j] . firstName = (char*)malloc(sizeof(char)*strlen(playersInTheTeam[j] . firstName));
            current -> playersInTeam[j] . secondName = (char*)malloc(sizeof(char)*strlen(playersInTheTeam[j] . secondName));
            strcpy( current -> playersInTeam[j] . firstName, playersInTheTeam[j] . firstName);
            strcpy( current -> playersInTeam[j] . secondName, playersInTheTeam[j] . secondName);
            printf("%s ", current -> playersInTeam[j].firstName);
            printf("%s \n", current -> playersInTeam[j].secondName);
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
        printf("%s \n", listOfTeamHead -> nameOfTeam);
        printf("--------------------- \n");
        for(int i=0; i < listOfTeamHead -> numberOfMembers; i++){
            printf("%s ", listOfTeamHead -> playersInTeam[i] . firstName);
            printf("%s ", listOfTeamHead -> playersInTeam[i] . secondName);
            printf("%d \n", listOfTeamHead -> playersInTeam[i] . points);
        }
        printf("--------------------- \n");
        printf("%d \n", listOfTeamHead -> numberOfMembers);
        listOfTeamHead = listOfTeamHead -> next;
    }
    return;
}