#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "objsdl.h"
#include "util.h"

#include "iobjgraph.h"

#include "menu.h"
#include "button.h"
#include "libelle.h"
#include "picture.h"

#include "vault.h"
#include "ball.h"
#include "bonus.h"
#include "brick.h"
#include "rocket.h"
#include "enemy.h"

using namespace std;

class Game
{
public:
    Game();

    void init(string name, int w, int h);
    void loop();

    void executeAction(int idAction);

    void addBall();

    void addEnemy();

private:
    void initMenu();
    void initVault();

    void generateBonus();
    void getNbLevel();
    void loadLevel(int i);
    void initLevel(int i);

    Menu* getMenuById(string id);

    void drawMenu(string id);
    void drawShadow(IObjGraph* obj);
    void drawSprite(IObjGraph* obj);
    void drawInterface();
    void drawBackground();

    void resetGame();

    void activeBonus(int id);
    void resetBonus();

    void gameCalcul();

    void actionButton(Button* btn);

    void checkClick(int xMouse, int yMouse);

    SDL_Window* pWindow;

    SDL_Surface* winSurface;
    SDL_Surface* asciiSurface;
    SDL_Surface* spriteSurface;
    SDL_Surface* effectSurface;
    SDL_Surface* logoSurface;

    SDL_Rect background;

    vector<Menu> menuList;
    vector<Libelle> hudLibelleList;

    string idActiveMenu;

    int wGameboard;
    int hGameboard;

    bool cylindric;
    bool enemies;
    bool bonus;

    vector<Bonus> bonusList;
    vector<Brick> brickList;
    vector<Rocket> rocketList;
    vector<Enemy> enemyList;

    int nbBreakableBrick;

    Vault vault;
    int xVault;

    vector<Ball> ballList;
    int xBallStickVault;
    bool launch;

    //bonus
    bool sticky;
    bool fire;
    bool slow;

    int fireCooldown;

    int enemySpawnCooldown;
    bool enemySpawnLeft;

    int roundWaitFrame;

    int currentLevel;
    int nbMaxLevel;
    bool goNextLevel;

    int highScore;
    bool extraLife;

    bool quit;
};

#endif // GAME_H
