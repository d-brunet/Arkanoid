#ifndef BONUS_H
#define BONUS_H

#include <SDL.h>

#include "iobjgraph.h"

#include "objsdl.h"

class Bonus : public IObjGraph
{
public:
    Bonus();
    Bonus(int id, int xPos, int yPos, SDL_Surface* srcSprite, SDL_Surface* srcShadow);

    int getId();

    int getXPos();
    int getYPos();
    void setXPos(int x);
    void setYPos(int y);

    void move();

    void draw(SDL_Surface* target) override;
    void drawShadow(SDL_Surface *target) override;

private:
    SDL_Surface* srcSprite;
    SDL_Surface* srcShadow;

    int id;
    int xSrcSprite;
    int ySrcSprite;
    int xSrcShadow;
    int ySrcShadow;
    int xPos;
    int yPos;

    int nbFrameSprite;

    int count;
    int xCurrentFrame;
};

#endif // BONUS_H
