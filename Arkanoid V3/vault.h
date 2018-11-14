#ifndef VAULT_H
#define VAULT_H

#include "iobjgraph.h"

#include "objsdl.h"

#include <SDL.h>

class Vault : public IObjGraph
{
public:
    Vault();
    Vault(int xPos, int yPos, int width, int* xVault, SDL_Surface* srcSprite, SDL_Surface* srcShadow);

    void setLife(int i);
    int getLife();

    void setScore(int s);
    int getScore();

    void setWidth(int w);
    int getWidth();

    void setXPos(int x);
    int getXPos();

    void updatePos();

    void setSrcSprite(int x, int y);

    void setActiveBonus(int i);
    int getActiveBonus();

    void setLastBonus(int i);
    int getLastBonus();

    void setBig(bool b);
    void setFire(bool f);

    void draw(SDL_Surface *target) override;
    void drawShadow(SDL_Surface *target) override;

private:
    SDL_Surface* srcSprite;
    SDL_Surface* srcShadow;

    int life;
    int score;

    int xSrcSprite;
    int ySrcSprite;
    int xSrcFireSprite;
    int ySrcFireSprite;
    int xSrcShadow;
    int ySrcShadow;
    int xPos;
    int yPos;

    bool big;
    bool fire;

    int width;
    int* xVault;
};

#endif // VAULT_H
