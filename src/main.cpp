#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Engine.h"
#include "Entity.h"
Engine engine;

TTF_Font* gFont;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
inline int ENTITY_SIZE = 25;
inline int ENTITY_COUNT = 90;
// inline int ENTITY_RADIUS = 12;

SDL_Texture* infoTextTexture;
std::string infoText = "first time";
std::vector<Entity*> entitys;

void restart();
void start();

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
            if (event.key.keysym.sym == SDLK_r) {
                restart();
            }
            break;
    }
}

void setup() {
    srand(time(NULL));  // random
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

    gFont = TTF_OpenFont("ttf/OpenSans-Bold.ttf", 12);
    if (gFont == nullptr) {
        std::cout << " ERROR TTF_OpenFont";
        return;
    }

    std::string path =
        std::string(SDL_GetBasePath()) + "../assets/img/rock.png";
    gRPSTexture[Rock] = IMG_LoadTexture(gRenderer, path.c_str());
    if (gRPSTexture[Rock] == NULL) {
        fprintf(stderr, "Failed to load texture image!\nError info: %s\n",
                IMG_GetError());
    }

    path = std::string(SDL_GetBasePath()) + "../assets/img/paper.png";
    gRPSTexture[Paper] = IMG_LoadTexture(gRenderer, path.c_str());
    if (gRPSTexture[Paper] == NULL) {
        fprintf(stderr, "Failed to load texture image!\nError info: %s\n",
                IMG_GetError());
    }

    path = std::string(SDL_GetBasePath()) + "../assets/img/scissors.png";
    gRPSTexture[Scissors] = IMG_LoadTexture(gRenderer, path.c_str());
    if (gRPSTexture[Scissors] == NULL) {
        fprintf(stderr, "Failed to load texture image!\nError info: %s\n",
                IMG_GetError());
    }
    // TTFoLD
    //  gTextTexture = renderText("Atduyar", gFont,
    //  (SDL_Color){0xFF,0xFF,0xFF,0xFF}, gRenderer);
}

int speed = 4;
int winCounter[3] = {0};
void update() {
    SDL_SetRenderDrawColor(gRenderer, 30, 27, 25, 20);
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);

    RPS finishRps = entitys[0]->getRps();
    bool finish = true;
    for (size_t i = 0; i < entitys.size(); ++i) {
        SDL_Point avgPoz = {WINDOW_WIDTH, WINDOW_HEIGHT};

        for (size_t j = 0; j < i + 1; ++j) {
            if (entitys[i]->getRps() >> GetPrey == entitys[j]->getRps()) {
                SDL_Point temp = entitys[j]->getPoz() - entitys[i]->getPoz();
                if (abs(temp.x) + abs(temp.y) < abs(avgPoz.x) + abs(avgPoz.y))
                    avgPoz = temp;
            }
        }

        for (size_t j = i + 1; j < entitys.size(); ++j) {
            if (entitys[i]->collision(*entitys[j])) {
                if (entitys[i]->getRps() >> GetPrey == entitys[j]->getRps()) {
                    entitys[j]->setRps(entitys[i]->getRps());
                } else {
                    entitys[i]->setRps(entitys[j]->getRps());
                }
            }
            if (entitys[i]->getRps() >> GetPrey == entitys[j]->getRps()) {
                SDL_Point temp = entitys[j]->getPoz() - entitys[i]->getPoz();
                if (abs(temp.x) + abs(temp.y) < abs(avgPoz.x) + abs(avgPoz.y))
                    avgPoz = temp;
            }
        }
        if (avgPoz.x + avgPoz.y == WINDOW_WIDTH + WINDOW_HEIGHT)
            avgPoz = {0, 0};
        else {
            SDL_RenderDrawLine(gRenderer, entitys[i]->getPoz().x,
                               entitys[i]->getPoz().y,
                               entitys[i]->getPoz().x + avgPoz.x,
                               entitys[i]->getPoz().y + avgPoz.y);

            double angle = atan2(avgPoz.x, avgPoz.y);
            // std::cout << sin(angle)*speed << " - "  << cos(angle)*speed <<
            // std::endl;
            entitys[i]->moveF(
                {(float)sin(angle) * speed, (float)cos(angle) * speed});
        }
        if (finishRps != entitys[i]->getRps()) finish = false;
    }
    if (finish) {
        winCounter[finishRps]++;
        infoText = "r:" + std::to_string(winCounter[0]) +
                   " p:" + std::to_string(winCounter[1]) +
                   " s:" + std::to_string(winCounter[2]) + "        " +
                   ToString(finishRps);
        std::cout << "r:" << winCounter[0] << " p:" << winCounter[1]
                  << " s:" << winCounter[2] << "\t" << ToString(finishRps)
                  << std::endl;
        restart();
    }
}

SDL_Rect testR;
void render() {
    // SDL_SetRenderDrawColor(gRenderer, 30, 27, 25, 20);
    // SDL_RenderClear(gRenderer);

    for (auto* entity : entitys) {
        entity->draw();
        // std::cout << *entity << std::endl;
    }

    SDL_Surface* surf = TTF_RenderText_Blended(gFont, infoText.c_str(),
                                               {0xFF, 0xFF, 0xFF, 0xFF});
    if (surf == nullptr) {
        std::cout << " ERROR TTF_RenderText";
        return;
    }

    infoTextTexture = SDL_CreateTextureFromSurface(gRenderer, surf);
    if (infoTextTexture == nullptr) {
        std::cout << " ERROR CreateTexture";
    }
    // Clean up the surface and font
    testR = {0, 0, surf->w, surf->h};
    SDL_RenderCopy(gRenderer, infoTextTexture, NULL, &testR);
    SDL_FreeSurface(surf);
    // SDL_RenderCopy(gRendgit checkout mastergit checkout mastererer,
    // gRPSTexture[Rock], NULL, &testR); SDL_SetRenderDrawColor(gRenderer, 255,
    // 255, 255, 255 ); SDL_RenderDrawRect(gRenderer, &testR);

    SDL_RenderPresent(gRenderer);
}
void restart() {
    entitys.clear();
    start();
}
void start() {
    for (int i = 0; i < ENTITY_COUNT; ++i) {
        RPS rps = RPS(rand() % 3);
        SDL_Point poz = {rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT};
        entitys.push_back(new Entity(rps, poz));
    }
}

int main(int argc, char* args[]) {
    srand(time(0));

    WINDOW_WIDTH = 720;
    WINDOW_HEIGHT = 720;
    testR = {WINDOW_WIDTH / 4 * 1, WINDOW_HEIGHT / 4 * 1, 25, 25};

    start();

    engine.start(setup, process_input, update, render);

    printf("Game is stoping...\n");
    return 0;
}
