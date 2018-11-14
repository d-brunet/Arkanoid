#ifndef PICTURE_H
#define PICTURE_H

#include "iobjgraph.h"

#include "objsdl.h"

class Picture : public IObjGraph
{
public:
    Picture(int xPos, int yPos, int xSrc, int ySrc, int w, int h, SDL_Surface* src);

    void draw(SDL_Surface* target);

private:
    int xPos;
    int yPos;
    int xSrc;
    int ySrc;
    int w;
    int h;

    SDL_Surface* src;
};

#endif // PICTURE_H
