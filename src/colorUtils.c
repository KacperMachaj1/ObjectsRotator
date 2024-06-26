#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "colorUtils.h"

int **createColorArray(int numberOfObjects)
{
    int **toReturn = (int **)malloc(numberOfObjects * sizeof(int *));

    for (int i = 0; i < numberOfObjects; i++)
    {
        toReturn[i] = (int *)malloc(3 * sizeof(int));
    }
    return toReturn;
}

void randomizeColors(int numberOfObjects, int **colorArray)
{
    srand(time(NULL));

    for (int i = 0; i < numberOfObjects; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            colorArray[i][j] = rand() % 256;
        }
    }
    return;
}

void freeColorArray(int numberOfObjects, int **colorArray)
{
    for (int i = 0; i < numberOfObjects; i++)
    {
        free(colorArray[i]);
    }
    free(colorArray);
}
