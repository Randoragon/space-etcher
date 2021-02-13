#ifndef OBJ_INCLUDE_H
#define OBJ_INCLUDE_H

#include "obj-ground.h"
#include "obj-player.h"

#define ADD_ALL_OBJECTS() \
    do { \
        RND_GAME_OBJECT_ADD(ObjGround, OBJI_GROUND); \
        RND_ctors[OBJI_GROUND] = objGroundCtor; \
        RND_dtors[OBJI_GROUND] = objGroundDtor; \
        RND_gameHandlerAdd(step_handler, OBJI_GROUND, objGroundStep); \
        RND_gameHandlerAdd(draw_handler, OBJI_GROUND, objGroundDraw); \
        RND_GAME_OBJECT_ADD(ObjPlayer, OBJI_PLAYER); \
        RND_ctors[OBJI_PLAYER] = objPlayerCtor; \
        RND_dtors[OBJI_PLAYER] = objPlayerDtor; \
        RND_gameHandlerAdd(step_handler, OBJI_PLAYER, objPlayerStep); \
        RND_gameHandlerAdd(draw_handler, OBJI_PLAYER, objPlayerDraw); \
   } while (0)

#endif /* OBJ_INCLUDE_H */