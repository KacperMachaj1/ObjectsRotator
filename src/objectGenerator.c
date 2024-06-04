#include <stdio.h>
#include <stdlib.h>

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