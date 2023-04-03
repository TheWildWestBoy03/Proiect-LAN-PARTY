#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WinnersTree{
    char *nameOfTeam;
    float points;
    struct WinnersTree *left, *right;
}WinnersTree;

typedef struct AVLNodeBuilding{
    char *nameOfTeam;
    float points;
    struct AVLNode *left, *right;
    int nodeHeight;
}AVLNode;
WinnersTree *createTheNode(char *nameOfTeam, float points);
WinnersTree *addTeamInTree(WinnersTree *BinarySearchTreeRoot, char *nameOfTeam, float points);
void inorder(WinnersTree *BinarySearchTreeRoot, FILE **outputFile);
void deleteTheTree(WinnersTree **BinarySearchTreeRoot);
AVLNode *createAVLNode(char *nameOfTeam, float points);
int getTheHeight(AVLNode *AVLRoot);
AVLNode *rotateToRight(AVLNode *rootSubtree);
AVLNode *rotateToLeft(AVLNode *rootSubtree);
AVLNode *insert(AVLNode *AVLRoot, char *nameOfTeam, float points);
int max(int x, int y);