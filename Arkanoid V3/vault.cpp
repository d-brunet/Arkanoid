#include "vault.h"

Vault::Vault()
{

}

Vault::Vault(int xPos, int yPos, int width, int* xVault, SDL_Surface* srcSprite, SDL_Surface* srcShadow)
{
    this->xSrcSprite = 384;
    this->ySrcSprite = 128;
    this->xSrcFireSprite = 0;
    this->ySrcFireSprite = 112;
    this->xSrcShadow = 0;
    this->ySrcShadow = 64;
    this->xPos = xPos;
    this->yPos = yPos;
    this->width = width;
    this->xVault = xVault;
    this->srcSprite = srcSprite;
    this->srcShadow = srcShadow;

    this->life = 2;
    this->big = false;
}

void Vault::setLife(int i)
{
    life = i;
}

int Vault::getLife()
{
    return life;
}

void Vault::setScore(int s)
{
    score = s;
}

int Vault::getScore()
{
    return score;
}

void Vault::setWidth(int w)
{
    width = w;
}

int Vault::getWidth()
{
    return width;
}

void Vault::setXPos(int x)
{
    xPos = x;
}

int Vault::getXPos()
{
    return xPos;
}

void Vault::updatePos()
{
    xPos = *xVault;
}

void Vault::setSrcSprite(int x, int y)
{
    xSrcSprite = x;
    ySrcSprite = y;
}

void Vault::setBig(bool b)
{
    big = b;
}

void Vault::setFire(bool f)
{
    fire = f;
}

void Vault::draw(SDL_Surface *target)
{
    if(big)
    {
        if(width < 134)
        {
            ySrcSprite += 16;
            width += 10;
            *xVault -= 5;
        }
    }
    else
    {
        if(width > 64)
        {
            ySrcSprite -= 16;
            width -= 10;
            *xVault += 5;
        }
    }

    SDL_Rect source = {xSrcSprite, ySrcSprite, width, 16};
    SDL_Rect position = {xPos, yPos, 0, 0};

    ObjSDL::blitSurface(srcSprite, &source, target, &position);

    if(fire && width == 64)
    {
        source = {xSrcFireSprite, ySrcFireSprite, 32, 8};
        position = {xPos + 16, yPos - 8, 0, 0};

        ObjSDL::blitSurface(srcSprite, &source, target, &position);
    }
}

void Vault::drawShadow(SDL_Surface *target)
{

    if(big)
    {
        if(width < 134)
            ySrcShadow += 16;
    }
    else
    {
        if(width > 64)
            ySrcShadow -= 16;
    }

    SDL_Rect source = {xSrcShadow, ySrcShadow, width, 16};
    SDL_Rect position = {xPos + 12, yPos + 12, 0, 0};

    ObjSDL::blitSurface(srcShadow, &source, target, &position);
}
