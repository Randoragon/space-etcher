#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <RND_Game.h>
#include <RND_ErrMsg.h>
#include <RND_BitMap.h>

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
    eventSnapshotDestroy(events);
    eventSnapshotDestroy(events_prev);
}

EventSnapshot *eventSnapshotCreate()
{
    EventSnapshot *ret;
    if (!(ret = malloc(sizeof(EventSnapshot)))) {
        RND_ERROR("malloc");
        return NULL;
    }
    if (!(ret->keyboard = RND_bitMapCreate(4))) {
        RND_ERROR("Failed to create bitmap\n");
        free(ret);
        return NULL;
    }
    return ret;
}

int eventSnapshotDestroy(EventSnapshot *es)
{
    if (!es) {
        RND_ERROR("es is NULL");
        return 1;
    }
    int code;
    if ((code = RND_bitMapDestroy(es->keyboard))) {
        RND_ERROR("Failed to destroy bitmap (RND_bitMapDestroy returned %d)\n", code);
        return 1;
    }
    free(es);
    return 0;
}

void handleKey(SDL_KeyboardEvent kev)
{
    if (kev.repeat) {
        return;
    }
    size_t index;
    bool   pressed;
    switch(kev.keysym.sym) {
        case SDLK_LEFT:
            index = 0;
            break;
        case SDLK_UP:
            index = 1;
            break;
        case SDLK_RIGHT:
            index = 2;
            break;
        case SDLK_DOWN:
            index = 3;
            break;
        default:
            return;
    }
    pressed = (kev.state == SDL_PRESSED)? true : false; 
    RND_bitMapSet(events->keyboard, index, pressed);
}
int main(int argc, char *argv[])
{
    init();
    loadResources();
    gameloop();
    cleanup();

    return EXIT_SUCCESS;
}
