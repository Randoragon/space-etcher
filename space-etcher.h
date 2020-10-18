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
void init();
void loadResources();
void gameloop();
void listen();
void step();
void draw();
void cleanup();

// Global variables
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Event input;
bool running;

#endif /* SPACE_ETCHER_H */
