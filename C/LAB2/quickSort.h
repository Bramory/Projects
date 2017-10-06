//
//  quickSort.h
//  demoSimpleSort
//
//  Created by Slava Gubar on 4/27/16.
//  Copyright © 2016 Slava Gubar. All rights reserved.
//

#ifndef quickSort_h
#define quickSort_h

#include <stdio.h>

int partitionIt(char anArray[], int aLeftIndex, int aRightIndex, char aPivot);
void quickSort(char anArray[], int aLeftIndex, int aRightIndex);
void quickSort2(char anArray[], int aLeftIndex, int aRightIndex);

#endif /* quickSort_h */
