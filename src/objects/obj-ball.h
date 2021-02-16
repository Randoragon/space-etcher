/** @file
 * Implementation of the "ball" object.
 */

#ifndef OBJ_BALL_H
#define OBJ_BALL_H

#include <SDL2/SDL.h>
#include <chipmunk/chipmunk.h>

#include "../sprite.h"
#include "macros.h"

typedef struct ObjBall
{
    cpFloat radius;
    cpBody *body;
    cpShape *shape;
    SDL_Color color;
} ObjBall;

int objBallCtor(void *self);
int objBallDtor(void *self);
int objBallStep(void *self);
int objBallDraw(void *self);

void objBallSet(ObjBall *o, uint32_t x, uint32_t y, SDL_Color color, float dir);

#endif /* OBJ_BALL_H */
