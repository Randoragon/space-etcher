#!/usr/bin/sh

# Auto-generates a header/source file pair for a new object.
# This is just a shortcut for creating objects quicker.
# The name of the new object has to be passed as STDIN argument.
# IMPORTANT: the object name should be passed in kebab-case.

objdir=src/objects

# Check for common errors
[ $# -ne 1 ] && printf "create-obj: exactly 1 argument required (object name)\n" && exit 1
[ -f "$objdir/$1.h" ] || [ -f "$objdir/$1.c" ] && printf "create-obj: object already exists\n" && exit 1

# Cache filenames and casing styles
hfile="$objdir/obj-$1.h"
sfile="$objdir/obj-$1.c"
hguard="OBJ_$(printf "%s" "$1" | tr '[:lower:]-' '[:upper:]_')_H"
pcase="$(printf "%s" "$1" | sed -r 's/(^|-)([a-z])/\U\2/g')"

# Let the user verify everything is correct
printf "INCLUDE_GUARD: %s\n" "$hguard"
printf "PascalCase:    %s\n" "$pcase"
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

#include <chipmunk/chipmunk.h>

#include \"../sprite.h\"
#include \"macros.h\"

typedef struct Obj$pcase
{

} Obj$pcase;

int obj${pcase}Ctor(void *self);
int obj${pcase}Dtor(void *self);
int obj${pcase}Step(void *self);
int obj${pcase}Draw(void *self);

#endif /* $hguard */" >"$hfile"
printf "done.\n"

# Generate the source file
printf "Generating %s... " "$sfile"
printf "%s" \
"#include <SDL2/SDL.h>
#include <math.h>

#include \"$hfile\"
#include \"macros.h\"
#include \"../space-etcher.h\"
#include \"../sprite.h\"
#include \"../input.h\"

extern cpSpace *main_space;

int obj${pcase}Ctor(void *self)
{
    Obj${pcase} *o = self;

    return 0;
}

int obj${pcase}Dtor(void *self)
{
    Obj${pcase} *o = self;

    return 0;
}

int obj${pcase}Step(void *self)
{
    Obj${pcase} *o = self;

    return 0;
}

int obj${pcase}Draw(void *self)
{
    Obj${pcase} *o = self;

    return 0;
}" >"$sfile"
printf "done.\n"
