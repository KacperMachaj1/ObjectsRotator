#include <SDL2/SDL.h>

#include <unistd.h>
#include <math.h>

#include "objectGenerator.h"

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 800;
const int OBJECTSIZE = 200;

void displayObject(float **object, SDL_Renderer *renderer, float *rotationVector);

int rotateVector(float *vector, float *angle);

// Function to set pixel color at (x, y) coordinates
void setPixel(SDL_Renderer *renderer, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(renderer, x, y);
}

int main(int argc, char **argv)
{
    float **object = (float **)generateObjectArray(OBJECTSIZE);
    transformObjectArrayToSquare(OBJECTSIZE, object);
    centerObjectArray(OBJECTSIZE, object);

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
        // Process events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Display the object on the screen
        displayObject(object, renderer, rotationVector);

        // Update the screen
        SDL_RenderPresent(renderer);
        sleep(0.1);
        rotationVector[0] = rotationVector[0] + 0.1;
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    freeObjectArray(OBJECTSIZE, object);
    free(rotationVector);

    return 0;
}

void displayObject(float **object, SDL_Renderer *renderer, float *rotationVector)
{
    float *vectorBuffer = (float *)malloc(3 * sizeof(float));

    for (int i = 0; i < OBJECTSIZE * OBJECTSIZE; i++)
    {
        memcpy(vectorBuffer, object[i], 3 * sizeof(float));
        rotateVector(vectorBuffer, rotationVector);
        setPixel(renderer, floor(vectorBuffer[0] + WIDTH / 2), floor(HEIGHT - (vectorBuffer[1] + HEIGHT / 2)), 255, 255, 255);
    }
}

int rotateVector(float *vector, float *angle)
{
    float newX = vector[0] * cosf(angle[0]) - vector[1] * sinf(angle[0]);
    float newY = vector[0] * sinf(angle[0]) + vector[1] * cosf(angle[0]);
    vector[0] = newX;
    vector[1] = newY;

    return 0;
}
