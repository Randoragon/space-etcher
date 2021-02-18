/** @file
 * Implementation of the "spawner" object.
 */

#ifndef OBJ_SPAWNER_H
#define OBJ_SPAWNER_H

#include <RND_Game.h>
#include <chipmunk/chipmunk.h>

#include "../sprite.h"
#include "macros.h"

typedef struct ObjSpawner
{
    int count;
    float dir;
    int moving_count;
    RND_GameInstanceId self_id;
} ObjSpawner;

int objSpawnerCtor(RND_GameInstance *self);
int objSpawnerDtor(RND_GameInstance *self);
int objSpawnerStep(RND_GameInstance *self);
int objSpawnerDraw(RND_GameInstance *self);

#endif /* OBJ_SPAWNER_H */
