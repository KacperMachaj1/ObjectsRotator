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
