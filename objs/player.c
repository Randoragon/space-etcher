#include "../space-etcher.h"
#include "player.h"

int objPlayerCtor(void *obj)
{
    ObjPlayer *o = obj;
    o->x = CANVAS_WIDTH / 2;
    o->y = CANVAS_HEIGHT - 20;
    return 0;
}

int objPlayerStep(void *obj)
{
    ObjPlayer *o = obj;
    o->x += 10 * (RND_bitMapGet(events->keyboard, 2) - RND_bitMapGet(events->keyboard, 0));
    o->y += 10 * (RND_bitMapGet(events->keyboard, 3) - RND_bitMapGet(events->keyboard, 1));
    printf("x: %lf\ty: %lf\n", o->x, o->y);
    return 0;
}
