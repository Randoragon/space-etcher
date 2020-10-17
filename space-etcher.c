#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <RND_Game.h>
#include <RND_ErrMsg.h>

#include "space-etcher.h"

extern SDL_Window *window;
extern SDL_Surface *surface;
extern bool running;

int gameloop()
{
    while (running) {
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
        SDL_UpdateWindowSurface(window);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    window = NULL;
    surface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        RND_ERROR("Failed to initialize SDL (%s)\n", SDL_GetError());
        exit(1);
    }
    window = SDL_CreateWindow("Space Etcher",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);
    if (window == NULL) {
        RND_ERROR("Failed to create window (%s)\n", SDL_GetError());
        exit(1);
    }
    surface = SDL_GetWindowSurface(window);

    running = true;
    gameloop();

    return EXIT_SUCCESS;
}
