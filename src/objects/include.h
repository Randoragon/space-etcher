#ifndef OBJ_INCLUDE_H
#define OBJ_INCLUDE_H

#include "macros.h"
#include "obj-ball.h"
#include "obj-ball-spawner.h"
#include "obj-square.h"
#include "obj-wall.h"

#define ADD_ALL_OBJECTS() \
    do { \
        RND_GAME_OBJECT_ADD(ObjBall, OBJI_BALL); \
        RND_ctors[OBJI_BALL] = objBallCtor; \
        RND_dtors[OBJI_BALL] = objBallDtor; \
        RND_gameHandlerAdd(step_handler, OBJI_BALL, objBallStep); \
        RND_gameHandlerAdd(draw_handler, OBJI_BALL, objBallDraw); \
        RND_GAME_OBJECT_ADD(ObjBallSpawner, OBJI_BALL_SPAWNER); \
        RND_ctors[OBJI_BALL_SPAWNER] = objBallSpawnerCtor; \
        RND_dtors[OBJI_BALL_SPAWNER] = objBallSpawnerDtor; \
        RND_gameHandlerAdd(step_handler, OBJI_BALL_SPAWNER, objBallSpawnerStep); \
        RND_gameHandlerAdd(draw_handler, OBJI_BALL_SPAWNER, objBallSpawnerDraw); \
        RND_GAME_OBJECT_ADD(ObjSquare, OBJI_SQUARE); \
        RND_ctors[OBJI_SQUARE] = objSquareCtor; \
        RND_dtors[OBJI_SQUARE] = objSquareDtor; \
        RND_gameHandlerAdd(step_handler, OBJI_SQUARE, objSquareStep); \
        RND_gameHandlerAdd(draw_handler, OBJI_SQUARE, objSquareDraw); \
        RND_GAME_OBJECT_ADD(ObjWall, OBJI_WALL); \
        RND_ctors[OBJI_WALL] = objWallCtor; \
        RND_dtors[OBJI_WALL] = objWallDtor; \
        RND_gameHandlerAdd(step_handler, OBJI_WALL, objWallStep); \
        RND_gameHandlerAdd(draw_handler, OBJI_WALL, objWallDraw); \
   } while (0)

#endif /* OBJ_INCLUDE_H */