#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinarySearchTreeNode{
    char *nameOfTeam;
    float points;
    struct BinarySearchTreeNode *left, *right;
}WinnersTree;

WinnersTree *createTheNode(char *nameOfTeam, float points);
WinnersTree *addTeamInTree(WinnersTree *BinarySearchTreeRoot, char *nameOfTeam, float points);
void inorder(WinnersTree *BinarySearchTreeRoot, FILE **outputFile);