#include <RND_Game.h>
#include <SDL2/SDL.h>
#include <math.h>

#include "obj-spawner.h"
#include "macros.h"
#include "../space-etcher.h"
#include "../sprite.h"
#include "../input.h"
#include "include.h"

extern cpSpace *main_space;

int objSpawnerCtor(RND_GameInstance *self)
{
    ObjSpawner *o = self->data;

    o->self_id = 0;
    o->count = 1000;
    o->dir = rand() % 360;
    o->moving_count = 0;

    return 0;
}

int objSpawnerDtor(RND_GameInstance *self)
{
    ObjSpawner *o = self->data;

    return 0;
}

int objSpawnerStep(RND_GameInstance *self)
{
    ObjSpawner *o = self->data;

    if (o->count > 0) {
        o->dir = fmod(o->dir + 15, 360);
        RND_GameInstanceId id;
        for (int i = 0; i < 2; i++) {
            if (rand() % 2 == 0) {
                id = RND_gameInstanceSpawn(OBJI_BALL);
                objBallSet(RND_instances[id].data,
                        o->self_id,
                        CANVAS_WIDTH / 2,
                        250,
                        fmod(o->dir + (i * 180), 360));
            } else {
                id = RND_gameInstanceSpawn(OBJI_SQUARE);
                objSquareSet(RND_instances[id].data,
                        o->self_id,
                        CANVAS_WIDTH / 2,
                        250,
                        fmod(o->dir + (i * 180), 360));
            }
        }
        o->count -= 2;
        o->moving_count += 2;
    } else if (o->moving_count == 0) {
        running = false;
    }
    return 0;
}

int objSpawnerDraw(RND_GameInstance *self)
{
    ObjSpawner *o = self->data;

    return 0;
}
