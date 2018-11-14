#include "button.h"

#include <iostream>

Button::Button(string id, string txt, int act, int x, int y, SDL_Surface* src, int xMax)
{
    this->id = id;
    this->txt = txt;
    this->act = act;
    this->x = x;
    this->y = y;
    this->src = src;
    this->xMax = xMax;

    this->srcBorder = ObjSDL::loadBmp("./assets/Arkanoid_blackWhite.bmp");
}

void Button::setText(string txt)
{
    this->txt = txt;
}

string Button::getId()
{
    return id;
}

int Button::getIdAction()
{
    return act;
}

bool Button::in(int xMouse, int yMouse)
{
    return (Util::between(xMouse, x, x + (txt.size() * 16)) && Util::between(yMouse, y, y + 32));
}

void Button::draw(SDL_Surface* target)
{
    int xPos = x;

    for(auto c: txt)
    {
        int ascii = (int)c;

        int xAscii = ((ascii - 32) % 16) * 32;
        int yAscii = floor((ascii - 32) / 16) * 32;

        SDL_Rect letter = ObjSDL::createRect(xAscii, yAscii, 16, 32);
        SDL_Rect position = ObjSDL::createRect(xPos, y, 0, 0);

        ObjSDL::blitSurface(src, &letter, target, &position);

        xPos += 16;
    }
}

void Button::drawBorder(SDL_Surface* target)
{
    SDL_Rect source = ObjSDL::createRect(32, 0, 8, 8);
    SDL_Rect position = ObjSDL::createRect(0, 0, 0, 0);

    for(int i = x - 16; i < x + (txt.size() + 1) * 16; i += 8)
    {
        position.x = i;

        position.y = y - 16;
        ObjSDL::blitSurface(srcBorder, &source, target, &position);

        position.y = y + 40;
        ObjSDL::blitSurface(srcBorder, &source, target, &position);

    }

    for(int i = y - 16; i < y + 40; i += 8)
    {
        position.y = i;

        position.x = x - 16;
        ObjSDL::blitSurface(srcBorder, &source, target, &position);

        position.x = x + txt.size() * 16 + 8;
        ObjSDL::blitSurface(srcBorder, &source, target, &position);

    }
}
