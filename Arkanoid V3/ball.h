#ifndef BALL_H
#define BALL_H

#include "iobjgraph.h"

#include "objsdl.h"

#include <SDL.h>

class Ball : public IObjGraph
{
public:
    Ball();
    Ball(int xPos, int yPos, SDL_Surface* srcSprite, SDL_Surface* srcShadow);

    int getXSpeed();
    int getYSpeed();

    void setSpeed(int x, int y);
    void setXSpeed(int x);
    void setYSpeed(int y);

    int getXPos();
    int getYPos();

    void setPos(int x, int y);

    void move(bool slow);

    bool getXReverse();
    bool getYReverse();

    void setXReverse(bool xRev);
    void setYReverse(bool yRev);

    void draw(SDL_Surface* target) override;
    void drawShadow(SDL_Surface* target) override;

private:
    SDL_Surface* srcSprite;
    SDL_Surface* srcShadow;

    int xSrcSprite;
    int ySrcSprite;
    int xSrcShadow;
    int ySrcShadow;
    int xPos;
    int yPos;

    int xSpeed;
    int ySpeed;

    bool xReverse;
    bool yReverse;
};

#endif // BALL_H
