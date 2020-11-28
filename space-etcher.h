/** @file
  * The main header file of the game.
  */

#ifndef SPACE_ETCHER_H
#define SPACE_ETCHER_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <RND_BitMap.h>
#include <RND_Game.h>
#include <chipmunk/chipmunk.h>


/***********************************************************
 *                       CONSTANTS                         *
 ***********************************************************/

#define CANVAS_WIDTH 1366
#define CANVAS_HEIGHT 768
#define FPS 60
#define GRAVITY 1000


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

/** Draws the current game state to the screen.
 *
 * This function updates the screen, and along with @ref listen
 * and @ref step is one of the vital components of @ref gameLoop.
 * It should be called after @ref step, because the state of
 * all object variables etc. should be up-to-date.
 */
void draw();

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

#endif /* SPACE_ETCHER_H */
