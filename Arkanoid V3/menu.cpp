#include "menu.h"

Menu::Menu(string id)
{
    this->id = id;
}

string Menu::getId()
{
    return id;
}

vector<Button>* Menu::getButtonList()
{
    return &buttonList;
}

void Menu::addButton(Button btn)
{
    buttonList.push_back(btn);
}

void Menu::addLibelle(Libelle lib)
{
    libelleList.push_back(lib);
}

void Menu::addPicture(Picture pic)
{
    pictureList.push_back(pic);
}

void Menu::setButtonText(string id, string txt)
{
    for(int i = 0; i < buttonList.size(); i++)
    {
        if(id == buttonList[i].getId())
            buttonList[i].setText(txt);
    }
}

void Menu::setLibelleText(string id, string txt)
{
    for(int i = 0; i < libelleList.size(); i++)
    {
        if(id == libelleList[i].getId())
            libelleList[i].setText(txt);
    }
}

void Menu::draw(SDL_Surface* target)
{
    for(Button btn: buttonList)
    {
        btn.draw(target);
    }

    for(Libelle lib: libelleList)
    {
        lib.draw(target);
    }

    for(Picture pic: pictureList)
    {
        pic.draw(target);
    }
}
