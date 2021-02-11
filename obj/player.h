/** @file
 * The object controlled by the player during the game.
 */

#ifndef OBJ_PLAYER_H
#define OBJ_PLAYER_H

#include <chipmunk/chipmunk.h>

#include "../sprite.h"
#include "snippets.h"

typedef struct ObjPlayer
{
    cpFloat radius;
    cpBody  *body;
    cpShape *shape;

    OS_SPRITE_DECL
} ObjPlayer;

int objPlayerCtor(void *self);
int objPlayerDtor(void *self);
int objPlayerStep(void *self);
int objPlayerDraw(void *self);

#endif /* OBJ_PLAYER_H */
