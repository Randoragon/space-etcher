#include "../space-etcher.h"
#include "player.h"

int objPlayerCtor(struct ObjPlayer *o)
{
    o->x = CANVAS_WIDTH / 2;
    o->y = CANVAS_HEIGHT - 20;
    return 0;
}
