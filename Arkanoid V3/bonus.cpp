#include "bonus.h"

Bonus::Bonus()
{

}

Bonus::Bonus(int id, int xPos, int yPos, SDL_Surface* srcSprite, SDL_Surface* srcShadow)
{
    this->id = id;
    this->xSrcSprite = 256;
    this->ySrcSprite = id * 16;
    this->xSrcShadow = 0; // a remplacer par la vrai ombre
    this->ySrcShadow = 48; // a remplacer par la vrai ombre
    this->nbFrameSprite = 8;
    this->xPos = xPos;
    this->yPos = yPos;
    this->srcSprite = srcSprite;
    this->srcShadow = srcShadow;

    this->count = 0;
}

int Bonus::getId()
{
    return id;
}

int Bonus::getXPos()
{
    return xPos;
}

int Bonus::getYPos()
{
    return yPos;
}

void Bonus::setXPos(int x)
{
    xPos = x;
}

void Bonus::setYPos(int y)
{
    yPos = y;
}

void Bonus::move()
{
    yPos += 7;
}

void Bonus::draw(SDL_Surface *target)
{
    count++;
    count = count % (nbFrameSprite * 5);

    xCurrentFrame = xSrcSprite + (int)floor(count / 5) * 32;

    SDL_Rect source = ObjSDL::createRect(xCurrentFrame, ySrcSprite, 32, 16);
    SDL_Rect position = ObjSDL::createRect(xPos, yPos, 0, 0);

    ObjSDL::blitSurface(srcSprite, &source, target, &position);
}

void Bonus::drawShadow(SDL_Surface *target)
{
    SDL_Rect source = ObjSDL::createRect(xSrcShadow, ySrcShadow, 32, 16);
    SDL_Rect position = ObjSDL::createRect(xPos + 12, yPos + 12, 0, 0);

    ObjSDL::blitSurface(srcShadow, &source, target, &position);
}
