#include "rocket.h"

Rocket::Rocket()
{

}

Rocket::Rocket(int xPos, int yPos, SDL_Surface* srcSprite, SDL_Surface* srcShadow)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->srcSprite = srcSprite;
    this->srcShadow = srcShadow;

    this->xSrcSprite = 0;
    this->ySrcSprite = 80;
    this->xSrcShadow = 32;
    this->ySrcShadow = 32;
}

int Rocket::getXPos()
{
    return xPos;
}

int Rocket::getYPos()
{
    return yPos;
}

void Rocket::move()
{
    yPos -= 16;
}

void Rocket::draw(SDL_Surface *target)
{
    SDL_Rect source = ObjSDL::createRect(xSrcSprite, ySrcSprite, 32, 32);
    SDL_Rect position = ObjSDL::createRect(xPos, yPos, 0, 0);

    ObjSDL::blitSurface(srcSprite, &source, target, &position);
}

void Rocket::drawShadow(SDL_Surface *target)
{
    SDL_Rect source = ObjSDL::createRect(xSrcShadow, ySrcShadow, 16, 32);
    SDL_Rect position = ObjSDL::createRect(xPos + 12, yPos + 12, 0, 0);

    ObjSDL::blitSurface(srcShadow, &source, target, &position);

    position.x = xPos + 20; //12 + 8
    ObjSDL::blitSurface(srcShadow, &source, target, &position);
}
