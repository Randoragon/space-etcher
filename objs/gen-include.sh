#!/usr/bin/sh

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
