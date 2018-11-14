#ifndef BRICK_H
#define BRICK_H


#include "objsdl.h"

#include "iobjgraph.h"

#include "bonus.h"

#include <SDL.h>

class Brick : public IObjGraph
{
public:
    Brick();
    Brick(int id, int numLvl, int xPos, int yPos, SDL_Surface* srcSprite, SDL_Surface* srcShadow);

    int getId();

    int getLife();
    void setLife(int l);

    int getXPos();
    int getYPos();

    int getPoint();

    void setBonus(Bonus b);
    Bonus getBonus();

    bool haveBonus();

    void draw(SDL_Surface *target) override;
    void drawShadow(SDL_Surface *target) override;

private:
    SDL_Surface* srcSprite;
    SDL_Surface* srcShadow;

    int id;
    int xSrcSprite;
    int ySrcSprite;
    int xSrcShadow;
    int ySrcShadow;
    int xSrcDestroy;
    int ySrcDestroy;
    int xPos;
    int yPos;

    int life;
    int point;

    int nbFrameSprite;
    int count;
    int wait;

    Bonus bonus;
    bool containBonus;
};

#endif // BRICK_H
