#ifndef ROCKET_H
#define ROCKET_H

#include <SDL.h>

#include "iobjgraph.h"

#include "objsdl.h"

class Rocket : public IObjGraph
{
public:
    Rocket();
    Rocket(int xPos, int yPos, SDL_Surface* srcSprite, SDL_Surface* srcShadow);

    int getXPos();
    int getYPos();

    void setLife(int l);
    int getLife();

    void move();

    void draw(SDL_Surface *target);
    void drawShadow(SDL_Surface *target);

private:
    SDL_Surface* srcSprite;
    SDL_Surface* srcShadow;

    int xSrcSprite;
    int ySrcSprite;
    int xSrcShadow;
    int ySrcShadow;
    int xPos;
    int yPos;
};

#endif // ROCKET_H
