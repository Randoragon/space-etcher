#ifndef OBJ_PLAYER_H
#define OBJ_PLAYER_H

typedef struct ObjPlayer
{
    double x, y;
} ObjPlayer;

int objPlayerCtor(struct ObjPlayer *o);

#endif // OBJ_PLAYER_H

