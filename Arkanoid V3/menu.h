#ifndef MENU_H
#define MENU_H

#include <SDL.h>

#include "iobjgraph.h"

#include "button.h"
#include "libelle.h"
#include "picture.h"

#include <vector>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

class Menu : public IObjGraph
{
public:
    Menu(string id);

    string getId();
    vector<Button>* getButtonList();

    void addButton(Button btn);
    void addLibelle(Libelle lib);
    void addPicture(Picture pic);

    void setButtonText(string id, string txt);
    void setLibelleText(string id, string txt);

    void draw(SDL_Surface* target);

private:
    string id;

    vector<Button> buttonList;
    vector<Libelle> libelleList;
    vector<Picture> pictureList;
};

#endif // MENU_H
