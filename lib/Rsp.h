#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum RPS {Rock=0, Paper=1, Scissors=2};

inline SDL_Texture* gRPSTexture[3] = {nullptr}; 

const char* ToString(RPS rps);
std::ostream& operator<<(std::ostream& os, const RPS& rsp);
RPS operator>>(RPS root, RPS (*func)(RPS));

RPS GetPrey(RPS rps);
RPS GetEnemy(RPS rps);