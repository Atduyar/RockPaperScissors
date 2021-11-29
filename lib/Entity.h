#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Rsp.h"

class Entity{
    public:
        Entity(RPS rps, SDL_Point pozition);
        SDL_Point getPoz() const;
        SDL_FPoint getFPoz() const;
        SDL_Rect getRect() const;
        RPS getRps() const;
        int getChangeCounter() const;

        void setPoz(SDL_Point pozition);
        void setRps(RPS rsp);
        
        void draw();
        void move(SDL_Point move);
        void moveF(SDL_FPoint move);
        
        bool collision(Entity& enemy);
    private:
        RPS rps;
        SDL_FRect rect;
        int changeCounter = 0;
};

SDL_Point operator-(const SDL_Point& rp, const SDL_Point& p);
SDL_Point& operator/=(SDL_Point& rootP, const size_t& x);
SDL_Point& operator+=(SDL_Point& rootP, const SDL_Point& point);
std::ostream& operator<<(std::ostream& os, const SDL_Point& point);
std::ostream& operator<<(std::ostream& os, const Entity& e);