#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WinnersTree{
    char *nameOfTeam;
    double points;
    struct WinnersTree *left, *right;
}WinnersTree;

typedef struct AVLNodeBuilding{
    char *nameOfTeam;
    double points;
    struct AVLNodeBuilding *left, *right;
    int nodeHeight;
}AVLNode;

WinnersTree *createTheNode(char *nameOfTeam, double points);
WinnersTree *addTeamInTree(WinnersTree *BinarySearchTreeRoot, char *nameOfTeam, double points);
void inorder(WinnersTree *BinarySearchTreeRoot, FILE **outputFile);
void deleteTheTree(WinnersTree **BinarySearchTreeRoot);
AVLNode *createAVLNode(char *nameOfTeam, double points);
int getTheHeight(AVLNode *AVLRoot);
AVLNode *rotateToRight(AVLNode *rootSubtree);
AVLNode *rotateToLeft(AVLNode *rootSubtree);
AVLNode *insertInAVL(AVLNode *AVLRoot, char *nameOfTeam, double points);
int max(int x, int y);
void deleteAVLTree(AVLNode *AVLRoot);