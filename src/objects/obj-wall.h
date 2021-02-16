/** @file
 * Implementation of the "wall" object.
 */

#ifndef OBJ_WALL_H
#define OBJ_WALL_H

#include <chipmunk/chipmunk.h>

#include <SDL2/SDL.h>
#include "../sprite.h"
#include "macros.h"

typedef struct ObjWall
{
    SDL_Point p1, p2;
    float thickness;
    cpShape *shape;
} ObjWall;

int objWallCtor(void *self);
int objWallDtor(void *self);
int objWallStep(void *self);
int objWallDraw(void *self);

void objWallSet(ObjWall *o, SDL_Point p1, SDL_Point p2, float thickness);

#endif /* OBJ_WALL_H */
