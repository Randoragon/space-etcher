#include <SDL2/SDL.h>
#include <math.h>

#include "obj-player.h"
#include "macros.h"
#include "../space-etcher.h"
#include "../sprite.h"
#include "../input.h"

extern cpSpace *main_space;

int objPlayerCtor(void *self)
{
    ObjPlayer *o = self;

    o->pulse_clock = 0.0;

    // Sprite
    OS_SPRITE_CTOR("candy_bullet");
    o->img_hscale = 2.0 * o->radius / o->spr->w;
    o->img_vscale = 2.0 * o->radius / o->spr->h;
    o->img_xorig  = o->spr->w / 2;
    o->img_yorig  = o->spr->h / 2;

    // Physics
    o->radius = 50;
    cpFloat mass = 1;
    cpFloat moment = cpMomentForCircle(mass, 0, o->radius, cpvzero);
    o->body = cpSpaceAddBody(main_space, cpBodyNew(mass, moment));
    cpBodySetPosition(o->body, cpv(CANVAS_WIDTH / 2.0, CANVAS_HEIGHT / 2.0));
    o->shape = cpSpaceAddShape(main_space, cpCircleShapeNew(o->body, o->radius, cpvzero));
    cpShapeSetFriction(o->shape, 0.7);
    cpBodySetAngularVelocity(o->body, M_PI * -1);
    cpShapeSetElasticity(o->shape, 0.9);

    return 0;
}

int objPlayerDtor(void *self)
{
    ObjPlayer *o = self;

    cpBodyFree(o->body);
    cpShapeFree(o->shape);

    return 0;
}

int objPlayerStep(void *self)
{
    ObjPlayer *o = self;

    o->img_hscale  = (2.0 * o->radius / o->spr->w) + sin(o->pulse_clock) * 0.6;
    o->img_vscale  = (2.0 * o->radius / o->spr->h) + cos(o->pulse_clock) * 0.6;
    o->pulse_clock = fmod(o->pulse_clock + 0.2, 2 * M_PI);

    OS_SPRITE_STEP;

    // Update image angle
    cpFloat ang_rad = cpBodyGetAngle(o->body);
    o->img_angle = ang_rad * 180 / M_PI;

    return 0;
}

int objPlayerDraw(void *self)
{
    ObjPlayer *o = self;

    // Draw self
    cpVect pos = cpBodyGetPosition(o->body);
    OS_SPRITE_DRAW(pos.x, pos.y);

    return 0;
}
