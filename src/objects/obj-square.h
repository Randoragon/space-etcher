/** @file
 * Implementation of the "square" object.
 */

#ifndef OBJ_SQUARE_H
#define OBJ_SQUARE_H

#include <SDL2/SDL.h>
#include <chipmunk/chipmunk.h>
#include <RND_Game.h>

#include "../sprite.h"
#include "macros.h"

typedef struct ObjSquare
{
    cpFloat w, h;
    cpBody *body;
    cpShape *shape;
    RND_GameInstanceId spawner;
    int moving;
    cpVect prev_pos;

    OS_SPRITE_DECL
} ObjSquare;

int objSquareCtor(void *self);
int objSquareDtor(void *self);
int objSquareStep(void *self);
int objSquareDraw(void *self);

void objSquareSet(ObjSquare *o, RND_GameInstanceId spawner, uint32_t x, uint32_t y, float dir);

#endif /* OBJ_SQUARE_H */
