/** @file
 * Implementation of the "spawner" object.
 */

#ifndef OBJ_SPAWNER_H
#define OBJ_SPAWNER_H

#include <chipmunk/chipmunk.h>
#include <RND_Game.h>

#include "../sprite.h"
#include "macros.h"

typedef struct ObjSpawner
{
    int count;
    float dir;
    int moving_count;
    RND_GameInstanceId self_id;
} ObjSpawner;

int objSpawnerCtor(void *self);
int objSpawnerDtor(void *self);
int objSpawnerStep(void *self);
int objSpawnerDraw(void *self);

#endif /* OBJ_SPAWNER_H */
