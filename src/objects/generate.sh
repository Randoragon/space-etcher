#!/usr/bin/sh
#
# Auto-generates the objects/include.h file, which is then included
# by space-etcher.c. This is a big commodity, as the number of
# objects in the project will rise inevitably, and each object
# needs its own header and source files, which then need to be
# included by the main program.

dir="$(dirname -- "$0")"
file="${dir}/include.h"
objregex='^obj-[a-z-]\+\.h$'

printf "%s" \
"#ifndef OBJ_INCLUDE_H
#define OBJ_INCLUDE_H

#include \"objects/macros.h\"
" >"$file"

kebabs=
for i in "$dir/"*.h; do
    fname="$(basename -- "$i")"
    if expr "$fname" : "$objregex" >/dev/null; then
        printf "#include \"%s\"\n" "$fname" >>"$file"

        kebab="${fname%.h}"
        kebab="${kebab#obj-}"
        kebabs="$kebabs $kebab"
    fi
done
printf "\n" >>"$file"


printf "%s" \
"#define ADD_ALL_OBJECTS() \\
    do { \\
" >>"$file"

for i in $kebabs; do
    uppersnake="$(printf "%s" "$i" | tr '[:lower:]-' '[:upper:]_')"
    pascal="$(printf "%s" "$i" | sed -r 's/(^|-)([a-z])/\U\2/g')"
    printf "%s" \
"        RND_GAME_OBJECT_ADD(Obj${pascal}, OBJI_${uppersnake}); \\
        RND_ctors[OBJI_${uppersnake}] = obj${pascal}Ctor; \\
        RND_dtors[OBJI_${uppersnake}] = obj${pascal}Dtor; \\
        RND_gameHandlerAdd(step_handler, OBJI_${uppersnake}, obj${pascal}Step); \\
        RND_gameHandlerAdd(draw_handler, OBJI_${uppersnake}, obj${pascal}Draw); \\
" >>"$file"
done

printf "%s" \
"   } while (0)

#endif /* OBJ_INCLUDE_H */" >>"$file"


