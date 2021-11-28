#include <iostream>
#include <math.h>
#include "Entity.h"
#include "Rsp.h"

inline int ENTITY_SIZE = 25;

Entity::Entity(RPS rps, SDL_Point pozition):rps(rps){
    this->rect = {pozition.x, pozition.y, ENTITY_SIZE, ENTITY_SIZE};
}

SDL_Point Entity::getPoz() const{
    return {this->rect.x, this->rect.y};
}

RPS Entity::getRps() const{
    return this->rps;
}

int Entity::getChangeCounter() const{
    return this->changeCounter;
}


void Entity::setRps(RPS rsp){
    this->rps = rsp;
    ++this->changeCounter;
}

void Entity::setPoz(SDL_Point pozition){
    this->rect.x = pozition.x;
    this->rect.y = pozition.y;
}

extern SDL_Renderer* gRenderer;
void Entity::draw(){
	SDL_RenderCopy(gRenderer, gRPSTexture[this->rps], NULL, &this->rect);
}

bool Entity::collision(Entity& enemy){
    SDL_Point enemyPoz = enemy.getPoz(); 
    int dx = this->rect.x - enemyPoz.x;
    int dy = this->rect.y - enemyPoz.y;
    int distance = sqrt(dx * dx + dy * dy);

    if (distance < ENTITY_SIZE) {
        return true;
    }
    return false;
}

inline std::ostream& operator<<(std::ostream& os, const SDL_Point& point){
    os << "x: " << point.x << " y: " << point.y;
    return os;
}
std::ostream& operator<<(std::ostream& os, const Entity& e){
    os << e.getPoz() << std::endl;
    os << e.getRps() << std::endl;
    os << "ChangeCounter: " << e.getChangeCounter();
    return os;
}   

