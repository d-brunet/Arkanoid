#include "enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(int id, int xPos, int yPos, SDL_Surface *srcSprite, SDL_Surface *srcShadow)
{
    this->id = id;
    this->xPos = xPos;
    this->yPos = yPos;
    this->srcSprite = srcSprite;
    this->srcShadow = srcShadow;

    this->xSrcSprite = 0;
    this->xSrcShadow = 0;
    this->ySrcShadow = 32;
    this->xSrcDestroy = 0;
    this->ySrcDestroy = 384;
    this->toLeft = rand()%20 >= 10;
    this->nbFrameDestroy = 6;

    this->xSpeed = 0;
    this->ySpeed = 2;

    this->life = 1;

    this->point = 120;

    switch (id) {
        case 0:
            this->ySrcSprite = 256;
            this->nbFrameSprite = 8;
        break;

        case 1:
            this->ySrcSprite = 288;
            this->nbFrameSprite = 11;
        break;

        case 2:
            this->ySrcSprite = 320;
            this->nbFrameSprite = 24;
        break;
    }

    this->count = 0;
}

int Enemy::getXPos()
{
    return xPos;
}

int Enemy::getYPos()
{
    return yPos;
}

void Enemy::setXSpeed(int x)
{
    xSpeed = x;
}

void Enemy::setYSpeed(int y)
{
    ySpeed = y;
}

int Enemy::getLife()
{
    return life;
}

void Enemy::setLife(int l)
{
    life = l;

    if(life == 0)
        count = 0;
}

bool Enemy::getToLeft()
{
    return toLeft;
}

void Enemy::setToLeft(bool l)
{
    toLeft = l;
}

void Enemy::move()
{
    xPos += xSpeed;
    yPos += ySpeed;
}

int Enemy::getPoint()
{
    return point;
}

void Enemy::draw(SDL_Surface *target)
{
    count++;

    SDL_Rect position = ObjSDL::createRect(xPos, yPos, 0, 0);
    SDL_Rect source;

    if(life > 0)
    {
        count = count % (nbFrameSprite * 5);

        xCurrentFrame = xSrcSprite + (int)floor(count / 5) * 32;

        if(xCurrentFrame >= 512)
        {
            xCurrentFrame = xCurrentFrame % 512;
            yCurrentFrame = ySrcSprite + 32;
        }
        else
            yCurrentFrame = ySrcSprite;


        source = ObjSDL::createRect(xCurrentFrame, yCurrentFrame, 32, 32);
    }
    else
    {
        count = count % (nbFrameDestroy * 5);

        xCurrentFrame = xSrcDestroy + (int)floor(count / 5) * 32;

        source = ObjSDL::createRect(xCurrentFrame, ySrcDestroy, 32, 32);
    }

    ObjSDL::blitSurface(srcSprite, &source, target, &position);
}

void Enemy::drawShadow(SDL_Surface *target)
{
    SDL_Rect source = ObjSDL::createRect(xSrcShadow, ySrcShadow, 32, 32);
    SDL_Rect position = ObjSDL::createRect(xPos + 12, yPos + 12, 0, 0);

    ObjSDL::blitSurface(srcShadow, &source, target, &position);
}
