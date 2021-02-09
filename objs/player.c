#include <SDL2/SDL.h>
#include <math.h>

#include "../space-etcher.h"
#include "player.h"
#include "../input.h"

extern cpSpace *main_space;

int objPlayerCtor(void *obj)
{
    ObjPlayer *o = obj;
    o->radius = 50;
    cpFloat mass   = 1;
    cpFloat moment = cpMomentForCircle(mass, 0, o->radius, cpvzero);
    o->body = cpSpaceAddBody(main_space, cpBodyNew(mass, moment));
    cpBodySetPosition(o->body, cpv(CANVAS_WIDTH / 2.0, CANVAS_HEIGHT / 2.0));

    o->shape = cpSpaceAddShape(main_space, cpCircleShapeNew(o->body, o->radius, cpvzero));
    cpShapeSetFriction(o->shape, 0.7);
    cpBodySetAngularVelocity(o->body, M_PI * -1);
    cpShapeSetElasticity(o->shape, 0.9);
    return 0;
}

int objPlayerStep(void *obj)
{
    //ObjPlayer *o = obj;
    //o->x += 10 * (keyIsDown(KEY_RIGHT) - keyIsDown(KEY_LEFT));
    //o->y += 10 * (keyIsDown(KEY_CROUCH) - keyIsDown(KEY_JUMP));
    return 0;
}

int objPlayerDraw(void *obj)
{
    ObjPlayer *o = obj;
    cpVect pos = cpBodyGetPosition(o->body);
    cpFloat ang = cpBodyGetAngle(o->body);
    filledCircleRGBA(renderer, pos.x, pos.y, o->radius, 0, 0, 0, 0xff);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawLine(renderer, pos.x,
                                 pos.y,
                                 pos.x + o->radius * cos(ang),
                                 pos.y + o->radius * sin(ang));
    return 0;
}
