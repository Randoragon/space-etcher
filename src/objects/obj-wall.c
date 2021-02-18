#include <RND_Game.h>
#include <SDL2/SDL.h>
#include <math.h>

#include "obj-wall.h"
#include "macros.h"
#include "../space-etcher.h"
#include "../sprite.h"
#include "../input.h"

extern cpSpace *main_space;
extern SDL_Renderer *renderer;

int objWallCtor(RND_GameInstance *self)
{
    ObjWall *o = self->data;

    o->shape = NULL;

    return 0;
}

int objWallDtor(RND_GameInstance *self)
{
    ObjWall *o = self->data;

    if (o->shape != NULL) {
        cpShapeFree(o->shape);
    }

    return 0;
}

int objWallStep(RND_GameInstance *self)
{
    ObjWall *o = self->data;

    return 0;
}

int objWallDraw(RND_GameInstance *self)
{
    ObjWall *o = self->data;

    // Draw line
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    thickLineRGBA(renderer, o->p1.x, o->p1.y, o->p2.x, o->p2.y, o->thickness, 0, 0, 0, 255);

    return 0;
}

void objWallSet(ObjWall *o, SDL_Point p1, SDL_Point p2, float thickness)
{
    o->p1 = p1;
    o->p2 = p2;
    o->thickness = thickness;
    if (o->shape != NULL) {
        cpSpaceRemoveShape(main_space, o->shape);
        cpShapeFree(o->shape);
    }
    o->shape = cpSegmentShapeNew(
            cpSpaceGetStaticBody(main_space),
            cpv(p1.x, p1.y),
            cpv(p2.x, p2.y),
            thickness / 2);
    cpSpaceAddShape(main_space, o->shape);
    cpShapeSetFriction(o->shape, 0.8);
    cpShapeSetElasticity(o->shape, 0.9);
}
