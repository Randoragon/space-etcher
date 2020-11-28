#ifndef OBJ_GROUND_H
#define OBJ_GROUND_H

#include <chipmunk/chipmunk.h>

typedef struct ObjGround
{
    cpShape *shape;
} ObjGround;

int objGroundCtor(void *obj);
int objGroundDtor(void *obj);
int objGroundDraw(void *obj);

#endif
