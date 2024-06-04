#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "objectGenerator.h"

int **generateObjectArray(int sizeOfObject)
{
    // An object is a 2d array with n*n 3d vectors
    int numberOfVectors = sizeOfObject * sizeOfObject;

    // Allocate memory for top level array
    int **matrix = (int **)malloc(numberOfVectors * sizeof(int *));
    if (matrix == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 0;
    }

    // Allocate memory for each vector
    for (int i = 0; i < numberOfVectors; i++)
    {
        matrix[i] = (int *)malloc(3 * sizeof(int));
        if (matrix[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            // Free previously allocated rows
            for (int j = 0; j < i; j++)
            {
                free(matrix[j]);
            }
            free(matrix);
            return 0;
        }
    }

    printf("Object array generated succesfully\n");

    return matrix;
}

int freeObjectArray(int sizeOfObject, int **objectArray)
{
    // An object is a 2d array with n*n 3d vectors
    int numberOfVectors = sizeOfObject * sizeOfObject;

    for (int i = 0; i < numberOfVectors; i++)
    {
        free(objectArray[i]);
    }
    free(objectArray);

    return 0;
}

int transformObjectArrayToSquare(int sizeOfObject, int **objectArray)
{
    for (int i = 0; i < sizeOfObject; i++)
    {
        for (int j = 0; j < sizeOfObject; j++)
        {
            int currentIndex = j + i * sizeOfObject;
            int *currentVector = objectArray[currentIndex];
            currentVector[0] = i;
            currentVector[1] = j;
            currentVector[2] = 0;
        }
    }
    return 0;
}

int printObjectArray(int sizeOfObject, int **objectArray)
{
    int numberOfVectors = sizeOfObject * sizeOfObject;

    printf("Vectors:\n");

    for (int i = 0; i < numberOfVectors; i++)
    {
        printf("%d,%d,%d\n", objectArray[i][0], objectArray[i][1], objectArray[i][2]);
    }
    return 0;
}

int centerObjectArray(int sizeOfObject, int **objectArray)
{
    for (int i = 0; i < sizeOfObject * sizeOfObject; i++)
    {
        objectArray[i][0] = objectArray[i][0] - sizeOfObject / 2;
        objectArray[i][1] = objectArray[i][1] - sizeOfObject / 2;
    }
}

int moveObjectRight(int sizeOfObject, int **objectArray, int displacement)
{
    for (int i = 0; i < sizeOfObject * sizeOfObject; i++)
    {
        objectArray[i][0] = objectArray[i][0] + displacement;
    }
}

int moveObjectUp(int sizeOfObject, int **objectArray, int displacement)
{
    for (int i = 0; i < sizeOfObject * sizeOfObject; i++)
    {
        objectArray[i][1] = objectArray[i][1] + displacement;
    }
}

int objectYawRotation(int sizeOfObject, int **objectArray, float angle)
{
    for (int i = 0; i < sizeOfObject * sizeOfObject; i++)
    {
        objectArray[i][0] = floor(objectArray[i][0] * cos(angle) - objectArray[i][1] * sin(angle));
        objectArray[i][1] = floor(objectArray[i][0] * sin(angle) + objectArray[i][1] * cos(angle));
    }
    return 0;
}