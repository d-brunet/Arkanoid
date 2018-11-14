#include "game.h"

Game::Game()
{

}

void Game::init(string name, int w, int h)
{
    pWindow = ObjSDL::createWindow(name, w, h);

    winSurface = ObjSDL::getSurfaceWindow(pWindow);
    asciiSurface = ObjSDL::loadBmp("./assets/Arkanoid_ascii.bmp");
    spriteSurface = ObjSDL::loadBmp("./assets/Arkanoid_sprites.bmp");
    effectSurface = ObjSDL::loadBmp("./assets/Arkanoid_ef.bmp");
    logoSurface = ObjSDL::loadBmp("./assets/Arkanoid_logo.bmp");

    ObjSDL::setColorKey(spriteSurface, true, ObjSDL::mapRGB(spriteSurface->format, 0, 0, 0));
    ObjSDL::setColorKey(effectSurface, true, ObjSDL::mapRGB(effectSurface->format, 28, 173, 0));

    wGameboard = winSurface->w - 448;
    hGameboard = 16 * 25;

    cylindric = false;
    enemies = true;
	bonus = true;

    roundWaitFrame = 0;

    getNbLevel();

    initMenu();

    idActiveMenu = "startMenu";
}

void Game::initMenu()
{
    Menu mainMenu = Menu("startMenu");
    mainMenu.addButton(Button("btn_start_game", "START GAME", 1, winSurface->w/2 - 80, winSurface->h/2 + 16, asciiSurface, winSurface->w));
    mainMenu.addButton(Button("btn_option_game", "OPTIONS", 2, winSurface->w/2 - 56, winSurface->h/2 + 80, asciiSurface, winSurface->w));
    mainMenu.addButton(Button("btn_command", "COMMAND", 12, winSurface->w/2 - 56, winSurface->h/2 + 144, asciiSurface, winSurface->w));
    mainMenu.addButton(Button("btn_quit_game", "QUIT", 3, winSurface->w/2 - 32, winSurface->h/2 + 208, asciiSurface, winSurface->w));

    mainMenu.addPicture(Picture(winSurface->w/2 - 256, 64, 0, 0, 512, 112, logoSurface));

    menuList.push_back(mainMenu);

    Menu optionMenu = Menu("optionMenu");
    optionMenu.addLibelle(Libelle("txt_option", "OPTIONS", winSurface->w/2 - 56, 16, asciiSurface, winSurface->w));
    optionMenu.addButton(Button("btn_remove_horizontal", "-", 4, winSurface->w - 64, 144, asciiSurface, winSurface->w));
    optionMenu.addButton(Button("btn_add_horizontal", "+", 5, winSurface->w - 144, 144, asciiSurface, winSurface->w));
    optionMenu.addButton(Button("btn_remove_vertical", "-", 6, winSurface->w - 64, 208, asciiSurface, winSurface->w));
    optionMenu.addButton(Button("btn_add_vertical", "+", 7, winSurface->w - 144, 208, asciiSurface, winSurface->w));
    optionMenu.addButton(Button("btn_cylindric_option", "FALSE", 8, winSurface->w - 144, 272, asciiSurface, winSurface->w));
    optionMenu.addButton(Button("btn_enemy_option", "TRUE", 9, winSurface->w - 144, 336, asciiSurface, winSurface->w));
    optionMenu.addButton(Button("btn_bonus_option", "TRUE", 13, winSurface->w - 144, 400, asciiSurface, winSurface->w));
    optionMenu.addButton(Button("btn_start_menu", "START MENU", 10, winSurface->w/2 - 80, 464, asciiSurface, winSurface->w));

    optionMenu.addLibelle(Libelle("txt_horizontal_size", "HORIZONTAL SIZE", 64, 144, asciiSurface, winSurface->w));
    optionMenu.addLibelle(Libelle("txt_horizontal_size_nb", to_string(wGameboard/32), winSurface->w - 112, 144, asciiSurface, winSurface->w));
    optionMenu.addLibelle(Libelle("txt_vertical_size", "VERTICAL SIZE", 64, 208, asciiSurface, winSurface->w));
    optionMenu.addLibelle(Libelle("txt_vertical_size_nb", to_string(hGameboard/16),  winSurface->w - 112, 208, asciiSurface, winSurface->w));
    optionMenu.addLibelle(Libelle("txt_cylindric", "CYLINDRIC GAMEBOARD", 64, 272, asciiSurface, winSurface->w));
    optionMenu.addLibelle(Libelle("txt_enemies", "ENEMIES", 64, 336, asciiSurface, winSurface->w));
    optionMenu.addLibelle(Libelle("txt_bonus", "BONUS", 64, 400, asciiSurface, winSurface->w));

    menuList.push_back(optionMenu);

    Menu roundMenu = Menu("roundMenu");
    roundMenu.addLibelle(Libelle("txt_round_menu", "ROUND " + to_string(0), winSurface->w/2 - 44, winSurface->h/2 - 16, asciiSurface, winSurface->w));

    menuList.push_back(roundMenu);

    Menu pauseMenu = Menu("pauseMenu");
    pauseMenu.addButton(Button("btn_resume", "RESUME", 11, winSurface->w/2 - 48, 336, asciiSurface, winSurface->w));
    pauseMenu.addButton(Button("btn_start_menu_pause", "START MENU", 10, winSurface->w/2 - 80, 400, asciiSurface, winSurface->w));

    pauseMenu.addLibelle(Libelle("txt_pause", "PAUSE", winSurface->w/2 - 40, 16, asciiSurface, winSurface->w));

    menuList.push_back(pauseMenu);

    Menu commandMenu = Menu("commandMenu");
    commandMenu.addButton(Button("btn_start_menu_command", "START MENU", 10, winSurface->w/2 - 80, 400, asciiSurface, winSurface->w));

    commandMenu.addLibelle(Libelle("txt_command", "COMMAND", winSurface->w/2 - 56, 16, asciiSurface, winSurface->w));
    commandMenu.addLibelle(Libelle("txt_command_space", "SPACE", 64, 144, asciiSurface, winSurface->w));
    commandMenu.addLibelle(Libelle("txt_command_space_def", "Lauch ball/Fire bullet", 224, 144, asciiSurface, winSurface->w));
    commandMenu.addLibelle(Libelle("txt_command_mouse", "MOUSE", 64, 208, asciiSurface, winSurface->w));
    commandMenu.addLibelle(Libelle("txt_command_mouse_def", "Move vault", 224, 208, asciiSurface, winSurface->w));
    commandMenu.addLibelle(Libelle("txt_command_escape", "ESCAPE", 64, 272, asciiSurface, winSurface->w));
    commandMenu.addLibelle(Libelle("txt_command_escape_def", "Pause menu/Previous menu/Quit game (on main menu)", 224, 272, asciiSurface, winSurface->w));

    menuList.push_back(commandMenu);

    Menu gameOverMenu = Menu("gameOverMenu");
    gameOverMenu.addButton(Button("btn_start_menu_game_over", "START MENU", 10, winSurface->w/2 - 80, 400, asciiSurface, winSurface->w));

    gameOverMenu.addLibelle(Libelle("txt_game_over", "GAME OVER", winSurface->w/2 - 40, 16, asciiSurface, winSurface->w));

    menuList.push_back(gameOverMenu);

    Menu finishMenu = Menu("finishMenu");
    finishMenu.addButton(Button("btn_start_menu_win", "START MENU!", 10, winSurface->w/2 - 80, 400, asciiSurface, winSurface->w));

    finishMenu.addLibelle(Libelle("txt_congratulation", "CONGRATULATION!", winSurface->w/2 - 120, 16, asciiSurface, winSurface->w));
    finishMenu.addLibelle(Libelle("txt_finish_the_game", "YOU FINISH THE GAME!", winSurface->w/2 - 160, 16, asciiSurface, winSurface->w));

    menuList.push_back(finishMenu);

    //interface
    hudLibelleList.push_back(Libelle("txt_high", "HIGH", 16, 16, asciiSurface, 224));
    hudLibelleList.push_back(Libelle("txt_score", "SCORE", 48, 48, asciiSurface, 224));
    hudLibelleList.push_back(Libelle("txt_high_score_level", to_string(5000), 16, 80, asciiSurface, 224));
    hudLibelleList.push_back(Libelle("txt_1up", "1UP", 16, 144, asciiSurface, 224));
    hudLibelleList.push_back(Libelle("txt_high_score_player", to_string(0), 16, 176, asciiSurface, 224));
    hudLibelleList.push_back(Libelle("txt_life", "LIFE", 16, 240, asciiSurface, 224));
    hudLibelleList.push_back(Libelle("txt_life_nb", to_string(0), 16, 276, asciiSurface, 224));
    hudLibelleList.push_back(Libelle("txt_round_num", "", 16, winSurface->h - 48 , asciiSurface, 224));
}

//---------------------------
//  vault
//---------------------------

void Game::initVault()
{
    vault = Vault(224 + (wGameboard/2) - 32, winSurface->h - 32, 64, &xVault, spriteSurface, effectSurface);
    xVault = 224 + (wGameboard/2) - 32;
    xVault = 224 + (wGameboard/2) - 32;
}

//---------------------------
//  bonus
//---------------------------

void Game::generateBonus()
{
    int nbBonusMax = rand()%5 + 5;
    int idBrick;
    int idBonus;

    vector<int> idBrickWithBonus;

    int i = 0;

    while(i < nbBonusMax)
    {
        idBrick = rand() % brickList.size();

        if(find(idBrickWithBonus.begin(), idBrickWithBonus.end(), idBrick) == idBrickWithBonus.end())
        {
            idBonus = rand() % 7;

            brickList[idBrick].setBonus(Bonus(idBonus, brickList[idBrick].getXPos(), brickList[idBrick].getYPos(), spriteSurface, effectSurface));

            idBrickWithBonus.push_back(idBrick);
            i++;
        }
    }
}

//---------------------------
//  level
//---------------------------

void Game::getNbLevel()
{
    int token;

    ifstream nbLevel("./levels/config.txt");

    if(nbLevel)
    {
        while(nbLevel >> token)
        {
            nbMaxLevel = token;
        }
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier: ./levels/config.txt" << endl;
        idActiveMenu = "startMenu";
    }
}

void Game::loadLevel(int i)
{
    ifstream level("./levels/level_" + to_string(i) + ".txt");

    if(level)
    {
        int token;
        int i = 0;

        while(level >> token)
        {
            if(token != -1)
            {
                int yPos = (int)floor((i * 32) / wGameboard + 5) * 16;

                if(yPos >= 80 && yPos < 80 + hGameboard)
                {
                    brickList.push_back(Brick(token, currentLevel, 224 + (i * 32) % wGameboard, yPos, spriteSurface, effectSurface));

                    if(token < 13)
                        nbBreakableBrick++;
                }
            }
            i++;
        }

        level.close();

		if(bonus)
            generateBonus();
    }
    else
    {
        cerr << "Impossible d'ouvrir le fichier: level_" << to_string(i) << ".txt" << endl;
        idActiveMenu = "startMenu";
    }
}

void Game::initLevel(int i)
{
    if(i > nbMaxLevel)
    {
        idActiveMenu = "finishMenu";
    }
    else
    {
        // general
        currentLevel = i;

        resetBonus();

        launch = false;

        highScore = 5000;
        extraLife = false;

        goNextLevel = false;

        // vault
        vault.setScore(0);

        vault.setWidth(64);
        vault.setSrcSprite(384, 128);

        vault.setXPos(224 + wGameboard/2 - 32);

        ballList.clear();
        brickList.clear();
        bonusList.clear();
        enemyList.clear();

        // ball
        Ball ballTmp = Ball(xVault + 24,  winSurface->h - 44, spriteSurface, effectSurface);
        ballTmp.setSpeed(8,8);
        ballList.push_back(ballTmp);

        xBallStickVault = vault.getWidth()/2 - 8;

        // brick
        nbBreakableBrick = 0;

        // enemy
        if(enemies)
        {
            enemySpawnLeft = rand()%20 >= 10;
            enemySpawnCooldown = 250;
        }

        // background
        int idBackground = (i - 1) % 6;

        if(idBackground == 0)
            background = {idBackground * 64, 128 + ((int)floor((i - 1) / 6) % 2) * 64, 48, 64};
        else
            background = {idBackground * 64, 128 + ((int)floor((i - 1) / 6) % 2) * 64, 64, 64};

        loadLevel(i);

        // transition menu
        getMenuById("roundMenu")->setLibelleText("txt_round_menu", "ROUND " + to_string(i));

        for(int j = 0; j < hudLibelleList.size(); j++)
        {
            if(hudLibelleList[j].getId() == "txt_round_num")
                hudLibelleList[j].setText("ROUND " + to_string(i));
        }

        idActiveMenu = "roundMenu";
        roundWaitFrame = 100;
    }
}

//---------------------------
//  menu
//---------------------------

Menu* Game::getMenuById(string id)
{
    for(int i = 0; i < menuList.size(); i++)
    {
        if(menuList[i].getId() == id)
        {
            return &menuList[i];
        }
    }
}

void Game::drawMenu(string id)
{
    SDL_Rect black = {0,0,32,32};
    SDL_Rect position = {0,0,0,0};

    for(int i = 0; i < winSurface->w; i += 32)
    {
        for(int j = 0; j < winSurface->h; j += 32)
        {
            position.x = i;
            position.y = j;
            ObjSDL::blitSurface(asciiSurface, &black, winSurface, &position);
        }
    }
    getMenuById(id)->draw(winSurface);

    //mouse hover button

    Menu* m = getMenuById(id);

    vector<Button>* buttonList = m->getButtonList();

    int xMouse, yMouse;

    ObjSDL::getMouseState(&xMouse, &yMouse);

    for(int i = 0; i < buttonList->size(); i++)
    {
        if(buttonList->at(i).in(xMouse, yMouse))
        {
            buttonList->at(i).drawBorder(winSurface);

        }
    }
}

void Game::checkClick(int x, int y)
{
    Menu* m = getMenuById(idActiveMenu);

    vector<Button>* buttonList = m->getButtonList();

    for(int i = 0; i < buttonList->size(); i++)
    {
        if(buttonList->at(i).in(x, y))
            actionButton(&buttonList->at(i));
    }
}

void Game::actionButton(Button* btn)
{
    int action = btn->getIdAction();

    switch (action) {
    case 1: //Start game
        currentLevel = 1;
        initLevel(currentLevel);
        break;
    case 2: //draw menu Option
        idActiveMenu = "optionMenu";
        break;

    case 3: //quit game
        quit = true;
        break;

    case 4: //remove row
        if(wGameboard > winSurface->w - 448)
        {
            wGameboard -= 32;
            getMenuById("optionMenu")->setLibelleText("txt_horizontal_size_nb", to_string(wGameboard/32));
        }
        break;

    case 5: //add row
        if(wGameboard < winSurface->w - 224)
        {
            wGameboard += 32;
            getMenuById("optionMenu")->setLibelleText("txt_horizontal_size_nb", to_string(wGameboard/32));
        }
        break;

    case 6: //remove line
        if(hGameboard > 16 * 25)
        {
            hGameboard -= 16;
            getMenuById("optionMenu")->setLibelleText("txt_vertical_size_nb", to_string(hGameboard/16));
        }
        break;

    case 7: //add line
        if(hGameboard < 16 * 35)
        {
            hGameboard += 16;
            getMenuById("optionMenu")->setLibelleText("txt_vertical_size_nb", to_string(hGameboard/16));
        }
        break;

    case 8: //toggle cylindric
        cylindric = !cylindric;
        if(cylindric)
            getMenuById("optionMenu")->setButtonText("btn_cylindric_option", "TRUE");
        else
            getMenuById("optionMenu")->setButtonText("btn_cylindric_option", "FALSE");
        break;

    case 9: //toggle enemies
        enemies = !enemies;
        if(enemies)
            getMenuById("optionMenu")->setButtonText("btn_enemy_option", "TRUE");
        else
            getMenuById("optionMenu")->setButtonText("btn_enemy_option", "FALSE");
        break;

    case 10: //start menu
        idActiveMenu = "startMenu";
        break;

    case 11: //resume game
        idActiveMenu = "";
        break;

    case 12: //command menu
        idActiveMenu = "commandMenu";
        break;

    case 13: //toggle bonus
        bonus = !bonus;
        if(bonus)
            getMenuById("optionMenu")->setButtonText("btn_bonus_option", "TRUE");
        else
            getMenuById("optionMenu")->setButtonText("btn_bonus_option", "FALSE");
        break;

    default:
        break;
    }
}

//---------------------------
//  draw object
//---------------------------

void Game::drawSprite(IObjGraph* obj)
{
    obj->draw(winSurface);
}

//---------------------------
//  draw shadow
//---------------------------

void Game::drawShadow(IObjGraph* obj)
{
    obj->drawShadow(winSurface);
}

//---------------------------
//  interface
//---------------------------

void Game::drawInterface()
{
    SDL_Rect black = {0,0,32,32};
    SDL_Rect position = {0,0,0,0};

    for(int j = 0; j < winSurface->h; j += 32)
    {
        for(int i = 0; i < 224; i += 32)
        {
                position.x = i;
                position.y = j;
                ObjSDL::blitSurface(asciiSurface, &black, winSurface, &position);
        }

        for(int i = 224 + wGameboard; i < winSurface->w; i += 32)
        {
                position.x = i;
                position.y = j;
                ObjSDL::blitSurface(asciiSurface, &black, winSurface, &position);
        }
    }

    for(int i = 0; i < hudLibelleList.size(); i++)
    {
        if(hudLibelleList[i].getId() == "txt_high_score_player")
            hudLibelleList[i].setText(to_string(vault.getScore()));
        else if(hudLibelleList[i].getId() == "txt_life_nb")
            hudLibelleList[i].setText(to_string(vault.getLife()));

        drawSprite(&hudLibelleList[i]);
    }

}

//---------------------------
//  background
//---------------------------

void Game::drawBackground()
{
    SDL_Rect position = ObjSDL::createRect(0, 0, 0, 0);

    for(int i = 224; i < wGameboard + 224; i += background.w)
    {
        for(int j = 0; j < winSurface->h; j += background.h)
        {
            position.x = i;
            position.y = j;
            ObjSDL::blitSurface(spriteSurface, &background, winSurface, &position);
        }
    }
}

//---------------------------
//  game calcul
//---------------------------

void Game::activeBonus(int id)
{
    switch (id) {
        case 0:
            slow = true;
        break;

        case 1:
            sticky = true;
        break;

        case 2:
            fire = true;
            vault.setFire(true);
        break;

        case 3:
            vault.setBig(true);
        break;

        case 4:
        {
            int xPos = ballList[0].getXPos();
            int yPos = ballList[0].getYPos();
            int xSpeed = ballList[0].getXSpeed();

            Ball ball = Ball(xPos, yPos, spriteSurface, effectSurface);

            ball.setSpeed(xSpeed + 2, 8);
            ballList.push_back(ball);

            ball.setSpeed(xSpeed - 2, 8);
            ballList.push_back(ball);
        }
        break;

        case 5:
            goNextLevel = true;
        break;

        case 6:
            vault.setLife(vault.getLife() + 1);
        break;
    }
}

void Game::resetBonus()
{
    slow = false;
    sticky = false;
    fire = false;
    launch = true;

    fireCooldown = 0;

    int i = 0;

    while(ballList.size() > 1)
    {
        i++;
        ballList.erase(ballList.begin() + i);
    }

    vault.setBig(false);
    vault.setFire(false);
}

void Game::gameCalcul()
{
    drawBackground();
    drawInterface();

    if(fireCooldown > 0)
        fireCooldown--;

    vault.updatePos();

    vector<int> eraseIndexRocket;

    for(int i = rocketList.size() - 1; i > -1; i--)
    {
        Rocket* rocketTmp = &rocketList[i];

        rocketTmp->move();

        if(rocketTmp->getYPos() <= 0)
            rocketList.erase(rocketList.begin() + i);
        else
        {
            for(int j = brickList.size() - 1; j > -1; j--)
            {
                Brick* brickTmp = &brickList[j];

                if(brickTmp->getLife() > 0)
                {
                    if(((rocketTmp->getYPos() > brickTmp->getYPos() && rocketTmp->getYPos() < brickTmp->getYPos() + 16)
                    || (rocketTmp->getYPos() + 16 > brickTmp->getYPos() && rocketTmp->getYPos() + 16 < brickTmp->getYPos() + 16))
                    && ((rocketTmp->getXPos() + 4 > brickTmp->getXPos() && rocketTmp->getXPos() + 4 < brickTmp->getXPos() + 32)
                    || (rocketTmp->getXPos() + 28 > brickTmp->getXPos() && rocketTmp->getXPos() + 28 < brickTmp->getXPos() + 32)))
                    {
                        brickTmp->setLife(brickTmp->getLife() - 1);

                        if(find(eraseIndexRocket.begin(), eraseIndexRocket.end(), i) == eraseIndexRocket.end())
                            eraseIndexRocket.push_back(i);
                    }
                }
            }
        }
    }

    for(int i = bonusList.size() - 1; i > -1; i--)
    {
        Bonus* bonusTmp = &bonusList[i];

        bonusTmp->move();

        if(bonusTmp->getYPos() >= winSurface->h)
            bonusList.erase(bonusList.begin() + i);
        else if((Util::between(bonusTmp->getXPos(), xVault, xVault + vault.getWidth()) || Util::between(bonusTmp->getXPos() + 32, xVault, xVault + vault.getWidth()))
                && bonusTmp->getYPos() + 16 >= winSurface->h - 44 + 16 && bonusTmp->getYPos() + 16 <= winSurface->h - 44 + 32)
        {
            resetBonus();
            activeBonus(bonusTmp->getId());

            bonusList.erase(bonusList.begin() + i);
        }
    }

    //calcul collision
    for(int i = ballList.size() - 1; i > -1; i--)
    {
        Ball* ballTmp = &ballList[i];

        if(!launch)
            ballTmp->setPos(xBallStickVault + xVault, winSurface->h - 44);
        else
            ballTmp->move(slow);

        if((Util::between(ballTmp->getXPos(), xVault, xVault + vault.getWidth()) || Util::between(ballTmp->getXPos() + 16, xVault, xVault + vault.getWidth()))
        && ballTmp->getYPos() + 16 >= winSurface->h - 44 + 16 && ballTmp->getYPos() + 16 <= winSurface->h - 44 + 32)
        {
            if(sticky)
                launch = false;

            xBallStickVault = ballTmp->getXPos() - xVault;

            if(ballTmp->getYSpeed() > 0)
                ballTmp->setYReverse(true);

            int xSpeed = (ballTmp->getXPos() + 8 - (vault.getXPos() + vault.getWidth()/2)) * 15 / vault.getWidth();

            if(xSpeed > 8)
                xSpeed = 8;
            else if(xSpeed < -8)
                xSpeed = -8;

            ballTmp->setXSpeed(xSpeed);
        }



        for(int i = brickList.size() - 1; i > -1; i--)
        {
            Brick* brickTmp = &brickList[i];

            if(brickTmp->getLife() > 0)
            {
                //right/left
                if(((ballTmp->getXPos() > brickTmp->getXPos() && ballTmp->getXPos() < brickTmp->getXPos() + 32)
                    || (ballTmp->getXPos() + 16 > brickTmp->getXPos() && ballTmp->getXPos() + 16 < brickTmp->getXPos() + 32))
                    && Util::between(ballTmp->getYPos() + 8, brickTmp->getYPos(), brickTmp->getYPos() + 16))
                {
                    ballTmp->setXReverse(true);
                    brickTmp->setLife(brickTmp->getLife() - 1);
                }

                //top/bottom
                if(((ballTmp->getYPos() > brickTmp->getYPos() && ballTmp->getYPos() < brickTmp->getYPos() + 16)
                    || (ballTmp->getYPos() + 16 > brickTmp->getYPos() && ballTmp->getYPos() + 16 < brickTmp->getYPos() + 16))
                    && Util::between(ballTmp->getXPos() + 8, brickTmp->getXPos(), brickTmp->getXPos() + 32))
                {
                    ballTmp->setYReverse(true);
                    brickTmp->setLife(brickTmp->getLife() - 1);
                }

                //corner
                if((Util::between(ballTmp->getXPos(), brickTmp->getXPos(), brickTmp->getXPos() + 32) && Util::between(ballTmp->getYPos(), brickTmp->getYPos(), brickTmp->getYPos() + 16) && !Util::between(ballTmp->getXPos() + 8, brickTmp->getXPos(), brickTmp->getXPos() + 32) && !Util::between(ballTmp->getYPos() + 8, brickTmp->getYPos(), brickTmp->getYPos() + 16))
                || (Util::between(ballTmp->getXPos() + 16, brickTmp->getXPos(), brickTmp->getXPos() + 32) && Util::between(ballTmp->getYPos(), brickTmp->getYPos(), brickTmp->getYPos() + 16) && !Util::between(ballTmp->getXPos() + 8, brickTmp->getXPos(), brickTmp->getXPos() + 32) && !Util::between(ballTmp->getYPos() + 8, brickTmp->getYPos(), brickTmp->getYPos() + 16))
                || (Util::between(ballTmp->getXPos(), brickTmp->getXPos(), brickTmp->getXPos() + 32) && Util::between(ballTmp->getYPos() + 16, brickTmp->getYPos(), brickTmp->getYPos() + 16) && !Util::between(ballTmp->getXPos() + 8, brickTmp->getXPos(), brickTmp->getXPos() + 32) && !Util::between(ballTmp->getYPos() + 8, brickTmp->getYPos(), brickTmp->getYPos() + 16))
                || (Util::between(ballTmp->getXPos() + 16, brickTmp->getXPos(), brickTmp->getXPos() + 32) && Util::between(ballTmp->getYPos() + 16, brickTmp->getYPos(), brickTmp->getYPos() + 16) && !Util::between(ballTmp->getXPos() + 8, brickTmp->getXPos(), brickTmp->getXPos() + 32) && !Util::between(ballTmp->getYPos() + 8, brickTmp->getYPos(), brickTmp->getYPos() + 16)))
                {
                    if((ballTmp->getXPos() <= brickTmp->getXPos() && ballTmp->getXSpeed() > 0) || (ballTmp->getXPos() >= brickTmp->getXPos() && ballTmp->getXSpeed() < 0))
                        ballTmp->setXReverse(true);

                    if((ballTmp->getYPos() <= brickTmp->getYPos() && ballTmp->getYSpeed() > 0) || (ballTmp->getYPos() >= brickTmp->getYPos() && ballTmp->getYSpeed() < 0))
                        ballTmp->setYReverse(true);

                    brickTmp->setLife(brickTmp->getLife() - 1);
                }

            }
            else
            {
                if(brickTmp->getLife() == -3)
                {
                    if(brickTmp->haveBonus())
                        bonusList.push_back(brickTmp->getBonus());

                    vault.setScore(vault.getScore() + brickTmp->getPoint());

                    if(vault.getScore() > highScore && !extraLife)
                    {
                        vault.setLife(vault.getLife() + 1);
                        extraLife = true;
                    }

                    brickList.erase(brickList.begin() + i);

                    nbBreakableBrick--;
                }
            }
        }

        if(ballTmp->getXPos() < 224)
            if(cylindric)
                ballTmp->setPos(224 + wGameboard - 16, ballTmp->getYPos());
            else
                ballTmp->setXReverse(true);
        else if(ballTmp->getXPos() + 16 > 224 + wGameboard)
            if(cylindric)
                ballTmp->setPos(224, ballTmp->getYPos());
            else
                ballTmp->setXReverse(true);

        if(ballTmp->getYPos() < 0)
            ballTmp->setYReverse(true);
        else if(ballTmp->getYPos() > winSurface->h)
        {
            if(ballList.size() <= 1)
            {
                if(vault.getLife() > 0)
                {
                    resetBonus();
                    launch = false;
                    xBallStickVault = vault.getWidth()/2 - 8;
                    vault.setLife(vault.getLife() - 1);

                    enemyList.clear();
                    bonusList.clear();
                }
                else
                {
                    idActiveMenu = "gameOverMenu";
                }
            }
            else
                ballList.erase(ballList.begin() + i);
        }
    }


    for(int i = enemyList.size() - 1; i > -1; i--)
    {
        Enemy* enemyTmp = &enemyList[i];

        if(enemyTmp->getLife() > 0)
        {
            bool down = true;
            bool left = true;
            bool right = true;

            for(int i = brickList.size() - 1; i > -1; i--)
            {
                Brick* brickTmp = &brickList[i];

                if(Util::between(enemyTmp->getYPos() + 32, brickTmp->getYPos(), brickTmp->getYPos() + 16) && (Util::between(enemyTmp->getXPos() + 2, brickTmp->getXPos(), brickTmp->getXPos() + 32) || Util::between(enemyTmp->getXPos() + 30, brickTmp->getXPos(), brickTmp->getXPos() + 32)))
                    down = false;
                if((Util::between(enemyTmp->getXPos() + 32, brickTmp->getXPos(), brickTmp->getXPos() + 32) && Util::between(brickTmp->getYPos(), enemyTmp->getYPos(), enemyTmp->getYPos() + 30)) || enemyTmp->getXPos() + 32 >= 224 + wGameboard)
                {
                    if(!enemyTmp->getToLeft())
                        enemyTmp->setToLeft(true);
                    right = false;
                }
                if((Util::between(enemyTmp->getXPos(), brickTmp->getXPos(), brickTmp->getXPos() + 32) && Util::between(brickTmp->getYPos(), enemyTmp->getYPos(), enemyTmp->getYPos() + 30)) || enemyTmp->getXPos() <= 224)
                {
                    if(enemyTmp->getToLeft())
                        enemyTmp->setToLeft(false);
                    left = false;
                }
            }

            if(down)
            {
                enemyTmp->setXSpeed(0);
                enemyTmp->setYSpeed(2);
                enemyTmp->move();
            }
            else if(right && !enemyTmp->getToLeft())
            {
                enemyTmp->setXSpeed(2);
                enemyTmp->setYSpeed(0);
                enemyTmp->move();
            }
            else if(left && enemyTmp)
            {
                enemyTmp->setXSpeed(-2);
                enemyTmp->setYSpeed(0);
                enemyTmp->move();
            }

            for(int j = ballList.size() - 1; j > -1; j--)
            {
                Ball* ballTmp = &ballList[j];

                if((Util::between(ballTmp->getXPos(), enemyTmp->getXPos() + 2, enemyTmp->getXPos() + 30) || Util::between(ballTmp->getXPos() + 16, enemyTmp->getXPos() + 2, enemyTmp->getXPos() + 30))
                && (Util::between(ballTmp->getYPos(), enemyTmp->getYPos() + 2, enemyTmp->getYPos() + 30) || Util::between(ballTmp->getYPos() + 16, enemyTmp->getYPos() + 2, enemyTmp->getYPos() + 30)))
                {
                    enemyTmp->setLife(enemyTmp->getLife() - 1);

                    vault.setScore(vault.getScore() + enemyTmp->getPoint());

                    if(vault.getScore() > highScore && !extraLife)
                    {
                        vault.setLife(vault.getLife() + 1);
                        extraLife = true;
                    }

                }
            }

            for(int j = rocketList.size() - 1; j > -1; j--)
            {
                Rocket* rocketTmp = &rocketList[j];

                if((Util::between(rocketTmp->getXPos() + 4, enemyTmp->getXPos() + 2, enemyTmp->getXPos() + 30) || Util::between(rocketTmp->getXPos() + 24, enemyTmp->getXPos() + 2, enemyTmp->getXPos() + 30))
                && Util::between(rocketTmp->getYPos(), enemyTmp->getYPos() + 2, enemyTmp->getYPos() + 30))
                {
                    enemyTmp->setLife(enemyTmp->getLife() - 1);

                    vault.setScore(vault.getScore() + enemyTmp->getPoint());

                    if(vault.getScore() > highScore && !extraLife)
                    {
                        vault.setLife(vault.getLife() + 1);
                        extraLife = true;
                    }

                    if(find(eraseIndexRocket.begin(), eraseIndexRocket.end(), i) == eraseIndexRocket.end())
                        eraseIndexRocket.push_back(i);

                }
            }

            if((Util::between(enemyTmp->getXPos(), xVault, xVault + vault.getWidth()) || Util::between(enemyTmp->getXPos() + 32, xVault, xVault + vault.getWidth()))
            && enemyTmp->getYPos() + 32 >= winSurface->h - 44 + 16 && enemyTmp->getYPos() + 32 <= winSurface->h - 44 + 32)
            {
                if(vault.getLife() > 0)
                {
                    resetBonus();
                    launch = false;
                    xBallStickVault = vault.getWidth()/2 - 8;
                    vault.setLife(vault.getLife() - 1);

                    enemyList.clear();
                    bonusList.clear();
                }
                else
                {
                    idActiveMenu = "gameOverMenu";
                }
            }
        }
        else
        {
            enemyTmp->setLife(enemyTmp->getLife() - 1);

            if(enemyTmp->getLife() < -28)
                enemyList.erase(enemyList.begin() + i);
        }

        if(enemyTmp->getYPos() > winSurface->h)
            enemyList.erase(enemyList.begin() + i);
    }

    //erase rocket
    for(int i : eraseIndexRocket)
        rocketList.erase(rocketList.begin() + i);

    // draw shadow

    for(int i = 0; i < rocketList.size(); i++)
    {
        drawShadow(&rocketList[i]);
    }

    for(int i = 0; i < bonusList.size(); i++)
    {
        drawShadow(&bonusList[i]);
    }

    for(int i = 0; i < ballList.size(); i++)
    {
        drawShadow(&ballList[i]);
    }

    for(int i = 0; i < brickList.size(); i++)
    {
        drawShadow(&brickList[i]);
    }

    for(int i = 0; i < enemyList.size(); i++)
    {
        drawShadow(&enemyList[i]);
    }

    drawShadow(&vault);

    // draw sprite
    for(int i = 0; i < rocketList.size(); i++)
    {
        drawSprite(&rocketList[i]);
    }

    for(int i = 0; i < bonusList.size(); i++)
    {
        drawSprite(&bonusList[i]);
    }

    for(int i = 0; i < ballList.size(); i++)
    {
        drawSprite(&ballList[i]);
    }

    for(int i = 0; i < brickList.size(); i++)
    {
        drawSprite(&brickList[i]);
    }

    for(int i = 0; i < enemyList.size(); i++)
    {
        drawSprite(&enemyList[i]);
    }

    drawSprite(&vault);

    //spawn ennemy
    if(enemies)// enemy option activate
    {
        if(enemySpawnCooldown == 0)
        {
            int xSpawn;

            if(enemySpawnLeft)
                xSpawn = 320; //224 + 3 * 32
            else
                xSpawn = 224 + wGameboard - 96; //224 + wGameboard - 3 * 32

            enemyList.push_back(Enemy(currentLevel % 3, xSpawn, -32, spriteSurface, effectSurface));

            enemySpawnLeft = !enemySpawnLeft;
            enemySpawnCooldown = 250;
        }
        else
            enemySpawnCooldown--;
    }

    // finish level
    if(nbBreakableBrick == 0 || goNextLevel)
    {
        goNextLevel = false;
        initLevel(currentLevel + 1);
    }
}

void Game::loop()
{
    quit = false;
    initVault();


    while(!quit)
    {
        SDL_Event event;
        while(!quit && ObjSDL::pollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        if(idActiveMenu == "")
                            idActiveMenu = "pauseMenu";
                        else if(idActiveMenu == "optionMenu" || idActiveMenu == "gameOverMenu")
                            idActiveMenu = "startMenu";
                        else if(idActiveMenu == "pauseMenu")
                            idActiveMenu = "";
                        else if(idActiveMenu == "startMenu")
                            quit = true;
                        break;

                    case SDLK_SPACE:
                    if(idActiveMenu == "")
                    {
                        if(!launch)
                            launch = true;
                        else if(fire && fireCooldown == 0)
                        {
                            fireCooldown = 15;
                            rocketList.push_back(Rocket(xVault + vault.getWidth() / 2 - 16, winSurface->h - 44, spriteSurface, effectSurface));
                        }
                    }
                }
                break;

            case SDL_MOUSEMOTION:
                if(idActiveMenu == "")
                    xVault += event.motion.xrel;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(idActiveMenu != "")
                {
                    int xMouse, yMouse;

                    ObjSDL::getMouseState(&xMouse, &yMouse);
                    checkClick(xMouse, yMouse);
                }
                break;
            }
        }

        if(idActiveMenu != "")
        {
            ObjSDL::setRelativeMouse(false);

            drawMenu(idActiveMenu);

            if(idActiveMenu == "roundMenu")
            {
                if(roundWaitFrame == 0)
                    idActiveMenu = "";
                else
                    roundWaitFrame--;
            }
        }
        else
        {
            ObjSDL::setRelativeMouse(true);

            if(xVault < 224)
                xVault = 224;
            else if(xVault > 224 + wGameboard - vault.getWidth())
                xVault = 224 + wGameboard - vault.getWidth();

            gameCalcul();
        }

        ObjSDL::updateWindowSurface(pWindow);
        ObjSDL::delay(20);
    }
    ObjSDL::quit();
}
