/** @file
 * Implementation of the "square" object.
 */

#ifndef OBJ_SQUARE_H
#define OBJ_SQUARE_H

#include <RND_Game.h>
#include <SDL2/SDL.h>
#include <chipmunk/chipmunk.h>

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

int objSquareCtor(RND_GameInstance *self);
int objSquareDtor(RND_GameInstance *self);
int objSquareStep(RND_GameInstance *self);
int objSquareDraw(RND_GameInstance *self);

void objSquareSet(ObjSquare *o, RND_GameInstanceId spawner, uint32_t x, uint32_t y, float dir);

#endif /* OBJ_SQUARE_H */
