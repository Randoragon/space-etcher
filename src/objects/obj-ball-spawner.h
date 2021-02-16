/** @file
 * Implementation of the "ball-spawner" object.
 */

#ifndef OBJ_BALL_SPAWNER_H
#define OBJ_BALL_SPAWNER_H

#include <chipmunk/chipmunk.h>

#include "../sprite.h"
#include "macros.h"

typedef struct ObjBallSpawner
{
    int count;
    float dir;
} ObjBallSpawner;

int objBallSpawnerCtor(void *self);
int objBallSpawnerDtor(void *self);
int objBallSpawnerStep(void *self);
int objBallSpawnerDraw(void *self);

#endif /* OBJ_BALL_SPAWNER_H */
