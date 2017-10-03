#include <GL/glut.h>
#include <cstdlib>
#include <stdio.h>

#include "binary_tree.h"
#include "List.h"
#include "mouse.h"
#include "const.h"


void MousePressed(int button, int state, int x, int y){
    bool down = false;
    LinkNode *aLinkNode = aList->head;
    TreeNode *aChosenTreeNode;
    if (state == down )    {
        system("cls");
        switch(button)
        {
            case GLUT_LEFT_BUTTON:
                //glutSetWindowTitle("LeftButtonPressed");
                aChosenTreeNode = MarkNodeToDelete(aTree, aList, x, y);
                analysis( aChosenTreeNode );
                printf("\n\naList to delete:\n");
                PrintList(aList);
                break;

            case GLUT_MIDDLE_BUTTON:
                //glutSetWindowTitle("MiddleButtonPressed");
                    destroyIntTree(aTree);
                    aTree = getIntTreeWithRandValues(1, 0);

                printf("You get a New Binary Tree!");

            //delete all chosen TreeNodes
            case GLUT_RIGHT_BUTTON:
                //glutSetWindowTitle("RightButtonPressed");
                 while(aList->count >= 1)                {
                    deleteNodeWithValue(aTree, aLinkNode->value);
                    aLinkNode = aLinkNode->next;
                    DeleteIntValueAtIndex(aList, 0);
                }
                printf("\naTree->count = %d", aTree->count);
                break;

                break;
        }
    }
}

void MouseMove(int ax, int ay){
    x = ax;
    y = ay;
    //glutSetWindowTitle("MouseMove");
//    printf("X = %d\n", x);
//    printf("Y = %d\n", y);
}


void MousePressedMove(int ax, int ay){
    x = ax;
    y = ay;
    //glutSetWindowTitle("MousePressedMove");
}
