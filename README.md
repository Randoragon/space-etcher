# Space Etcher

## WORK IN PROGRESS

This game is in very early stages of development, it is not ready to be played yet.

---

Space Etcher is a game project I started to learn the ropes of SDL2.
The aim of the game is to provide a good real-time action-puzzle experience with
focus on speed, great mobility and a wide array of player abilities. The game should
offer a lot of content due to its complexity, while remaining feather-weight, running
fast and using system resources sparingly.

## Documentation

I try to maintain a [Doxygen](https://www.doxygen.nl) documentation in the comments.
Things may be outdated here and there, but it is generally the best way of examining
the code base without actually looking at source code. The Doxyfile contains configuration
for the doxygen utility, to generate a `docs` directory containing the documentation
simply run

    doxygen

from the project's root directory. Then you can open the `docs/html/index.html` file
in your web browser.

## Dependencies

- [SDL2](https://libsdl.org)
- [RND\_Game](https://github.com/randoragon/randoutils/tree/master/c-libs/game)
- [RND\_BitMap](https://github.com/randoragon/randoutils/tree/master/c-libs/bitmap)

## Installation

Run the following (if necessary, as root):

    make install

The executable will be copied to `/usr/local/bin/space-etcher`.
