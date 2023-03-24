#include "listOfTeams.h"

int main(){
    int numberOfTeams;
    Team *listOfTeamsHead = NULL;
    FILE *teamsFiles;
    for(int i=0; i < numberOfTeams; i++){
        Data numberOfMembers;
        char *nameOfTeam;
        int x;
        printf("The number of members in this team is: ");
        scanf("%d", &x);
        numberOfMembers = x;
        addingAtBeginning(&listOfTeamsHead, numberOfMembers, nameOfTeam);
    }
}
