#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <RND_Game.h>
#include <RND_ErrMsg.h>

#include "space-etcher.h"

SDL_Window *window;
SDL_Renderer *renderer;
bool running;
EventSnapshot *events, *events_prev;

void init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        RND_ERROR("Failed to initialize SDL (%s)\n", SDL_GetError());
        exit(1);
    }
    window = SDL_CreateWindow("Space Etcher",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            CANVAS_WIDTH,
            CANVAS_HEIGHT,
            SDL_WINDOW_SHOWN);
    if (window == NULL) {
        RND_ERROR("Failed to create window (%s)\n", SDL_GetError());
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
        RND_ERROR("Failed to create renderer (%s)\n", SDL_GetError());
        exit(1);
    }
    if (!(events = calloc(1, sizeof(EventSnapshot)))) {
        RND_ERROR("calloc");
        exit(1);
    }
    if (!(events_prev = calloc(1, sizeof(EventSnapshot)))) {
        RND_ERROR("calloc");
        exit(1);
    }
    if (RND_gameInit()) {
        RND_ERROR("Failed to initialize RND_Game\n");
        exit(1);
    }
    running = true;
}

void loadResources()
{
}

void gameloop()
{
    while (running) {
        listen();
        step();
        draw();
        SDL_Delay(1000 / FPS);
    }
}

void listen()
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev) > 0) {
        if (ev.type == SDL_QUIT) {
            running = false;
        }
    }
}

void step()
{
}

void draw()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    RND_gameCleanup();
}

int main(int argc, char *argv[])
{
    init();
    loadResources();
    gameloop();
    cleanup();

    return EXIT_SUCCESS;
}
