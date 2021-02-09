/** @file
 * The object controlled by the player during the game.
 */

#ifndef OBJ_PLAYER_H
#define OBJ_PLAYER_H

#include <chipmunk/chipmunk.h>

typedef struct ObjPlayer
{
    cpFloat radius;
    cpBody  *body;
    cpShape *shape;
} ObjPlayer;

int objPlayerCtor(void *obj);
int objPlayerStep(void *obj);
int objPlayerDraw(void *obj);

#endif /* OBJ_PLAYER_H */
