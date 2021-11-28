#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Rsp.h"

class Entity{
    public:
        Entity(RPS rps, SDL_Point pozition);
        SDL_Point getPoz() const;
        RPS getRps() const;
        int getChangeCounter() const;

        void setPoz(SDL_Point pozition);
        void setRps(RPS rsp);
        
        void draw();
        
        bool collision(Entity& enemy);
    private:
        RPS rps;
        SDL_Rect rect;
        int changeCounter = 0;
};

inline std::ostream& operator<<(std::ostream& os, const SDL_Point& point);
std::ostream& operator<<(std::ostream& os, const Entity& e);