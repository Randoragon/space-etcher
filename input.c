#include <SDL2/SDL.h>
#include <RND_ErrMsg.h>
#include "input.h"

EventSnapshot *events, *events_prev;

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
    bool   pressed, prev;
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
    prev    = RND_bitMapGet(events->keyboard, index);
    RND_bitMapSet(events_prev->keyboard, index, prev);
    RND_bitMapSet(events->keyboard, index, pressed);
}

