#ifndef IOBJGRAPH_H
#define IOBJGRAPH_H

#include <SDL.h>

class IObjGraph
{
public:
    virtual void draw(SDL_Surface* target) {}
    virtual void drawShadow(SDL_Surface* target) {}
};

#endif // IOBJGRAPH_H
