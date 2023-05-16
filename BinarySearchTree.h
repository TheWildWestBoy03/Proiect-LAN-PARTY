#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct WinnersTree
{
    char *nameOfTeam;
    float points;
    struct WinnersTree *left, *right;
} WinnersTree;

typedef struct AVLNodeBuilding
{
    char *nameOfTeam;
    float points;
    struct AVLNodeBuilding *left, *right;
    int nodeHeight;
} AVLNode;

WinnersTree *createTheNode(char *nameOfTeam, float points);
WinnersTree *addTeamInTree(WinnersTree *BinarySearchTreeRoot, char *nameOfTeam, float points);
void inorder(WinnersTree *BinarySearchTreeRoot, FILE **outputFile);
void deleteTheTree(WinnersTree **BinarySearchTreeRoot);
AVLNode *createAVLNode(char *nameOfTeam, float points);
int getTheHeight(AVLNode *AVLRoot);
AVLNode *rotateToRight(AVLNode *rootSubtree);
AVLNode *rotateToLeft(AVLNode *rootSubtree);
<<<<<<< HEAD
AVLNode *insertInAVL(AVLNode *AVLRoot, char *nameOfTeam, double points);
int max(int x, int y);
AVLNode *leftRightRotate(AVLNode *AVLRoot);
AVLNode *rightLeftRotate(AVLNode *AVLRoot);
=======
AVLNode *insertInAVL(AVLNode *AVLRoot, char *nameOfTeam, float points);
int max(int x, int y);
>>>>>>> parent of d755007 (All requests for this homework are done. Still i need to delete the date structures.)
