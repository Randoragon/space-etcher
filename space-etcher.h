#ifndef SPACE_ETCHER_H
#define SPACE_ETCHER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

// Constants
#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768
#define FPS 60

// Functions
int main(int argc, char *argv[0]);
int gameloop();

// Global variables
SDL_Window *window;
SDL_Surface *surface;
bool running;

#endif /* SPACE_ETCHER_H */
