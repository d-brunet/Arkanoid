#ifndef ENEMY_H
#define ENEMY_H

#include <SDL.h>

#include "iobjgraph.h"

#include "objsdl.h"

class Enemy : public IObjGraph
{
public:
    Enemy();
    Enemy(int id, int xPos, int yPos, SDL_Surface* srcSprite, SDL_Surface* srcShadow);

    int getXPos();
    int getYPos();

    void setXSpeed(int x);
    void setYSpeed(int y);

    int getLife();
    void setLife(int l);

    bool getToLeft();
    void setToLeft(bool l);

    void move();

    int getPoint();

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
    int xSrcDestroy;
    int ySrcDestroy;
    int xPos;
    int yPos;

    int xSpeed;
    int ySpeed;

    int life;
    int point;

    bool toLeft;

    int nbFrameSprite;
    int nbFrameDestroy;

    int count;
    int xCurrentFrame;
    int yCurrentFrame;
};

#endif // ENEMY_H
