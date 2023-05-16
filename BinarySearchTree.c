#include "BinarySearchTree.h"

WinnersTree *createTheNode(char *nameOfTeam, float points)
{
    WinnersTree *winnersTreeNode = (WinnersTree *)malloc(sizeof(WinnersTree));
    winnersTreeNode->nameOfTeam = (char *)malloc(strlen(nameOfTeam) + 1);
    strcpy(winnersTreeNode->nameOfTeam, nameOfTeam);
    winnersTreeNode->left = winnersTreeNode->right = NULL;
    winnersTreeNode->points = points;
    return winnersTreeNode;
}
int max(int x, int y)
{
    return (x >= y) ? x : y;
}
WinnersTree *addTeamInTree(WinnersTree *BinarySearchTreeRoot, char *nameOfTeam, float points)
{
    if (BinarySearchTreeRoot == NULL)
    {
        BinarySearchTreeRoot = createTheNode(nameOfTeam, points);
    }
    if (BinarySearchTreeRoot->points > points)
    {
        BinarySearchTreeRoot->right = addTeamInTree(BinarySearchTreeRoot->right, nameOfTeam, points);
    }
    if (BinarySearchTreeRoot->points < points)
    {
        BinarySearchTreeRoot->left = addTeamInTree(BinarySearchTreeRoot->left, nameOfTeam, points);
    }
    if (BinarySearchTreeRoot->points == points)
    {
        if (strcmp(BinarySearchTreeRoot->nameOfTeam, nameOfTeam) > 0)
        {
            BinarySearchTreeRoot->right = addTeamInTree(BinarySearchTreeRoot->right, nameOfTeam, points);
        }
        else if (strcmp(BinarySearchTreeRoot->nameOfTeam, nameOfTeam) < 0)
        {
            BinarySearchTreeRoot->left = addTeamInTree(BinarySearchTreeRoot->left, nameOfTeam, points);
        }
    }
    return BinarySearchTreeRoot;
}

void inorder(WinnersTree *BinarySearchTreeRoot, FILE **outputFile)
{
    if (BinarySearchTreeRoot != NULL)
    {
        inorder(BinarySearchTreeRoot->left, &*outputFile);
        int index = strlen(BinarySearchTreeRoot->nameOfTeam);
        fprintf(*outputFile, "%s", BinarySearchTreeRoot->nameOfTeam);
        while (index < 34)
        {
            fputc(' ', *outputFile);
            index++;
        }
        fprintf(*outputFile, "-  ");
        fprintf(*outputFile, "%.2f\n", BinarySearchTreeRoot->points);
        inorder(BinarySearchTreeRoot->right, &*outputFile);
    }
}

void deleteTheTree(WinnersTree **BinarySearchTreeRoot)
{
    if ((*BinarySearchTreeRoot) != NULL)
    {
        deleteTheTree(&((*BinarySearchTreeRoot)->left));
        deleteTheTree(&((*BinarySearchTreeRoot)->right));
        free((*BinarySearchTreeRoot)->nameOfTeam);
        (*BinarySearchTreeRoot)->nameOfTeam = NULL;
        (*BinarySearchTreeRoot)->left = (*BinarySearchTreeRoot)->right = NULL;
        free((*BinarySearchTreeRoot));
    }
    *BinarySearchTreeRoot = NULL;
}

<<<<<<< HEAD
AVLNode *createAVLNode(char *nameOfTeam, double points)
{
    AVLNode *avlWinnerNode = (AVLNode *)malloc(sizeof(AVLNode));
    avlWinnerNode->left = avlWinnerNode->right = NULL;
    avlWinnerNode->nameOfTeam = (char *)malloc(strlen(nameOfTeam) + 1);
    strcpy(avlWinnerNode->nameOfTeam, nameOfTeam);
    avlWinnerNode->points = points;
    avlWinnerNode->nodeHeight = 1;
=======
AVLNode *createAVLNode(char *nameOfTeam, float points){
    AVLNode *avlWinnerNode = (AVLNode*)malloc(sizeof(AVLNode));
    avlWinnerNode -> left = avlWinnerNode -> right = NULL;
    avlWinnerNode -> nameOfTeam = (char*)malloc(strlen(nameOfTeam)+1);
    strcpy(avlWinnerNode -> nameOfTeam, nameOfTeam);
    avlWinnerNode -> points = points;
    avlWinnerNode -> nodeHeight = 1;
>>>>>>> parent of d755007 (All requests for this homework are done. Still i need to delete the date structures.)
    return avlWinnerNode;
}

int getTheHeight(AVLNode *AVLRoot)
{
    if (AVLRoot == NULL)
    {
        return 0;
    }
    return AVLRoot->nodeHeight;
}

AVLNode *rotateToRight(AVLNode *rootSubtree)
{
    AVLNode *leftNode = rootSubtree->left;
    AVLNode *rightSubtreeNode = leftNode->right;
    leftNode->right = rootSubtree;
    rootSubtree->left = rightSubtreeNode;
    rootSubtree->nodeHeight = max(getTheHeight(rootSubtree->left), getTheHeight(rootSubtree->right)) + 1;
    leftNode->nodeHeight = max(getTheHeight(leftNode->left), getTheHeight(leftNode->right)) + 1;
    return leftNode;
}
AVLNode *rotateToLeft(AVLNode *rootSubtree)
{
    AVLNode *rightNode = rootSubtree->right;
    AVLNode *leftSubtreeNode = rightNode->left;
    rightNode->left = rootSubtree;
    rootSubtree->right = leftSubtreeNode;
    rootSubtree->nodeHeight = max(getTheHeight(rootSubtree->left), getTheHeight(rootSubtree->right)) + 1;
    rightNode->nodeHeight = max(getTheHeight(rightNode->left), getTheHeight(rightNode->right)) + 1;
    return rightNode;
}
AVLNode *leftRightRotate(AVLNode *AVLRoot){
    AVLRoot->left = rotateToLeft(AVLRoot->left);
    return rotateToRight(AVLRoot);
}
AVLNode *rightLeftRotate(AVLNode *AVLRoot){
    AVLRoot -> right = rotateToRight(AVLRoot->right);
    return rotateToLeft(AVLRoot);
}
int getBalance(AVLNode *subtreeNode)
{
    if (subtreeNode == NULL)
    {
        return 0;
    }
    return getTheHeight(subtreeNode->left) - getTheHeight(subtreeNode->right);
}
<<<<<<< HEAD
AVLNode *insertInAVL(AVLNode *AVLRoot, char *nameOfTeam, double points)
{
    if (AVLRoot == NULL)
    {
=======
AVLNode *insertInAVL(AVLNode *AVLRoot, char *nameOfTeam, float points){
    if(AVLRoot == NULL){
>>>>>>> parent of d755007 (All requests for this homework are done. Still i need to delete the date structures.)
        AVLRoot = createAVLNode(nameOfTeam, points);
    }
    if (AVLRoot->points < points)
    {
        AVLRoot->left = insertInAVL(AVLRoot->left, nameOfTeam, points);
    }
    else if (AVLRoot->points > points)
    {
        AVLRoot->right = insertInAVL(AVLRoot->right, nameOfTeam, points);
    }
    else if (AVLRoot->points == points)
    {

        if (strcmp((AVLRoot->nameOfTeam), nameOfTeam) > 0)
        {
            AVLRoot->right = insertInAVL(AVLRoot->right, nameOfTeam, points);
        }
        else if (strcmp((AVLRoot->nameOfTeam), nameOfTeam) < 0)
        {
            AVLRoot->left = insertInAVL(AVLRoot->left, nameOfTeam, points);
        }
    }
    AVLRoot->nodeHeight = 1 + max(getTheHeight(AVLRoot->left), getTheHeight(AVLRoot->right));

    int balance = getBalance(AVLRoot);

    if (balance < -1)
    {
        if (AVLRoot -> right -> points > points)
        {
            return rotateToLeft(AVLRoot);
        }
        if (AVLRoot -> right -> points == points)
        {
            if (strcmp(AVLRoot -> right -> nameOfTeam, nameOfTeam) > 0)
            {
                return rotateToLeft(AVLRoot);
            }
            else if (strcmp(AVLRoot -> right -> nameOfTeam, nameOfTeam) < 0)
            {
               return rightLeftRotate(AVLRoot);
            }
        }
        if (AVLRoot -> right -> points < points)
        {
            return rightLeftRotate(AVLRoot);
        }
    }

    if (balance > 1)
    {
        if (points < AVLRoot -> left -> points)
        {
            return leftRightRotate(AVLRoot);
        }
        if (AVLRoot->points == points)
        {
            if (strcmp(AVLRoot -> left -> nameOfTeam, nameOfTeam) > 0)
            {
               return leftRightRotate(AVLRoot);
            }
            else if (strcmp(AVLRoot->nameOfTeam, nameOfTeam) < 0)
            {
                return rotateToRight(AVLRoot);
            }
        }
        if (AVLRoot -> left -> points < points)
        {
            return rotateToRight(AVLRoot);
        }
    }
    return AVLRoot;
}

void deleteAVLTree(AVLNode *AVLRoot){
    if(AVLRoot != NULL){
        deleteAVLTree(AVLRoot -> left);
        deleteAVLTree(AVLRoot -> right);
        free(AVLRoot -> nameOfTeam);
        AVLRoot -> nameOfTeam = NULL;
        free(AVLRoot);
    }
}