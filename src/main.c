#include <SDL2/SDL.h>

#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "objectGenerator.h"
#include "constants.h"
#include "colorUtils.h"

void displayObjects(float ***objectsArray, SDL_Renderer *renderer, float *rotationVector, int **colorArray);

int rotateVector(float *vector, float *angle);

void setPixel(SDL_Renderer *renderer, int x, int y, Uint8 r, Uint8 g, Uint8 b);

int main(int argc, char **argv)
{
    // Create the array contatining all objects
    float ***objectsArray = (float ***)malloc(NUMBEROFOBJECTS * sizeof(float **));

    int **colorArray = createColorArray(NUMBEROFOBJECTS);
    randomizeColors(NUMBEROFOBJECTS, colorArray);

    // Initialize front
    objectsArray[0] = (float **)generateObjectArray(OBJECTSIZE);
    transformObjectArrayToSquare(OBJECTSIZE, objectsArray[0]);
    centerObjectArray(OBJECTSIZE, objectsArray[0]);
    moveObjectRight(OBJECTSIZE, objectsArray[0], -100);

    // Initialize back
    objectsArray[1] = (float **)generateObjectArray(OBJECTSIZE);
    transformObjectArrayToSquare(OBJECTSIZE, objectsArray[1]);
    centerObjectArray(OBJECTSIZE, objectsArray[1]);
    moveObjectRight(OBJECTSIZE, objectsArray[1], 100);

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

    float *rotationVector = (float *)malloc(sizeof(float) * 3);
    rotationVector[0] = 0.0f;
    rotationVector[1] = 0.0f;
    rotationVector[2] = 0.0f;

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

        // Display the object on the screen
        displayObjects(objectsArray, renderer, rotationVector, colorArray);

        // Update the screen
        SDL_RenderPresent(renderer);
        rotationVector[0] = rotationVector[0] + 1;
        rotationVector[1] = rotationVector[1] + 0;
        rotationVector[2] = rotationVector[2] + 0;

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < FRAME_TIME)
        {
            SDL_Delay(FRAME_TIME - frameTime);
        }
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    freeObjectArray(OBJECTSIZE, objectsArray[0]);
    free(rotationVector);
    free(objectsArray);

    return 0;
}

void displayObjects(float ***objectsArray, SDL_Renderer *renderer, float *rotationVector, int **colorArray)
{
    float *vectorBuffer = (float *)malloc(3 * sizeof(float));

    for (int i = 0; i < NUMBEROFOBJECTS; i++)
    {
        for (int j = 0; j < OBJECTSIZE * OBJECTSIZE; j++)
        {
            memcpy(vectorBuffer, objectsArray[i][j], 3 * sizeof(float));
            rotateVector(vectorBuffer, rotationVector);
            setPixel(renderer, floor(vectorBuffer[0] + WIDTH / 2), floor(HEIGHT - (vectorBuffer[1] + HEIGHT / 2)), colorArray[i][0], colorArray[i][1], colorArray[i][2]);
        }
    }
}

int rotateVector(float *vector, float *angle)
{
    float sinA = sinf(angle[0] * M_PI / 180);
    float cosA = cosf(angle[0] * M_PI / 180);
    float sinB = sinf(angle[1] * M_PI / 180);
    float cosB = cosf(angle[1] * M_PI / 180);
    float sinC = sinf(angle[2] * M_PI / 180);
    float cosC = cosf(angle[2] * M_PI / 180);
    float x = vector[0];
    float y = vector[1];
    float z = vector[2];

    float newX = x * (cosB * cosC) + y * (sinA * sinB * cosC - cosA * sinC) + z * (cosA * sinB * cosC + sinA * sinC);
    float newY = x * (cosB * sinC) + y * (sinA * sinB * sinC + cosA * cosC) + z * (cosA * sinB * sinC - sinA * cosC);
    float newZ = x * (-sinB) + y * (sinA * cosB) + z * (cosA * cosB);

    vector[0] = newX;
    vector[1] = newY;
    vector[2] = newZ;

    return 0;
}

void setPixel(SDL_Renderer *renderer, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(renderer, x, y);
}
