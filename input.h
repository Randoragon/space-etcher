/** @file
 * Functions and constants governing user input,
 * such as keyboard and mouse.
 */

#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <RND_BitMap.h>


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

#endif // INPUT_H
