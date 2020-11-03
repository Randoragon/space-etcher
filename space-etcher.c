#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <RND_Game.h>
#include <RND_ErrMsg.h>
#include <RND_BitMap.h>

#include "space-etcher.h"
#include "objs/include.h"
#include "input.h"

SDL_Window *window;
SDL_Renderer *renderer;
bool running;
RND_GameHandler *step_handler, *draw_handler;

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
    if (!(events = eventSnapshotCreate())) {
        RND_ERROR("Failed to create EventSnapshot\n");
        exit(1);
    }
    if (!(events_prev = eventSnapshotCreate())) {
        RND_ERROR("Failed to create EventSnapshot\n");
        exit(1);
    }
    if (RND_gameInit()) {
        RND_ERROR("Failed to initialize RND_Game\n");
        exit(1);
    }
    RND_GAME_OBJECT_ADD(ObjPlayer, OBJI_PLAYER);
    RND_ctors[OBJI_PLAYER] = objPlayerCtor;
    step_handler = RND_gameHandlerCreate(NULL);
    draw_handler = RND_gameHandlerCreate(NULL);
    RND_gameHandlerAdd(step_handler, OBJI_PLAYER, objPlayerStep);
    RND_gameHandlerAdd(draw_handler, OBJI_PLAYER, objPlayerDraw);
    running = true;
}

void loadResources()
{
}

void gameBegin()
{
    RND_gameInstanceSpawn(OBJI_PLAYER);
}

void gameLoop()
{
    while (running) {
        listen();
        step();
        draw();
        SDL_Delay(1000 / FPS);
    }
}

void gameEnd()
{
}

void listen()
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev) > 0) {
        switch(ev.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN: case SDL_KEYUP:
                handleKey(ev.key);
                break;
            default:
                break;
        }
    }
}

void step()
{
    RND_gameHandlerRun(step_handler);
}

void draw()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    RND_gameHandlerRun(draw_handler);
    SDL_RenderPresent(renderer);
}

void cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    RND_gameCleanup();
    eventSnapshotDestroy(events);
    eventSnapshotDestroy(events_prev);
}

int main(int argc, char *argv[])
{
    init();
    loadResources();
    gameBegin();
    gameLoop();
    gameEnd();
    cleanup();

    return EXIT_SUCCESS;
}
