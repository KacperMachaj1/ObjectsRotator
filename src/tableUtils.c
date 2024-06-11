#include <stdlib.h>
#include <stdio.h>
#include "tableUtils.h"

float **createTable(int width, int height)
{
    // Allocate memory for top level array
    float **table = (float **)malloc(width * sizeof(float *));

    if (table == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 0;
    }

    // Allocate memory for each vector
    for (int i = 0; i < width; i++)
    {
        table[i] = (float *)calloc(1, height * sizeof(float));
        if (table[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            // Free previously allocated rows
            for (int j = 0; j < i; j++)
            {
                free(table[j]);
            }
            free(table);
            return 0;
        }
    }

    return table;
}

int freeTable(float **table, int width, int height)
{

    for (int i = 0; i < width; i++)
    {
        free(table[i]);
    }
    free(table);

    return 0;
}

int resetTable(float **table, int width, int height, float newVal)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            table[i][j] = newVal;
        }
    }
    return 0;
}
