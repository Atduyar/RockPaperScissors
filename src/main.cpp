#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>

#include "Entity.h"
#include "Engine.h"
Engine engine;

TTF_Font* gFont;

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
inline int ENTITY_SIZE = 25;
//inline int ENTITY_RADIUS = 12;

std::vector<Entity*> entitys;

void process_input() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	    case SDL_QUIT:
		    game_is_running = false;
		    break;
	    case SDL_KEYDOWN:
		    if (event.key.keysym.sym == SDLK_ESCAPE) {
		    	game_is_running = false;
		    }
		    break;
	}
}

void setup() {
	srand(time(NULL));//random
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

	gFont = TTF_OpenFont("ttf/OpenSans-Bold.ttf", 12);
	if (gFont == nullptr){
		std::cout << " ERROR TTF_OpenFont";
		return;
	}

    std::string path = std::string(SDL_GetBasePath()) + "../assets/img/rock.png";
	gRPSTexture[Rock] = IMG_LoadTexture(gRenderer, path.c_str());
    if( gRPSTexture[Rock] == NULL )
    {
        fprintf(stderr, "Failed to load texture image!\nError info: %s\n", IMG_GetError());
    }

    path = std::string(SDL_GetBasePath()) + "../assets/img/paper.png";
	gRPSTexture[Paper] = IMG_LoadTexture(gRenderer, path.c_str());
    if( gRPSTexture[Paper] == NULL )
    {
        fprintf(stderr, "Failed to load texture image!\nError info: %s\n", IMG_GetError());
    }

    path = std::string(SDL_GetBasePath()) + "../assets/img/scissors.png";
	gRPSTexture[Scissors] = IMG_LoadTexture(gRenderer, path.c_str());
    if( gRPSTexture[Scissors] == NULL )
    {
        fprintf(stderr, "Failed to load texture image!\nError info: %s\n", IMG_GetError());
    }
	//TTFoLD
	// gTextTexture = renderText("Atduyar", gFont, (SDL_Color){0xFF,0xFF,0xFF,0xFF}, gRenderer);
}

void update() {
    for(size_t i = 0; i < entitys.size();++i){
        for(size_t j = i+1; j < entitys.size();++j){
            if(entitys[i]->collision(*entitys[j])){
                if(entitys[i]->getRps()>>GetPrey == entitys[j]->getRps()){
                    entitys[j]->setRps(entitys[i]->getRps());
                }
                else{
                    entitys[i]->setRps(entitys[j]->getRps());
                }
            }
        }
    }
}

SDL_Rect testR;
void render() {
	SDL_SetRenderDrawColor(gRenderer, 30, 27, 25, 20);
	SDL_RenderClear(gRenderer);

    for(auto* entity : entitys){
        entity->draw();
        //std::cout << *entity << std::endl;
    }

	//SDL_RenderCopy(gRenderer, gRPSTexture[Rock], NULL, &testR);
    //SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255 );
	//SDL_RenderDrawRect(gRenderer, &testR);

	SDL_RenderPresent(gRenderer);
}


int main(int argc, char* args[]) {
	srand(time(0));

    WINDOW_WIDTH = 720;
    WINDOW_HEIGHT = 720;
    testR = {WINDOW_WIDTH/4*1, WINDOW_HEIGHT/4*1, 25, 25};
    
    for(int i = 0; i < 60;++i) entitys.push_back(new Entity(RPS(rand()%3), 
        {rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT} ));

	engine.start(setup, process_input, update, render);

	printf("Game is stoping...\n");
	return 0;
}

