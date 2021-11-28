#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))


inline int WINDOW_WIDTH = 1080;
inline int WINDOW_HEIGHT = 720;
inline int WINDOW_RESIZABLE = 0;//WINDOW_RESIZABLE;

inline int last_frame_time = 0;
inline float delta_time = 0;
inline int game_is_running = false;
inline SDL_Window* gWindow = NULL;
inline SDL_Renderer* gRenderer = NULL;

class Engine
{
private:
    void _update(void (*update)());
public:
    Engine();
    ~Engine();
    int initialize_window();
    void start(void (*setup)(), void (*process_input)(), void (*update)(), void (*render)());
    void destroy_window();
};