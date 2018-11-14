#include "brick.h"
#include <iostream>
Brick::Brick()
{

}

Brick::Brick(int id, int numLvl, int xPos, int yPos, SDL_Surface* srcSprite, SDL_Surface* srcShadow)
{
    this->id = id;
    this->xPos = xPos;
    this->yPos = yPos;
    this->srcSprite = srcSprite;
    this->srcShadow = srcShadow;

    this->xSrcShadow = 0;
    this->ySrcShadow = 0;
    this->xSrcDestroy = 0;
    this->ySrcDestroy = 16;

    if(id < 12)
    {
        this->xSrcSprite = (id * 32) % 192;
        this->ySrcSprite = floor((id * 32) / 192) * 16;
        this->life = 1;

        if(id == 0 || id == 1)
            this->point = 50;
        else if(id == 2 || id == 3)
            this->point = 60;
        else if(id == 4 || id == 5)
            this->point = 70;
        else if(id == 6 || id == 7)
            this->point = 80;
        else if(id == 8)
            this->point = 90;
        else if(id == 9)
            this->point = 100;
        else if(id == 10)
            this->point = 110;
        else if(id == 11)
            this->point = 120;

        this->nbFrameSprite = 1;
    }
    else if(id == 12)
    {
        this->xSrcSprite = 0;
        this->ySrcSprite = 32;

        if(numLvl <= 8)
            this->life = 2;
        else if(numLvl <=16)
            this->life = 3;
        else if(numLvl <=24)
            this->life = 4;
        else if(numLvl <=32)
            this->life = 5;

        this->point = 100 * numLvl;
        this->nbFrameSprite = 6;
    }
    else if(id == 13)
    {
        this->xSrcSprite = 0;
        this->ySrcSprite = 48;

        this->life = 1;

        this->nbFrameSprite = 6;
    }

    count = 0;
    wait = 0;

    containBonus = false;
}

int Brick::getId()
{
    return id;
}

int Brick::getLife()
{
    return life;
}

void Brick::setLife(int l)
{
    if(id != 13)
        life = l;
}

int Brick::getXPos()
{
    return xPos;
}

int Brick::getYPos()
{
    return yPos;
}

int Brick::getPoint()
{
    return point;
}

void Brick::setBonus(Bonus b)
{
    containBonus = true;
    bonus = b;
}

Bonus Brick::getBonus()
{
    return bonus;
}

bool Brick::haveBonus()
{
    return containBonus;
}

void Brick::draw(SDL_Surface *target)
{
    SDL_Rect source;
    SDL_Rect position = ObjSDL::createRect(xPos, yPos, 0, 0);

    if(id < 12)
        source = ObjSDL::createRect(xSrcSprite, ySrcSprite, 32, 16);
    else
    {
        if(wait <= 0)
        {
            count++;

            if(count == 30)
                wait = 100;

            count = count % (nbFrameSprite * 5);
        }
        else
            wait--;

        int xCurrentFrame = xSrcSprite + (int)floor(count / 5) * 32;

        source = ObjSDL::createRect(xCurrentFrame, ySrcSprite, 32, 16);
    }

    ObjSDL::blitSurface(srcSprite, &source, target, &position);

    if(life <= 0)
    {
        SDL_Rect destroy = ObjSDL::createRect(xSrcDestroy + (life * -1) * 32, ySrcDestroy, 32, 16);
        ObjSDL::blitSurface(srcShadow, &destroy, target, &position);

        life--;
    }
}

void Brick::drawShadow(SDL_Surface *target)
{
    SDL_Rect source = ObjSDL::createRect(xSrcShadow, ySrcShadow, 32, 16);
    SDL_Rect position = ObjSDL::createRect(xPos + 12, yPos + 12, 0, 0);

    ObjSDL::blitSurface(srcShadow, &source, target, &position);
}
