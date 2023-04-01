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