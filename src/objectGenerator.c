#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "objectGenerator.h"
#include "tableUtils.h"

float **generateObjectArray(int sizeOfObject)
{
    // An object is a 2d array with n*n 3d vectors
    int numberOfVectors = sizeOfObject * sizeOfObject;

    return createTable(numberOfVectors, 3);
}

int freeObjectArray(int sizeOfObject, float **objectArray)
{
    // An object is a 2d array with n*n 3d vectors
    int numberOfVectors = sizeOfObject * sizeOfObject;

    freeTable(objectArray, numberOfVectors, 3);

    return 0;
}

int transformObjectArrayToSquare(int sizeOfObject, float **objectArray)
{
    for (int i = 0; i < sizeOfObject; i++)
    {
        for (int j = 0; j < sizeOfObject; j++)
        {
            int currentIndex = j + i * sizeOfObject;
            float *currentVector = objectArray[currentIndex];
            currentVector[0] = i;
            currentVector[1] = j;
            currentVector[2] = 0;
        }
    }
    return 0;
}

int printObjectArray(int sizeOfObject, float **objectArray)
{
    int numberOfVectors = sizeOfObject * sizeOfObject;

    printf("Vectors:\n");

    for (int i = 0; i < numberOfVectors; i++)
    {
        printf("%f,%f,%f\n", objectArray[i][0], objectArray[i][1], objectArray[i][2]);
    }
    return 0;
}

int centerObjectArray(int sizeOfObject, float **objectArray)
{
    for (int i = 0; i < sizeOfObject * sizeOfObject; i++)
    {
        objectArray[i][0] = objectArray[i][0] - sizeOfObject / 2;
        objectArray[i][1] = objectArray[i][1] - sizeOfObject / 2;
    }
    return 0;
}

int moveObjectRight(int sizeOfObject, float **objectArray, float displacement)
{
    for (int i = 0; i < sizeOfObject * sizeOfObject; i++)
    {
        objectArray[i][0] = objectArray[i][0] + displacement;
    }
    return 0;
}

int moveObjectUp(int sizeOfObject, float **objectArray, float displacement)
{
    for (int i = 0; i < sizeOfObject * sizeOfObject; i++)
    {
        objectArray[i][1] = objectArray[i][1] + displacement;
    }
    return 0;
}

int moveObjectFront(int sizeOfObject, float **objectArray, float displacement)
{
    for (int i = 0; i < sizeOfObject * sizeOfObject; i++)
    {
        objectArray[i][2] = objectArray[i][2] + displacement;
    }
    return 0;
}
