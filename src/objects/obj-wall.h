/** @file
 * Implementation of the "wall" object.
 */

#ifndef OBJ_WALL_H
#define OBJ_WALL_H

#include <RND_Game.h>
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

int objWallCtor(RND_GameInstance *self);
int objWallDtor(RND_GameInstance *self);
int objWallStep(RND_GameInstance *self);
int objWallDraw(RND_GameInstance *self);

void objWallSet(ObjWall *o, SDL_Point p1, SDL_Point p2, float thickness);

#endif /* OBJ_WALL_H */
