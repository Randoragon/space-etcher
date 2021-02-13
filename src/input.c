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
    if (!(ret->keyboard = RND_bitArrayCreate(4))) {
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
    if ((code = RND_bitArrayDestroy(es->keyboard))) {
        RND_ERROR("Failed to destroy bitmap (RND_bitArrayDestroy returned %d)\n", code);
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
            index = KEY_LEFT;
            break;
        case SDLK_UP:
            index = KEY_JUMP;
            break;
        case SDLK_RIGHT:
            index = KEY_RIGHT;
            break;
        case SDLK_DOWN:
            index = KEY_CROUCH;
            break;
        default:
            return;
    }
    pressed = (kev.state == SDL_PRESSED)? true : false; 
    RND_bitArraySet(events->keyboard, index, pressed);
}
