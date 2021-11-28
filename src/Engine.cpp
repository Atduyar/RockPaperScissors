#include "Engine.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

extern TTF_Font* gFont;

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::start(void (*setup)(), void (*process_input)(), void (*update)(), void (*render)()){
	game_is_running = initialize_window();
    
	setup();
	
	SDL_Delay(1000);
	while (game_is_running) {

		process_input();
		_update(update);
		render();

		fflush(stdout);
	}

	destroy_window();
}

void Engine::_update(void (*update)()){
	//En son update yaptığından bu yana FRAME_TARGET_TIME kadar zaman geçmesini bekle
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);//bir fps e göresaniyede beklemesi gereken tik sayısını hesaplar
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) SDL_Delay(time_to_wait);
	//En son update yaptığından bu yana ne kadar zaman geçti(FRAME_TARGET_TIME kadar)
	//delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
	last_frame_time = SDL_GetTicks();

    update();
}

void Engine::destroy_window(){
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

int Engine::initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error SDL init\n");
		return false;
	}

	gWindow = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		WINDOW_RESIZABLE//SDL_WINDOW_RESIZABLE//0/*SDL_WINDOW_BORDERLESS*/
	);
	if (!gWindow) {
		fprintf(stderr, "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
	if (!gRenderer) {
		fprintf(stderr, "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}

 	int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        fprintf(stderr, "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
    }
	
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }
	return true;
}
