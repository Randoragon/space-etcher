#!/usr/bin/sh

# Auto-generates a header/source file pair for a new object.
# This is just a shortcut for creating objects quicker.
# The name of the new object has to be passed as STDIN argument.
# IMPORTANT: the object name should be passed in kebab-case.

objdir=src/objects
objregex='^[a-z-]\+$'

# Check for common errors
[ $# -ne 1 ] && printf "create-obj: exactly 1 argument required (object name)\n" && exit 1
expr "$1" : "$objregex" >/dev/null || { printf "create-obj: invalid object name (use kebab-case)\n" && exit 1; }
[ -f "$objdir/$1.h" ] || [ -f "$objdir/$1.c" ] && printf "create-obj: object already exists\n" && exit 1

# Cache filenames and casing styles
hfile="$objdir/obj-$1.h"
sfile="$objdir/obj-$1.c"
hguard="OBJ_$(printf "%s" "$1" | tr '[:lower:]-' '[:upper:]_')_H"
pascal="$(printf "%s" "$1" | sed -r 's/(^|-)([a-z])/\U\2/g')"

# Let the user verify everything is correct
printf "INCLUDE_GUARD: %s\n" "$hguard"
printf "PascalCase:    %s\n" "$pascal"
printf "continue? [Y\\\n] "
read -r ans
[ "$ans" = "N" ] || [ "$ans" = "n" ] && exit 0

# Generate the header file
printf "\nGenerating %s... " "$hfile"
printf "%s" \
"/** @file
 * Implementation of the \"$1\" object.
 */

#ifndef $hguard
#define $hguard

#include <RND_Game.h>
#include <chipmunk/chipmunk.h>

#include \"../sprite.h\"
#include \"macros.h\"

typedef struct Obj$pascal
{

} Obj$pascal;

int obj${pascal}Ctor(RND_GameInstance *self);
int obj${pascal}Dtor(RND_GameInstance *self);
int obj${pascal}Step(RND_GameInstance *self);
int obj${pascal}Draw(RND_GameInstance *self);

#endif /* $hguard */" >"$hfile"
printf "done.\n"

# Generate the source file
printf "Generating %s... " "$sfile"
printf "%s" \
"#include <RND_Game.h>
#include <chipmunk/chipmunk.h>
#include <SDL2/SDL.h>
#include <math.h>

#include \"${hfile#src/objects/}\"
#include \"macros.h\"
#include \"../space-etcher.h\"
#include \"../sprite.h\"
#include \"../input.h\"

extern cpSpace *main_space;
extern SDL_Renderer *renderer;
extern SDL_Window *window;

int obj${pascal}Ctor(RND_GameInstance *self)
{
    Obj${pascal} *o = self->data;

    return 0;
}

int obj${pascal}Dtor(RND_GameInstance *self)
{
    Obj${pascal} *o = self->data;

    return 0;
}

int obj${pascal}Step(RND_GameInstance *self)
{
    Obj${pascal} *o = self->data;

    return 0;
}

int obj${pascal}Draw(RND_GameInstance *self)
{
    Obj${pascal} *o = self->data;

    return 0;
}" >"$sfile"
printf "done.\n"
