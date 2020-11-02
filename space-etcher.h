#ifndef SPACE_ETCHER_H
#define SPACE_ETCHER_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <RND_BitMap.h>


/***********************************************************
 *                       CONSTANTS                         *
 ***********************************************************/

#define CANVAS_WIDTH 1366
#define CANVAS_HEIGHT 768
#define FPS 60


/********************************************************
 *                      STRUCTURES                      *
 ********************************************************/

/// @cond
typedef struct EventSnapshot EventSnapshot;
/// @endcond

/** Holds a single snapshot of all events handled by @ref listen.
 *
 * To make it easy to check if a key is pressed, or some other
 * event type has occurred, each game loop calls the @ref listen
 * function, which handles the SDL event queue and stores the
 * results inside two global variables (@ref events and @ref
 * events_prev). With this thin extra layer of abstraction,
 * other functions can easily tap into these structures to obtain
 * information (for example about the keyboard state). The
 * contents of this struct are custom-tailored to the game's
 * needs, i.e. only the information needed by the game is stored,
 * and if someone were to introduce some new keybinding, they
 * would have to add that key to this struct and update @ref
 * listen to store its information in @ref events and @ref 
 * events_prev.
 */
struct EventSnapshot
{
    /// Binary values representing individual key states.
    RND_BitMap *keyboard;
};

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

/** Enters the game event loop.
 *
 * The loop calls @ref listen, @ref step and @ref draw functions
 * respectively, and repeats itself at @ref FPS frames per second.
 */
void gameloop();

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
 * inside the @ref gameloop function, it advances the game
 * by one tick based on the previous step and the latest event
 * data (obtained by @ref listen).
 */
void step();

/** Draws the current game state to the screen.
 *
 * This function updates the screen, and along with @ref listen
 * and @ref step is one of the vital components of @ref gameloop.
 * It should be called after @ref step, because the state of
 * all object variables etc. should be up-to-date.
 */
void draw();

/** Frees all resources and prepares the game for an exit.
 *
 * This function is run once right before the game is terminated.
 */
void cleanup();

/** Allocates and initializes a new EventSnapshot structure.
 *
 * @returns 
 * - pointer to the new struct - success
 * - @c NULL - insufficient memory
 */
EventSnapshot *eventSnapshotCreate();

/** Frees all memory associated with an EventSnapshot.
 *
 * @param es A pointer to the snapshot.
 * @returns
 * - 0 - success
 * - 1 - failure
 */
int eventSnapshotDestroy(EventSnapshot *es);

/** Handles key presses/releases and updates the @ref events
 * and @ref events_prev variables.
 */
void handleKey(SDL_KeyboardEvent kev);

/***********************************************************
 *                   GLOBAL VARIABLES                      *
 ***********************************************************/

/// The main SDL2 game window.
extern SDL_Window *window;

/// The renderer for @ref window.
extern SDL_Renderer *renderer;

/** Points to the results of the last @ref listen run.
  * It can be used in conjunction with @ref events_prev for example
  * to check for individual button presses.
  */
extern EventSnapshot *events;

/** Points to the results of the second last @ref listen run.
  * It can be used in conjunction with @ref events for example to check
  * for individual button presses.
  */
extern EventSnapshot *events_prev;

/// The program will @ref cleanup and exit when this is set to @c false.
extern bool running;

#endif /* SPACE_ETCHER_H */
