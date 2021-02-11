/** @file
 * Code snippets for repetitive code that appears inside objects.
 * Snippets begin with "OS" for "Object Snippet".
 */

/// Put inside struct body to include sprite related members.
#define OS_SPRITE_DECL    \
    const Sprite   *spr;  \
    float    img_hscale;  \
    float    img_vscale;  \
    float    img_alpha;   \
    float    img_angle;   \
    uint32_t img_xorig;   \
    uint32_t img_yorig;   \
    float    anim_frame;  \
    float    anim_speed;

#define OS_SPRITE_CTOR(name) \
    do { \
        o->spr = RND_hashMapGet(sprites, name); \
        o->img_hscale = 1.0; \
        o->img_vscale = 1.0; \
        o->img_alpha  = 1.0; \
        o->img_angle  = 0.0; \
        o->img_xorig  = 0;   \
        o->img_yorig  = 0;   \
        o->anim_frame = 0.0; \
        o->anim_speed = 1.0; \
    } while (0)

#define OS_SPRITE_STEP \
    do { \
        o->anim_frame = fmod(o->anim_frame + (o->anim_speed * o->spr->anim_speed), o->spr->frames); \
    } while (0)

#define OS_SPRITE_DRAW(X, Y) \
    do { \
        SDL_Rect src, dest; \
        SDL_Point origin; \
        src.x = ((uint32_t)o->anim_frame) * o->spr->w; \
        src.y = 0; \
        src.w = o->spr->w; \
        src.h = o->spr->h; \
        dest.x = (X) - (o->img_xorig * o->img_hscale); \
        dest.y = (Y) - (o->img_yorig * o->img_vscale); \
        dest.w = o->spr->w * o->img_hscale; \
        dest.h = o->spr->h * o->img_vscale; \
        origin.x = o->img_xorig * o->img_hscale; \
        origin.y = o->img_yorig * o->img_vscale; \
        SDL_RenderCopyEx(renderer, o->spr->tex, &src, &dest, o->img_angle, &origin, SDL_FLIP_NONE); \
    } while (0)
