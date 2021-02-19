#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <RND_Game.h>
#include <RND_ErrMsg.h>
#include <RND_BitArray.h>
#include <RND_HashMap.h>
#include <RND_Utils.h>

#include "space-etcher.h"
#include "objects/include.h"
#include "input.h"
#include "sprite.h"

SDL_Window *window;
SDL_Renderer *renderer;
bool running;
RND_GameHandler *step_handler, *draw_handler;
cpSpace *main_space;
RND_HashMap *sprites;

void init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        RND_ERROR("Failed to initialize SDL2 (%s)", SDL_GetError());
        exit(1);
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        RND_ERROR("Failed to initialize SDL2_image (%s)", IMG_GetError());
    }
    window = SDL_CreateWindow("Space Etcher",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            CANVAS_WIDTH,
            CANVAS_HEIGHT,
            SDL_WINDOW_SHOWN);
    if (window == NULL) {
        RND_ERROR("Failed to create window (%s)", SDL_GetError());
        exit(1);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        RND_ERROR("Failed to create renderer (%s)", SDL_GetError());
        exit(1);
    }
    if (!(events = eventSnapshotCreate())) {
        RND_ERROR("Failed to create EventSnapshot");
        exit(1);
    }
    if (!(events_prev = eventSnapshotCreate())) {
        RND_ERROR("Failed to create EventSnapshot");
        exit(1);
    }
    if (!(main_space = cpSpaceNew())) {
        RND_ERROR("Failed to create Chipmunk space");
        exit(1);
    }
    if (RND_gameInit()) {
        RND_ERROR("Failed to initialize RND_Game");
        exit(1);
    }
    step_handler = RND_gameHandlerCreate(NULL);
    draw_handler = RND_gameHandlerCreate(NULL);
    if (!(sprites = RND_hashMapCreate(4096, NULL))) {
        RND_ERROR("Failed to create sprites hashmap");
        exit(1);
    }
    running = true;
}

void loadResources()
{
    ADD_ALL_OBJECTS();
    ADD_SPRITE("ball", "data/sprites/spr_ball.png", 38, 0.5);
    ADD_SPRITE("square", "data/sprites/spr_square.png", 38, 0.5);
}

void gameBegin()
{
    srand(0);

    // Spawn walls
    RND_GameInstanceId id;
    id = RND_gameInstanceSpawn(OBJI_WALL);
    objWallSet(RND_instances[id].data,
            (SDL_Point) { 0, 200 },
            (SDL_Point) { CANVAS_WIDTH / 2, CANVAS_HEIGHT - 10 },
            9);
    id = RND_gameInstanceSpawn(OBJI_WALL);
    objWallSet(RND_instances[id].data,
            (SDL_Point) { CANVAS_WIDTH / 2, CANVAS_HEIGHT - 10 },
            (SDL_Point) { CANVAS_WIDTH, 200 },
            9);
    id = RND_gameInstanceSpawn(OBJI_WALL);
    objWallSet(RND_instances[id].data,
            (SDL_Point) { 0, 0 },
            (SDL_Point) { CANVAS_WIDTH, 0 },
            9);
    id = RND_gameInstanceSpawn(OBJI_WALL);
    objWallSet(RND_instances[id].data,
            (SDL_Point) { 0, 0 },
            (SDL_Point) { 0, 200 },
            9);
    id = RND_gameInstanceSpawn(OBJI_WALL);
    objWallSet(RND_instances[id].data,
            (SDL_Point) { CANVAS_WIDTH, 0 },
            (SDL_Point) { CANVAS_WIDTH, 200 },
            9);

    id = RND_gameInstanceSpawn(OBJI_SPAWNER);
    RND_GAME_INST(id, ObjSpawner).self_id = id;
    cpSpaceSetGravity(main_space, cpv(0, GRAVITY));
}

void gameLoop()
{
    /* This entire function is heavily based on the "Fix Your Timestep!" article
     * written by Glenn Fiedler. Read the article here:
     * https://www.gafferongames.com/post/fix_your_timestep/
     */

    // For wall-clock time tracking and adjustments
    double dt = 1.0 / FPS,
           prev_time,
           accumulator;

    // Textures for alpha blending previous and current frame
    SDL_Texture *last_tex, *current_tex;
    Uint32 format = SDL_GetWindowPixelFormat(window);
    last_tex    = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET,
            CANVAS_WIDTH, CANVAS_HEIGHT);
    current_tex = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET,
            CANVAS_WIDTH, CANVAS_HEIGHT);
    SDL_SetTextureBlendMode(current_tex, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(last_tex, SDL_BLENDMODE_BLEND);

    prev_time = RND_getWallTime_usec() / 1e6;
    accumulator = 0.0;

    while (running) {
        double new_time, frame_time;
        new_time   = RND_getWallTime_usec() / 1e6;
        frame_time = new_time - prev_time;
        prev_time  = new_time;
        accumulator += frame_time;

        int timeout = 0;
        while (accumulator >= dt) {
            listen();
            cpSpaceStep(main_space, dt);
            step();
            accumulator -= dt;
            // cap repetitions to avoid the "spiral of death"
            if (++timeout > 5) {
                accumulator = 0;
            }
        }

        // Swap current and last textures
        SDL_Texture *tmp;
        tmp = current_tex;
        current_tex = last_tex;
        last_tex = tmp;

        // Draw state to current texture
        draw(current_tex);

        // Blend current and last textures for smoothing effect
        Uint8 alpha = 255.0 * accumulator / dt;
        SDL_SetTextureAlphaMod(last_tex, 255 - alpha);
        SDL_RenderCopy(renderer, last_tex, NULL, NULL);
        SDL_SetTextureAlphaMod(current_tex, alpha);
        SDL_RenderCopy(renderer, current_tex, NULL, NULL);

        SDL_RenderPresent(renderer);
    }
}

void gameEnd()
{
}

void listen()
{
    for (int i = 0; i < KEY_SIZE; i++) {
        bool last = keyIsDown(i);
        RND_bitArraySet(events_prev->keyboard, i, last);
    }
    SDL_Event ev;
    while (SDL_PollEvent(&ev) > 0) {
        switch(ev.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN: case SDL_KEYUP:
                handleKey(ev.key);
                break;
            default:
                break;
        }
    }
}

void step()
{
    int err;
    if ((err = RND_gameHandlerRun(step_handler))) {
        RND_ERROR("step handler returned %d", err);
    }
}

void draw(SDL_Texture *target)
{
    SDL_SetRenderTarget(renderer, target);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    int err;
    if ((err = RND_gameHandlerRun(draw_handler))) {
        RND_ERROR("draw handler returned %d", err);
    }
    SDL_SetRenderTarget(renderer, NULL);
}

void cleanup()
{
    RND_hashMapDestroy(sprites, spriteDestroy); // Must come before SDL_Quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    cpSpaceFree(main_space); // Must come before RND_gameCleanup
    eventSnapshotDestroy(events);
    eventSnapshotDestroy(events_prev);
    RND_gameCleanup();
}

int main(int argc, char *argv[])
{
    init();
    loadResources();
    gameBegin();
    gameLoop();
    gameEnd();
    cleanup();

    return EXIT_SUCCESS;
}
