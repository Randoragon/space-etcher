#include <SDL2/SDL.h>
#include <math.h>

#include "obj-ball.h"
#include "macros.h"
#include "../space-etcher.h"
#include "../sprite.h"
#include "../input.h"

extern cpSpace *main_space;
extern SDL_Renderer *renderer;

int objBallCtor(void *self)
{
    ObjBall *o = self;

    // Physics
    o->radius = 8 + rand() % 6;
    cpFloat mass = 5;
    cpFloat moment = cpMomentForCircle(mass, 0, o->radius * 2, cpvzero);
    o->body = cpSpaceAddBody(main_space, cpBodyNew(mass, moment));
    cpBodySetPosition(o->body, cpv(CANVAS_WIDTH / 2.0, 50));
    o->shape = cpSpaceAddShape(main_space, cpCircleShapeNew(o->body, o->radius, cpvzero));
    cpShapeSetFriction(o->shape, 0.7);
    cpBodySetAngularVelocity(o->body, M_PI * ((float)((rand() % 200) - 100) / 100));
    cpShapeSetElasticity(o->shape, 0.8);
    o->color = (SDL_Color) { rand() % 255, rand() % 255, rand() % 255, 255 };

    return 0;
}

int objBallDtor(void *self)
{
    ObjBall *o = self;

    cpShapeFree(o->shape);
    cpBodyFree(o->body);

    return 0;
}

int objBallStep(void *self)
{
    ObjBall *o = self;

    return 0;
}

int objBallDraw(void *self)
{
    ObjBall *o = self;

    cpVect pos = cpBodyGetPosition(o->body);
    filledCircleRGBA(renderer, pos.x, pos.y, o->radius, o->color.r, o->color.g, o->color.b, o->color.a);

    float dir = cpBodyGetAngle(o->body);
    aalineRGBA(renderer, pos.x, pos.y,
            pos.x + o->radius * cos(dir),
            pos.y + o->radius * sin(dir),
            255 - o->color.r,
            255 - o->color.g,
            255 - o->color.b,
            255);
    aacircleRGBA(renderer, pos.x, pos.y, o->radius - 1, 0, 0, 0, o->color.a);
    aacircleRGBA(renderer, pos.x, pos.y, o->radius, 0, 0, 0, o->color.a);

    return 0;
}

void objBallSet(ObjBall *o, uint32_t x, uint32_t y, SDL_Color color, float dir)
{
    cpBodySetPosition(o->body, cpv(x, y));
    o->color = color;
    cpFloat h = 500 * cos(dir * M_PI / 180);
    cpFloat w = 600 * sin(dir * M_PI / 180);
    cpVect v = { w, h };
    cpBodySetVelocity(o->body, v);
}
