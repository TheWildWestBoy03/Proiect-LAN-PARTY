#include "Player.h"
typedef int Data;

typedef struct Team{
    Data numberOfMembers;
    char *nameOfTeam;
    struct Team *next; 
    Player *playersHead;
    float medium;
}Team;

typedef struct WinnersList{
    char *nameOfWinnersTeam;
    float points;
    struct WinnersList *next;
}WinnersList;

void addingAtBeginning(Team **listOfTeamHead, Team **current);
void addTheTeams(Team **listOfTeamHead, int numberOfTeams, FILE *teamsfile);
void addingPlayer(Player **playerHead, Player *currentPlayer);
void displayThePlayers(Player *playerHead, FILE **outputFile);
void deleteTheTeam(Team **current);
void displayTheList(Team *listOfTeamHead, FILE **outputFile);
void eliminateTheTeamsUtil(Team **listOfTeamsHead, int *numberOfTeams, FILE **outputFile);
void eliminateTheTeams(Team **ListOfTeamsHead);
void openTheFile(FILE **input, char *mode, char *nameOfFile);
void closeTheFile(FILE **input);
int readTheRequests(FILE **requestsFile, int positionOfTheLastRequest, char *argv[]);
void readingData(int lastRequest, int *numberOfTeams, FILE **teamsFile, Team **listOfTeamsHead, char *argv[]);
void addTheWinners(WinnersList **winnersListHead, WinnersList *currentTeam);