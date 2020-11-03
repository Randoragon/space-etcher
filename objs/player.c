#include <SDL2/SDL.h>

#include "../space-etcher.h"
#include "player.h"
#include "../input.h"

int objPlayerCtor(void *obj)
{
    ObjPlayer *o = obj;
    o->x = CANVAS_WIDTH / 2;
    o->y = CANVAS_HEIGHT - 20;
    return 0;
}

int objPlayerStep(void *obj)
{
    ObjPlayer *o = obj;
    o->x += 10 * (keyIsDown(KEY_RIGHT) - keyIsDown(KEY_LEFT));
    o->y += 10 * (keyIsDown(KEY_CROUCH) - keyIsDown(KEY_JUMP));
    return 0;
}

int objPlayerDraw(void *obj)
{
    ObjPlayer *o = obj;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect r = {o->x - 5, o->y - 5, 10, 10};
    SDL_RenderFillRect(renderer, &r);
    return 0;
}
