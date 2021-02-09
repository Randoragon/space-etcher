#include "../space-etcher.h"
#include "ground.h"

extern SDL_Renderer *renderer;
extern cpSpace *main_space;

int objGroundCtor(void *self)
{
    ObjGround *o = self;
    o->shape = cpSegmentShapeNew(cpSpaceGetStaticBody(main_space), cpv(0, CANVAS_HEIGHT - 70), cpv(CANVAS_WIDTH, CANVAS_HEIGHT - 30), 0);
    cpSpaceAddShape(main_space, o->shape);
    cpShapeSetFriction(o->shape, 0.8);
    cpShapeSetElasticity(o->shape, 0.9);
    return 0;
}

int objGroundDtor(void *self)
{
    ObjGround *o = self;
    cpShapeFree(o->shape);
    return 0;
}

int objGroundDraw(void *self)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    int y0 = 70, y1 = 30;
    SDL_RenderDrawLine(renderer, 0, CANVAS_HEIGHT - y0, CANVAS_WIDTH, CANVAS_HEIGHT - y1);
    SDL_RenderDrawLine(renderer, 0, CANVAS_HEIGHT - y0 - 1, CANVAS_WIDTH, CANVAS_HEIGHT - y1 - 1);
    SDL_RenderDrawLine(renderer, 0, CANVAS_HEIGHT - y0 - 2, CANVAS_WIDTH, CANVAS_HEIGHT - y1 - 2);
    return 0;
}
