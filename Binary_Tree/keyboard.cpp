#include <GL/glut.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "binary_tree.h"
#include "keyboard.h"
#include "List.h"
#include "const.h"


void Keyboard(unsigned char key, int x, int y){
    system("cls");
    printf("aTree with a count (%d)\n", aTree->count);

    switch (key)    {
        case '1':
            printf("Straight method:\n");
            printTree(aTree, straight);
            break;

        case '2':
            printf("Symmetry method:\n");
            printTree(aTree, symmetry);
            break;

        case '3':
            printf("Backward method:\n");
            printTree(aTree, backward);
            break;

        case 'e':
            exit(0);
            break;
    }
}

void SKeyboard(int key, int x, int y){
    system("cls");
    TreeNode *aNodeToDelete = NULL;

    switch (key)    {
        case GLUT_KEY_LEFT:

           //delete left child of the root
            aNodeToDelete = aTree->root->leftChild;
            if (aTree->count > 1 && aNodeToDelete != NULL )            {
                deleteNodeWithValue(aTree, aNodeToDelete->value);
                printf("Root->leftChild was deleted!");
            }
            else            {
                printf("Root->leftChild don't exist!");
            }

            break;

        case GLUT_KEY_RIGHT:

            //delete right child of the root
            aNodeToDelete = aTree->root->rightChild;
            if (aTree->count > 1 && aNodeToDelete != NULL ){
                deleteNodeWithValue(aTree, aNodeToDelete->value);
                printf("Root->rightChild was deleted!");
            }
            else{
                printf("Root->rightChild don't exist!");
            }

            break;

        case GLUT_KEY_UP:

            //filling aTree with amount == const
            //initialization in the const.c
            while (aTree->count < amount){
                insertIntValueToTree(aTree, randomIntFromRange(min, max));
            }
            printf("aTree have MAX_AMOUNT");

            break;

        case GLUT_KEY_DOWN:

             //insert 1 Node
            if (aTree->count < amount){
                while ( 1 ){
                    if (0 == insertIntValueToTree(aTree, randomIntFromRange(min, max))){
                        printf("a TreeNode was inserted!");
                        break;
                    }
                }
            }
            else{
                printf("aTree have MAX_AMOUNT");
            }
            break;
    }
    printf("\naTree->count = %d", aTree->count);
}

