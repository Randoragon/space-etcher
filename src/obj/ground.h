#ifndef OBJ_GROUND_H
#define OBJ_GROUND_H

#include <chipmunk/chipmunk.h>

typedef struct ObjGround
{
    cpShape *shape;
} ObjGround;

int objGroundCtor(void *self);
int objGroundDtor(void *self);
int objGroundDraw(void *self);

#endif /* OBJ_GROUND_H */
