/** @file
 * Implements a sprite struct and functions for
 * managing sprites.
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

/// A bundle of textures which compose a single sprite.
typedef struct Sprite
{
    /// A spritesheet texture.
    SDL_Texture *tex;
    /// Sprite width (single frame).
    uint32_t w;
    /// Sprite height (single frame).
    uint32_t h;
    /// Number of frames in the texture.
    uint32_t frames;
    /// Animation speed (only relevant for multi-frame sprites).
    float anim_speed;
} Sprite;

/** Loads a horizontal spritesheet into an array of SDL_Surfaces.
 *
 * No padding/margins are allowed, all frames must perfectly compose
 * a spritesheet.
 *
 * @param[out] spr_ptr Pointer that will be overwritten to point to
 * the newly allocated sprite.
 * @param[in] path The path to the image (PNG) to load.
 * @param[in] frames The number of frames in the horizontal spritesheet.
 * @param[in] speed The animation speed (@c 1.0 = 60FPS).
 * All frames must be of equal size.
 * @returns
 * - 0 - success
 * - 1 - out of memory
 * - 2 - failed to load texture
 * - 3 - texture width not divisible by @p frames
 */
int loadSpritesheet(Sprite **spr_ptr, const char *path, uint32_t frames, float speed);

/** Frees all memory associated with a sprite.
 *
 * This function should eventually be called for every sprite
 * created with @ref loadSpritesheet.
 *
 * @param[in] spr A pointer to the sprite.
 * @returns
 * - 0
 */
int spriteDestroy(const void *spr);

#endif /* SPRITE_H */
