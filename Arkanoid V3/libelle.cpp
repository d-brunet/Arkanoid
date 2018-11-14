#include "libelle.h"

Libelle::Libelle(string id, string txt, int x, int y, SDL_Surface* src, int xMax)
{
    this->id = id;
    this->txt = txt;
    this->x = x;
    this->y = y;
    this->src = src;
    this->xMax = xMax;
}

void Libelle::setText(string txt)
{
    this->txt = txt;
}

string Libelle::getId()
{
    return id;
}

void Libelle::draw(SDL_Surface* target)
{
    int xPos = x;
    int yPos = y;

    string s;
    istringstream f(txt);

    while(getline(f, s, ' '))
    {
        s += " ";
        if(xPos + s.size() * 16 > xMax - 32)
        {
            yPos += 32;
            xPos = x;
        }
        for(auto c: s)
        {
            int ascii = (int)c;

            int xAscii = ((ascii - 32) % 16) * 32;
            int yAscii = floor((ascii - 32) / 16) * 32;

            SDL_Rect letter = ObjSDL::createRect(xAscii, yAscii, 16, 32);
            SDL_Rect position = ObjSDL::createRect(xPos, yPos, 0, 0);

            ObjSDL::blitSurface(src, &letter, target, &position);

            xPos += 16;
        }
    }
}
