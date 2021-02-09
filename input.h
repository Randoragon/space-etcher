/** @file
 * Functions and constants governing user input,
 * such as keyboard and mouse.
 */

#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <RND_BitArray.h>


/***********************************************************
 *                       CONSTANTS                         *
 ***********************************************************/

/** This enum maps keys to array indices.
 *
 * @c SDLK_* macros are good for determining keysyms,
 * but their numerical values aren't suited to be array
 * indices, because they're all over the place. The values
 * contained in this enum are used to access the @ref
 * EventSnapshot::keyboard arrays of @ref events and @ref
 * events_prev.
 */
typedef enum EKeyIndex
{
    KEY_JUMP,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_CROUCH,
    KEY_SIZE     /* KEY_SIZE needs to be last */
} EKeyIndex;

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
    RND_BitArray *keyboard;
};


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
 * @param[in] es A pointer to the snapshot.
 * @returns
 * - 0 - success
 * - 1 - failure
 */
int eventSnapshotDestroy(EventSnapshot *es);

/** Handles key presses/releases and updates the @ref events
 * and @ref events_prev variables.
 */
void handleKey(SDL_KeyboardEvent kev);

/** Returns whether a key is being held down or not.
 *
 * This function only retrieves data from the
 * @ref events variable, and therefore requires
 * a preceding call to @ref listen, which updates
 * the contents of @ref events and @ref events_prev.
 *
 * @param[in] key The unique key index.
 * @returns
 * - @c true - key is being held down
 * - @c false - key is not being held down
 */
inline bool keyIsDown(EKeyIndex key)
{
    return RND_bitArrayGet(events->keyboard, key);
}

/** Returns whether a key has just been pressed or not.
 *
 * A key is considered to "have just been pressed" if
 * its state stored in @ref events_prev is @c false
 * (not pressed), and its current state is @c true (pressed).
 *
 * This function only retrieves data from the @ref
 * events and @ref events_prev variables, and therefore
 * requires a preceding call to @ref listen, which
 * updates the contents of @ref events and @ref
 * events_prev.
 *
 * @param[in] key The unique key index.
 * @returns
 * - @c true - key has just been pressed
 * - @c false - otherwise
 */
inline bool keyIsPressed(EKeyIndex key)
{
    return RND_bitArrayGet(events->keyboard, key) &&
        !RND_bitArrayGet(events_prev->keyboard, key);
}

/** Returns whether a key has just been released or not.
 *
 * A key is considered to "have just been released" if
 * its state stored in @ref events_prev is @c true
 * (pressed), and its current state is @c false (not pressed).
 *
 * This function only retrieves data from the @ref
 * events and @ref events_prev variables, and therefore
 * requires a preceding call to @ref listen, which
 * updates the contents of @ref events and @ref
 * events_prev.
 *
 * @param[in] key The unique key index.
 * @returns
 * - @c true - key has just been released
 * - @c false - otherwise
 */
inline bool keyIsReleased(EKeyIndex key)
{
    return !RND_bitArrayGet(events->keyboard, key) &&
        RND_bitArrayGet(events_prev->keyboard, key);
}

#endif // INPUT_H
