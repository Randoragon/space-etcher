/** @file
  * The main header file of the game.
  */

#ifndef SPACE_ETCHER_H
#define SPACE_ETCHER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <RND_BitArray.h>
#include <RND_Game.h>
#include <RND_HashMap.h>
#include <chipmunk/chipmunk.h>

/********************************************************
 *                         MACROS                       *
 ********************************************************/

/// Oneliner for adding sprites at the @ref loadResources stage.
#define ADD_SPRITE(name, path, frames, speed) \
    do { \
        Sprite *spr; \
        loadSpritesheet(&spr, path, frames, speed); \
        RND_hashMapAdd(sprites, name, spr); \
    } while (0)

/***********************************************************
 *                       CONSTANTS                         *
 ***********************************************************/

/// The width of the window.
#define CANVAS_WIDTH 1366
/// The height of the window.
#define CANVAS_HEIGHT 768
/// In-game target frames per second.
#define FPS 60
/// In-game gravity value (for Chipmunk).
#define GRAVITY 640


/***********************************************************
 *                       STRUCTURES                        *
 ***********************************************************/


/***********************************************************
 *                       FUNCTIONS                         *
 ***********************************************************/

/** Initializes libraries and global variables.
 *
 * This procedure is called once when the program starts,
 * it initializes some global variables and the SDL2 and
 * RND_game libraries.
 */
void init();

/// Loads default game resources into memory.
void loadResources();

/// Executes code that needs to be run once before @ref gameLoop.
void gameBegin();

/** Enters the game event loop.
 *
 * The loop calls @ref listen, @ref step and @ref draw functions
 * respectively, and repeats itself at @ref FPS frames per second.
 */
void gameLoop();

/// Executes code that needs to be run once after @ref gameLoop ends.
void gameEnd();

/** Handles all enqueued SDL2 events.
 *
 * This function loops through all pending SDL2 events and
 * handles them appropriately. A lot of functionality relies
 * on having up-to-date event data, so it is important for
 * this function to be run at least once per game step and
 * before some other functions like @ref step.
 */
void listen();

/** Executes code based on the last @ref listen results.
 *
 * This function should only ever be called once per game step
 * inside the @ref gameLoop function, it advances the game
 * by one tick based on the previous step and the latest event
 * data (obtained by @ref listen).
 */
void step();

/** Draws the current game state to a texture.
 *
 * This function is used to updates the screen, and along with
 * @ref listen and @ref step is one of the vital components of
 * @ref gameLoop.  It should be called after @ref step, because
 * the state of all object variables etc. should be up-to-date.
 * @param[out] target An initialized texture to draw to.
 */
void draw(SDL_Texture *target);

/** Frees all resources and prepares the game for an exit.
 *
 * This function is run once right before the game is terminated.
 */
void cleanup();

/***********************************************************
 *                   GLOBAL VARIABLES                      *
 ***********************************************************/

/// The main SDL2 game window.
extern SDL_Window *window;

/// The renderer for @ref window.
extern SDL_Renderer *renderer;

/// The program will @ref cleanup and exit when this is set to @c false.
extern bool running;

/// Handler for instance step event, executed in @ref step.
extern RND_GameHandler *step_handler;

/// Handler for instance draw event, executed in @ref draw.
extern RND_GameHandler *draw_handler;

/// Chipmunk physics engine space.
extern cpSpace *main_space;

/// An map of all sprites.
extern RND_HashMap *sprites;

#endif /* SPACE_ETCHER_H */
