#!/usr/bin/sh
#
# Auto-generates the objs/include.h file, which is then included
# by space-etcher.c. This is a big commodity, as the number of
# objects in the project will rise inevitably, and each object
# needs its own header and source files, which then need to be
# included by the main program.

dir="$(dirname -- "$0")"

file="$(printf "%s/%s" "$dir" "include.h")"

printf "#ifndef OBJ_INCLUDE_H
#define OBJ_INCLUDE_H
\n" >"$file"

for i in "$dir/"*.h; do
    fname="$(basename -- "$i")"
    [ "$fname" != "include.h" ] && printf "#include \"%s\"\n" "$fname" >>"$file"
done

printf "\n#endif // OBJ_INCLUDE_H" >>"$file"
