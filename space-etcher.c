#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <RND_Game.h>
#include <RND_ErrMsg.h>
#include <RND_BitArray.h>

#include "space-etcher.h"
#include "objs/include.h"
#include "input.h"

SDL_Window *window;
SDL_Renderer *renderer;
bool running;
RND_GameHandler *step_handler, *draw_handler;
cpSpace *main_space;

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
    if (!(main_space = cpSpaceNew())) {
        RND_ERROR("Failed to create Chipmunk space\n");
        exit(1);
    }
    if (RND_gameInit()) {
        RND_ERROR("Failed to initialize RND_Game\n");
        exit(1);
    }
    RND_GAME_OBJECT_ADD(ObjPlayer, OBJI_PLAYER);
    RND_GAME_OBJECT_ADD(ObjGround, OBJI_GROUND);
    RND_ctors[OBJI_PLAYER] = objPlayerCtor;
    RND_ctors[OBJI_GROUND] = objGroundCtor;
    RND_dtors[OBJI_GROUND] = objGroundDtor;
    step_handler = RND_gameHandlerCreate(NULL);
    draw_handler = RND_gameHandlerCreate(NULL);
    RND_gameHandlerAdd(step_handler, OBJI_PLAYER, objPlayerStep);
    RND_gameHandlerAdd(draw_handler, OBJI_PLAYER, objPlayerDraw);
    RND_gameHandlerAdd(draw_handler, OBJI_GROUND, objGroundDraw);
    running = true;
}

void loadResources()
{
}

void gameBegin()
{
    RND_gameInstanceSpawn(OBJI_GROUND);
    RND_gameInstanceSpawn(OBJI_PLAYER);
    cpSpaceSetGravity(main_space, cpv(0, GRAVITY));
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
    for (int i = 0; i < KEY_SIZE; i++) {
        bool last = keyIsDown(i);
        RND_bitArraySet(events_prev->keyboard, i, last);
    }
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
    cpSpaceStep(main_space, 1.0 / FPS);
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
    cpSpaceFree(main_space);
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
