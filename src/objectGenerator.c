#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "objectGenerator.h"

float **generateObjectArray(int sizeOfObject)
{
    // An object is a 2d array with n*n 3d vectors
    int numberOfVectors = sizeOfObject * sizeOfObject;

    // Allocate memory for top level array
    float **objectArray = (float **)malloc(numberOfVectors * sizeof(float *));

    if (objectArray == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 0;
    }

    // Allocate memory for each vector
    for (int i = 0; i < numberOfVectors; i++)
    {
        objectArray[i] = (float *)malloc(3 * sizeof(float));
        if (objectArray[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            // Free previously allocated rows
            for (int j = 0; j < i; j++)
            {
                free(objectArray[j]);
            }
            free(objectArray);
            return 0;
        }
    }

    printf("Object array generated succesfully\n");

    return objectArray;
}

int freeObjectArray(int sizeOfObject, float **objectArray)
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

int moveObjectRight(int sizeOfObject, float **objectArray, int displacement)
{
    for (int i = 0; i < sizeOfObject * sizeOfObject; i++)
    {
        objectArray[i][0] = objectArray[i][0] + displacement;
    }
    return 0;
}

int moveObjectUp(int sizeOfObject, float **objectArray, int displacement)
{
    for (int i = 0; i < sizeOfObject * sizeOfObject; i++)
    {
        objectArray[i][1] = objectArray[i][1] + displacement;
    }
    return 0;
}
