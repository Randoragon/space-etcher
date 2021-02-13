#ifndef OBJ_PLAYER_H
#define OBJ_PLAYER_H

#include <chipmunk/chipmunk.h>

#include "../sprite.h"
#include "macros.h"

typedef struct ObjPlayer
{
    cpFloat radius;
    float   pulse_clock;
    cpBody  *body;
    cpShape *shape;

    OS_SPRITE_DECL
} ObjPlayer;

int objPlayerCtor(void *self);
int objPlayerDtor(void *self);
int objPlayerStep(void *self);
int objPlayerDraw(void *self);

#endif /* OBJ_PLAYER_H */
