#include "ball.h"

Ball::Ball()
{

}

Ball::Ball(int xPos, int yPos, SDL_Surface* srcSprite, SDL_Surface* srcShadow)
{
    this->xSrcSprite = 80;
    this->ySrcSprite = 66;
    this->xSrcShadow = 32;
    this->ySrcShadow = 0;
    this->xPos = xPos;
    this->yPos = yPos;
    this->srcSprite = srcSprite;
    this->srcShadow = srcShadow;
}

int Ball::getXSpeed()
{
    return xSpeed;
}

int Ball::getYSpeed()
{
    return ySpeed;
}

void Ball::setSpeed(int x, int y)
{
    xSpeed = x;
    ySpeed = y;
}

void Ball::setXSpeed(int x)
{
    xSpeed = x;
}

void Ball::setYSpeed(int y)
{
    ySpeed = y;
}

int Ball::getXPos()
{
    return xPos;
}

int Ball::getYPos()
{
    return yPos;
}

void Ball::setPos(int x, int y)
{
    xPos = x;
    yPos = y;
}

bool Ball::getXReverse()
{
    return xReverse;
}

bool Ball::getYReverse()
{
    return yReverse;
}
void Ball::setXReverse(bool xRev)
{
    xReverse = xRev;
}

void Ball::setYReverse(bool yRev)
{
    yReverse = yRev;
}

void Ball::move(bool slow)
{
    if(xReverse)
        xSpeed *= -1;

    if(yReverse)
        ySpeed *= -1;

    if(slow)
    {
        xPos += xSpeed/2;
        yPos += ySpeed/2;
    }
    else
    {
        xPos += xSpeed;
        yPos += ySpeed;
    }

    xReverse = false;
    yReverse = false;
}

void Ball::draw(SDL_Surface *target)
{
    SDL_Rect source = {xSrcSprite, ySrcSprite, 16, 16};
    SDL_Rect position = {xPos, yPos, 0, 0};

    ObjSDL::blitSurface(srcSprite, &source, target, &position);
}

void Ball::drawShadow(SDL_Surface *target)
{
    SDL_Rect source = {xSrcShadow, ySrcShadow, 16, 16};
    SDL_Rect position = {xPos + 12, yPos + 12, 0, 0};

    ObjSDL::blitSurface(srcShadow, &source, target, &position);
}
