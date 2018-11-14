#include "objsdl.h"

using namespace std;

ObjSDL::ObjSDL()
{

}

SDL_Rect ObjSDL::createRect(int x, int y, int w, int h)
{
    SDL_Rect sprite = {x, y, w, h};
    return sprite;
}

SDL_Window* ObjSDL::createWindow(string title, int w, int h)
{
    return SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
}

SDL_Surface* ObjSDL::getSurfaceWindow(SDL_Window* win)
{
    return SDL_GetWindowSurface(win);
}

SDL_Surface* ObjSDL::loadBmp(string path)
{
    return SDL_LoadBMP(path.c_str());
}

Uint32 ObjSDL::mapRGB(SDL_PixelFormat *fmt, int r, int g, int b)
{
    return SDL_MapRGB(fmt, r, g, b);
}

void ObjSDL::blitSurface(SDL_Surface *imgSource, SDL_Rect *sprite, SDL_Surface *window, SDL_Rect *position)
{
    SDL_BlitSurface(imgSource, sprite, window, position);
}

void ObjSDL::setColorKey(SDL_Surface* img, bool invisible, int color)
{
    SDL_SetColorKey(img, invisible, color);
}

void ObjSDL::getMouseState(int *x, int *y)
{
    SDL_GetMouseState(x, y);
}

void ObjSDL::setRelativeMouse(bool free)
{
    if(free)
        SDL_SetRelativeMouseMode(SDL_TRUE);
    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}

void ObjSDL::updateWindowSurface(SDL_Window* win)
{
    SDL_UpdateWindowSurface(win);
}

void ObjSDL::delay(int time)
{
    SDL_Delay(time);
}

void ObjSDL::quit()
{
    SDL_Quit();
}

bool ObjSDL::pollEvent(SDL_Event *event)
{
    return SDL_PollEvent(event);
}
