#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <RND_ErrMsg.h>

#include "space-etcher.h"
#include "sprite.h"

int loadSpritesheet(Sprite **spr_ptr, const char *path, uint32_t frames, float speed)
{
    Sprite *sprite;
    if (!(sprite = (Sprite*)malloc(sizeof(Sprite)))) {
        RND_ERROR("malloc");
        return 1;
    }
    sprite->tex = IMG_LoadTexture(renderer, path);
    if (sprite->tex == NULL) {
        RND_ERROR("failed to load texture \"%s\"", path);
        free(sprite);
        return 2;
    }
    int w, h;
    SDL_QueryTexture(sprite->tex, NULL, NULL, &w, &h);
    if (w % frames != 0) {
        RND_ERROR("texture width (%u) not divisible by frame count (%u)", w, frames);
        SDL_DestroyTexture(sprite->tex);
        free(sprite);
        return 3;
    }
    sprite->w = w / frames;
    sprite->h = h;
    sprite->frames = frames;
    sprite->anim_speed = speed;
    *spr_ptr = sprite;
    return 0;
}

int spriteDestroy(const void *spr)
{
    if (spr == NULL) {
        RND_WARN("spr is NULL");
        return 0;
    }
    SDL_DestroyTexture(((Sprite*)spr)->tex);
    free((void*)spr);
    return 0;
}
