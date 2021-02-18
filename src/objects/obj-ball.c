#include <RND_Game.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

#include "obj-ball.h"
#include "obj-spawner.h"
#include "macros.h"
#include "../space-etcher.h"
#include "../sprite.h"
#include "../input.h"

extern cpSpace *main_space;
extern SDL_Renderer *renderer;

int objBallCtor(RND_GameInstance *self)
{
    ObjBall *o = self->data;

    o->spawner = 0;
    o->moving = 1;

    // Physics
    o->radius = 9 + rand() % 6;
    cpFloat mass = 5;
    cpFloat moment = cpMomentForCircle(mass, 0, o->radius * 2, cpvzero);
    o->body = cpSpaceAddBody(main_space, cpBodyNew(mass, moment));
    cpBodySetPosition(o->body, cpv(CANVAS_WIDTH / 2.0, 50));
    o->shape = cpSpaceAddShape(main_space, cpCircleShapeNew(o->body, o->radius, cpvzero));
    cpShapeSetFriction(o->shape, 0.7);
    cpBodySetAngle(o->body, fmod(rand(), 2 * M_PI));
    cpBodySetAngularVelocity(o->body, M_PI * ((float)((rand() % 30) - 15)));
    cpShapeSetElasticity(o->shape, 0.8);
    o->prev_pos = cpBodyGetPosition(o->body);

    // Sprite
    OS_SPRITE_CTOR("ball");
    o->img_xorig = o->spr->w / 2;
    o->img_yorig = o->spr->h / 2;
    o->img_hscale = (o->radius * 2) / o->spr->w;
    o->img_vscale = (o->radius * 2) / o->spr->h;
    o->anim_frame = rand() % 38;

    return 0;
}

int objBallDtor(RND_GameInstance *self)
{
    ObjBall *o = self->data;

    cpShapeFree(o->shape);
    cpBodyFree(o->body);

    return 0;
}

int objBallStep(RND_GameInstance *self)
{
    ObjBall *o = self->data;

    OS_SPRITE_STEP;

    if (o->moving > 0) {
        cpVect pos = cpBodyGetPosition(o->body);
        if (fabs(pos.x - o->prev_pos.x) <= 0.3 && fabs(pos.y - o->prev_pos.y) <= 0.3) {
            if (++o->moving > 100) {
                o->moving = 0;
                RND_GAME_INST(o->spawner, ObjSpawner).moving_count--;
            }
        } else {
            o->moving = 1;
        }
        o->prev_pos = pos;
    }

    return 0;
}

int objBallDraw(RND_GameInstance *self)
{
    ObjBall *o = self->data;

    // Draw self
    cpVect pos = cpBodyGetPosition(o->body);
    cpFloat ang = cpBodyGetAngle(o->body);
    o->img_angle = ang * 180 / M_PI;
    OS_SPRITE_DRAW(pos.x, pos.y);

    return 0;
}

void objBallSet(ObjBall *o, RND_GameInstanceId spawner, uint32_t x, uint32_t y, float dir)
{
    cpBodySetPosition(o->body, cpv(x, y));
    o->spawner = spawner;
    cpFloat h = 600 * cos(dir * M_PI / 180);
    cpFloat w = 600 * sin(dir * M_PI / 180);
    cpVect v = { w, h };
    cpBodySetVelocity(o->body, v);
}
