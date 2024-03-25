#include "Entity.h"

#include <math.h>

#include <iostream>

#include "Rsp.h"

inline int ENTITY_SIZE = 25;

Entity::Entity(RPS rps, SDL_Point pozition) : rps(rps) {
    this->rect = {(float)pozition.x, (float)pozition.y, (float)ENTITY_SIZE,
                  (float)ENTITY_SIZE};
}

SDL_Point Entity::getPoz() const {
    return {(int)this->rect.x, (int)this->rect.y};
}
SDL_FPoint Entity::getFPoz() const { return {this->rect.x, this->rect.y}; }
SDL_Rect Entity::getRect() const {
    return {(int)this->rect.x, (int)this->rect.y, (int)this->rect.w,
            (int)this->rect.h};
}

RPS Entity::getRps() const { return this->rps; }

int Entity::getChangeCounter() const { return this->changeCounter; }

void Entity::setRps(RPS rsp) {
    this->rps = rsp;
    ++this->changeCounter;
}

void Entity::setPoz(SDL_Point pozition) {
    this->rect.x = pozition.x;
    this->rect.y = pozition.y;
}

extern SDL_Renderer* gRenderer;
void Entity::draw() {
    SDL_RenderCopyF(gRenderer, gRPSTexture[this->rps], NULL, &this->rect);
}

void Entity::move(SDL_Point move) {
    this->rect.x += move.x;
    this->rect.y += move.y;
}
void Entity::moveF(SDL_FPoint move) {
    this->rect.x += move.x;
    this->rect.y += move.y;
}

bool Entity::collision(Entity& enemy) {
    SDL_Point enemyPoz = enemy.getPoz();
    int dx = this->rect.x - enemyPoz.x;
    int dy = this->rect.y - enemyPoz.y;
    int distance = sqrt(dx * dx + dy * dy);

    if (distance < ENTITY_SIZE) {
        return true;
    }
    return false;
}

SDL_Point operator-(const SDL_Point& rp, const SDL_Point& p) {
    return {rp.x - p.x, rp.y - p.y};
}
SDL_Point& operator/=(SDL_Point& rootP, const size_t& x) {
    rootP.x /= x;
    rootP.y /= x;
    return rootP;
}
SDL_Point& operator+=(SDL_Point& rootP, const SDL_Point& point) {
    rootP.x += point.x;
    rootP.y += point.y;
    return rootP;
}
std::ostream& operator<<(std::ostream& os, const SDL_Point& point) {
    os << "x: " << point.x << " y: " << point.y;
    return os;
}
std::ostream& operator<<(std::ostream& os, const Entity& e) {
    os << e.getPoz() << std::endl;
    os << e.getRps() << std::endl;
    os << "ChangeCounter: " << e.getChangeCounter();
    return os;
}
