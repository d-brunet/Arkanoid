#include "picture.h"

Picture::Picture(int xPos, int yPos, int xSrc, int ySrc, int w, int h, SDL_Surface* src)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->xSrc = xSrc;
    this->ySrc = ySrc;
    this->w = w;
    this->h = h;
    this->src = src;
}

void Picture::draw(SDL_Surface *target)
{
    SDL_Rect source = ObjSDL::createRect(xSrc, ySrc, w, h);
    SDL_Rect position = ObjSDL::createRect(xPos, yPos, 0, 0);

    ObjSDL::blitSurface(src, &source, target, &position);
}
