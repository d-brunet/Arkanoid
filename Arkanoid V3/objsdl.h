#ifndef OBJSDL_H
#define OBJSDL_H

#include <SDL.h>

#include <string>

#include <unistd.h>
#include <stdlib.h>

using namespace std;

class ObjSDL
{
public:
    ObjSDL();

    static SDL_Rect createRect(int x, int y, int w, int h);

    static SDL_Window* createWindow(string title, int w, int h);

    static SDL_Surface* getSurfaceWindow(SDL_Window* win);
    static SDL_Surface* loadBmp(string path);

    static Uint32 mapRGB(SDL_PixelFormat *fmt, int r, int g, int b);

    static void blitSurface(SDL_Surface* imgSource, SDL_Rect* sprite, SDL_Surface* window, SDL_Rect* position);
    static void setColorKey(SDL_Surface* img, bool invisible, int color);

    static void getMouseState(int* x, int* y);
    static void setRelativeMouse(bool free);

    static void updateWindowSurface(SDL_Window* win);
    static void delay(int time);
    static void quit();

    static bool pollEvent(SDL_Event* event);
};

#endif // OBJSDL_H
