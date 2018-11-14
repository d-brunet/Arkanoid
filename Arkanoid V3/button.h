#ifndef BUTTON_H
#define BUTTON_H

#include "iobjgraph.h"

#include "objsdl.h"
#include "util.h"

#include <SDL.h>

using namespace std;

class Button : public IObjGraph
{
public:
    Button(string id, string text, int action, int x, int y, SDL_Surface* src, int xMax);

    void setText(string txt);

    string getId();

    int getIdAction();

    bool in(int xMouse, int yMouse);

    void draw(SDL_Surface* target);
    void drawBorder(SDL_Surface* target);

private:
    string id;
    string txt;

    int act;
    int x;
    int y;

    int xMax;

    SDL_Surface* src;
    SDL_Surface* srcBorder;
};

#endif // BUTTON_H
