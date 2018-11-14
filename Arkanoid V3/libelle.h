#ifndef LIBELLE_H
#define LIBELLE_H

#include "iobjgraph.h"

#include "objsdl.h"
#include "util.h"

#include <SDL.h>
#include <sstream>

using namespace std;

class Libelle : public IObjGraph
{
public:
    Libelle(string id, string text, int x, int y, SDL_Surface* src, int xMax);

    void setText(string txt);

    string getId();

    void draw(SDL_Surface* target) override;

private:
    string id;
    string txt;

    int x;
    int y;

    int xMax;

    SDL_Surface* src;
};

#endif // LIBELLE_H
