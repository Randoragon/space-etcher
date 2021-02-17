#include <SDL2/SDL.h>
#include <math.h>

#include "obj-ball-spawner.h"
#include "macros.h"
#include "../space-etcher.h"
#include "../sprite.h"
#include "../input.h"
#include "include.h"

extern cpSpace *main_space;

int objBallSpawnerCtor(void *self)
{
    ObjBallSpawner *o = self;

    o->self_id = 0;
    o->count = 1000;
    o->dir = rand() % 360;
    o->moving_balls_count = 0;

    return 0;
}

int objBallSpawnerDtor(void *self)
{
    ObjBallSpawner *o = self;

    return 0;
}

int objBallSpawnerStep(void *self)
{
    ObjBallSpawner *o = self;

    if (o->count > 0) {
        o->dir = fmod(o->dir + 15, 360);
        RND_GameInstanceId id;
        id = RND_gameInstanceSpawn(OBJI_BALL);
        objBallSet(RND_instances[id].data,
                o->self_id,
                CANVAS_WIDTH / 2,
                250,
                o->dir);
        id = RND_gameInstanceSpawn(OBJI_BALL);
        objBallSet(RND_instances[id].data,
                o->self_id,
                CANVAS_WIDTH / 2,
                250,
                fmod(o->dir + 180, 360));
        o->count -= 2;
        o->moving_balls_count += 2;
    } else if (o->moving_balls_count == 0) {
        running = false;
    }
    return 0;
}

int objBallSpawnerDraw(void *self)
{
    ObjBallSpawner *o = self;

    return 0;
}
