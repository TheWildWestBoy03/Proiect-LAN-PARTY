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
int max(int x, int y){
    return (x >= y)? x : y;
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

void deleteTheTree(WinnersTree **BinarySearchTreeRoot){
    if( (*BinarySearchTreeRoot) != NULL){
        deleteTheTree(&((*BinarySearchTreeRoot) -> left));
        deleteTheTree(&((*BinarySearchTreeRoot) -> right));
        free( (*BinarySearchTreeRoot) -> nameOfTeam);
        (*BinarySearchTreeRoot) -> nameOfTeam = NULL;
        (*BinarySearchTreeRoot) -> left = (*BinarySearchTreeRoot) -> right = NULL;
        free((*BinarySearchTreeRoot));
    }
    *BinarySearchTreeRoot = NULL;
}

AVLNode *createAVLNode(char *nameOfTeam, float points){
    AVLNode *avlWinnerNode = (AVLNode*)malloc(sizeof(AVLNode));
    avlWinnerNode -> left = avlWinnerNode -> right = NULL;
    avlWinnerNode -> nameOfTeam = (char*)malloc(strlen(nameOfTeam)+1);
    strcpy(avlWinnerNode -> nameOfTeam, nameOfTeam);
    avlWinnerNode -> points = points;
    avlWinnerNode -> nodeHeight = 1;
    return avlWinnerNode;
}

int getTheHeight(AVLNode *AVLRoot){
    if(AVLRoot == NULL){
        return 0;
    }
    return AVLRoot -> nodeHeight;
}

AVLNode *rotateToRight(AVLNode *rootSubtree){
    AVLNode *leftNode = rootSubtree -> left;
    AVLNode *rightSubtreeNode = leftNode -> right;
    leftNode -> right = rootSubtree; 
    rootSubtree -> left = rightSubtreeNode;
    rootSubtree -> nodeHeight = max(getTheHeight(rootSubtree -> left), getTheHeight(rootSubtree -> right)) + 1;
    leftNode -> nodeHeight = max(getTheHeight(leftNode -> left), getTheHeight(leftNode -> right)) + 1;
    return leftNode;
}
AVLNode *rotateToLeft(AVLNode *rootSubtree){
    AVLNode *rightNode = rootSubtree -> right;
    AVLNode *leftSubtreeNode = rightNode -> left;
    rightNode -> left = rootSubtree;
    rootSubtree -> right = leftSubtreeNode;
    rootSubtree -> nodeHeight = max(getTheHeight(rootSubtree -> left), getTheHeight(rootSubtree -> right)) + 1;
    rightNode -> nodeHeight = max(getTheHeight(leftNode -> left), getTheHeight(leftNode -> right)) + 1;
    return rightNode;
}

int getBalance(AVLNode *subtreeNode){
    if(subtreeNode == NULL){
        return 0;
    }
    return height(subtreeNode -> left, subtreeNode -> right);
}
AVLNode *insert(AVLNode *AVLRoot, char *nameOfTeam, float points){
    if(AVLRoot == NULL){
        AVLRoot = createAVLNode(nameOfTeam, points);
    }
    if(AVLRoot -> points < points){
        AVLRoot -> left = insert(AVLRoot -> left, points);
    }
    else if(AVLRoot -> points > points){
        AVLRoot -> right = insert(AVLRoot -> right, points);
    }
    else if(AVLRoot -> points > points){
        if(strcmp((AVLRoot -> nameOfTeam), nameOfTeam) == 0){
            return AVLRoot;
        }
        else if(strcmp((AVLRoot -> nameOfTeam), nameOfTeam) > 0){
            AVLRoot -> right = insert(AVLRoot -> right, points);
        }
        else{
            AVLRoot -> left = insert(AVLRoot -> left, points);
        }
    }

    int balance = getBalance(AVLRoot);

    if(balance < -1){
        if(AVLRoot -> points > points){
            rotateToLeft(AVLRoot);
        }
        if(AVLRoot -> points == points){
            if(strcmp(AVLRoot -> nameOfTeam, nameOfTeam) < 0){
                rotateToLeft(AVLRoot);
            }
            else if(strcmp(AVLRoot -> nameOfTeam, nameOfTeam) < 0){
                AVLRoot -> left = rotateToLeft(AVLRoot -> left)
                rotateToRight(AVLRoot);
            }
        }
    }
    
    if(balance < -1){
        if(AVLRoot -> points < points){
            AVLRoot -> right = rotateToRight(AVLRoot -> right);
            rotateToLeft(AVLRoot);
        }
        if(AVLRoot -> points == points){
            if(strcmp(AVLRoot -> nameOfTeam, nameOfTeam) > 0){
                AVLRoot -> right = rotateToRight(AVLRoot -> right);
                rotateToLeft(AVLRoot);
            }
        }
    }

    
    if(balance > 1){
        if(AVLRoot -> points > points){
            AVLRoot -> left = rotateToLeft(AVLRoot -> left);
            rotateToRight(AVLRoot);
        }
        if(AVLRoot -> points == points){
            if(strcmp(AVLRoot -> nameOfTeam, nameOfTeam) > 0){
                AVLRoot -> left = rotateToLeft(AVLRoot -> left);
                rotateToRight(AVLRoot);
            }
        }
    }
    
    if(balance > 1){
        if(AVLRoot -> points > points){
            AVLRoot -> left = rotateToLeft(AVLRoot -> left);
            rotateToRight(AVLRoot);
        }
        if(AVLRoot -> points == points){
            if(strcmp(AVLRoot -> nameOfTeam, nameOfTeam) > 0){
                rotateToLeft(AVLRoot);
            }
            else if(strcmp(AVLRoot -> nameOfTeam, nameOfTeam) < 0){
                AVLRoot -> left = rotateToLeft(AVLRoot -> left)
                rotateToRight(AVLRoot);
            }
        }
    }
    if(balance > 1){
        if(AVLRoot -> points < points){

        }
    }
}