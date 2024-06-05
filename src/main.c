#include <SDL2/SDL.h>
#include "objectGenerator.h"
#include <unistd.h>

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 800;
const int OBJECTSIZE = 300;

void displayObject(float **object, SDL_Renderer *renderer);

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
    printObjectArray(OBJECTSIZE, object);

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
        displayObject(object, renderer);
        objectYawRotation(OBJECTSIZE, object, 0.1);

        // Update the screen
        SDL_RenderPresent(renderer);
        sleep(0.1);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    freeObjectArray(OBJECTSIZE, object);

    return 0;
}

void displayObject(float **object, SDL_Renderer *renderer)
{
    for (int i = 0; i < OBJECTSIZE * OBJECTSIZE; i++)
    {
        setPixel(renderer, floor(object[i][0] + WIDTH / 2), floor(HEIGHT - (object[i][1] + HEIGHT / 2)), 255, 255, 255);
    }
}
