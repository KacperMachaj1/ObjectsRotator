#include <SDL2/SDL.h>

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <float.h>

#include "objectGenerator.h"
#include "constants.h"
#include "colorUtils.h"
#include "tableUtils.h"
#include "vectorUtils.h"

void displayObjects(float ***objectsArray, SDL_Renderer *renderer, float *rotationVector, int **colorArray, float **displayTable);

void setPixel(SDL_Renderer *renderer, int x, int y, Uint8 r, Uint8 g, Uint8 b);

int main(int argc, char **argv)
{
    // Create the array contatining all objects
    float ***objectsArray = generateSquare(OBJECTSIZE);

    int **colorArray = createColorArray(NUMBEROFOBJECTS);
    randomizeColors(NUMBEROFOBJECTS, colorArray);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());

        return 1;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow("Objects Rotator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    float *rotationVector = (float *)calloc(1, sizeof(float) * 3);

    // SETUP OF THE DISPLAY TABLE
    float **displayTable = createTable(WIDTH, HEIGHT);
    resetTable(displayTable, WIDTH, HEIGHT, -FLT_MAX);

    // Main loop
    SDL_Event event;
    int running = 1;
    while (running)
    {

        Uint32 frameStart = SDL_GetTicks();

        // Process events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 36, 107, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Resets the displayTable table
        resetTable(displayTable, WIDTH, HEIGHT, -FLT_MAX);

        // Display the object on the screen
        displayObjects(objectsArray, renderer, rotationVector, colorArray, displayTable);

        // Update the screen
        SDL_RenderPresent(renderer);

        rotationVector[0] = rotationVector[0] + 5;
        rotationVector[1] = rotationVector[1] + 3;
        rotationVector[2] = rotationVector[2] + 1;

        // Handle Framerate
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_TIME)
        {
            SDL_Delay(FRAME_TIME - frameTime);
        }
    }

    // SDL Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // Objects Cleanup
    freeObjectArray(OBJECTSIZE, objectsArray[0]);
    free(rotationVector);
    free(objectsArray);

    // Colors Cleanup
    freeColorArray(NUMBEROFOBJECTS, colorArray);

    // Cleanup of the display table
    freeTable(displayTable, WIDTH, HEIGHT);

    return 0;
}

void displayObjects(float ***objectsArray, SDL_Renderer *renderer, float *rotationVector, int **colorArray, float **displayTable)
{
    float *vectorBuffer = (float *)malloc(3 * sizeof(float));

    for (int i = 0; i < NUMBEROFOBJECTS; i++)
    {
        for (int j = 0; j < OBJECTSIZE * OBJECTSIZE; j++)
        {
            memcpy(vectorBuffer, objectsArray[i][j], 3 * sizeof(float));
            rotateVector(vectorBuffer, rotationVector);

            int x = round(vectorBuffer[0] + WIDTH / 2);
            int y = round(HEIGHT - (vectorBuffer[1] + HEIGHT / 2));
            float z = vectorBuffer[2];
            // int random_bool = rand() % 1;
            // if (!random_bool)
            // {
            if ((x > 0 && x < WIDTH) && (y > 0 && y < HEIGHT))
            {
                if (z > displayTable[x][y])
                {
                    displayTable[x][y] = z;
                    setPixel(renderer, x, y, colorArray[i][0], colorArray[i][1], colorArray[i][2]);
                }
            }

            // setPixel(renderer, floor(vectorBuffer[0] + WIDTH / 2), floor(HEIGHT - (vectorBuffer[1] + HEIGHT / 2)), colorArray[i][0], colorArray[i][1], colorArray[i][2]);
        }
    }
}

void setPixel(SDL_Renderer *renderer, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(renderer, x, y);
}
