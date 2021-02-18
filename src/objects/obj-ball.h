/** @file
 * Implementation of the "ball" object.
 */

#ifndef OBJ_BALL_H
#define OBJ_BALL_H

#include <RND_Game.h>
#include <SDL2/SDL.h>
#include <chipmunk/chipmunk.h>

#include "../sprite.h"
#include "macros.h"

typedef struct ObjBall
{
    cpFloat radius;
    cpBody *body;
    cpShape *shape;
    RND_GameInstanceId spawner;
    int moving;
    cpVect prev_pos;

    OS_SPRITE_DECL
} ObjBall;

int objBallCtor(RND_GameInstance *self);
int objBallDtor(RND_GameInstance *self);
int objBallStep(RND_GameInstance *self);
int objBallDraw(RND_GameInstance *self);

void objBallSet(ObjBall *o, RND_GameInstanceId spawner, uint32_t x, uint32_t y, float dir);

#endif /* OBJ_BALL_H */
