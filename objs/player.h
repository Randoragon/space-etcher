/** @file
 * The object controlled by the player during the game.
 */

#ifndef OBJ_PLAYER_H
#define OBJ_PLAYER_H

#include "../space-etcher.h"

typedef struct ObjPlayer
{
    double x, y;
} ObjPlayer;

extern EventSnapshot *events;

int objPlayerCtor(void *obj);
int objPlayerStep(void *obj);

#endif // OBJ_PLAYER_H

