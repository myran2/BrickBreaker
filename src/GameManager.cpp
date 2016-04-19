#include <iostream>
#include <time.h>
#include <array>
#include "Brick.h"
#include "GameManager.h"
#include "Log.h"
#include "Menu.h"
#include "Timer.h"
#include "levelLoader.h"

GameManager::GameManager(Window* window):
    window(window)
{
    currentState = STATE_MENU;
    _quit = false;
    srand(time(NULL));
    music = NULL;

    paddle = new Entity(window, "paddle.bmp", 305, 490);
    entities.push_back(paddle);

    currentLevel = 2;
}

void GameManager::initGame()
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    std::string resPath = "res";
    std::string filePath = "";
    filePath = resPath + PATH_SEP + "backgroundmusic.wav";

    music = Mix_LoadMUS(filePath.c_str());

    if(!music)
        printf("Mix_LoadMUS(\"backgroundmusic.wav\"): %s\n", Mix_GetError());

    Mix_PlayMusic(music, -1);

    paddle->setMoveRate(8);
    paddle->setTexture("paddle.bmp");
    paddle->setX(305);
    paddle->setY(490);
    paddle->stopMoving(MOVE_LEFT);
    paddle->stopMoving(MOVE_RIGHT);


    ball = new Ball(window, "ball.png", window->getWidth() / 2, window->getHeight() / 2, paddle);
    ball->setOnPaddle(true);

    //used for random powerup spwaning
    randNum = rand() % 4;
    mod = new Mods(window, "PowerUP.bmp", 305, 0 );//makes a new power down object

    upNum = rand() % 2;
    downNum = rand() % 2;

    LevelLoader* loader = new LevelLoader(this);
    switch (currentLevel)
    {
        case 1:
            loader->openMap("lvl1.txt");
            break;
        case 2:
            loader->openMap("lvl2.txt");
            break;
        default:
            Log::error("Tried to open unknown level: " + std::to_string(currentLevel));
            break;
    }
}

void GameManager::runGame()
{
    Menu mainMenu(this);
    mainMenu.addEntry("Play");
    mainMenu.addEntry("How to Play");
    mainMenu.addEntry("Credits");
    mainMenu.addEntry("Exit");

    Timer fpsTimer;
    Timer capTimer;

    uint32_t frameCount = 0;
    fpsTimer.start();

    while (!_quit)
    {
        window->clear();

        capTimer.start();

        switch (currentState)
        {
        case STATE_MENU:
        {
            SDL_Texture* bgTexture = window->loadTexture("bg.bmp");
            window->renderTexture(bgTexture, 0, 0);
            mainMenu.tick();
            break;
        }
        case STATE_HOWTOPLAY:
        {
            SDL_Texture* htpTexture = window->loadTexture("HowToPlay.bmp");
            window->renderTexture(htpTexture, 0, 0);
            listenForQuit();
            break;
        }
        case STATE_CREDITS:
        {
            SDL_Texture* bgTexture = window->loadTexture("bg.bmp");
            window->renderTexture(bgTexture, 0, 0);
            printCredits();
            listenForQuit();
            break;
        }
        case STATE_PLAYING:
            gameTick();
            break;

        default:
            Log::warn("Recieved unhandled gamestate: " + std::to_string(currentState));
            break;
        }

        // divide the amount of frames displayed by the runtime in seconds to get the average fps
        float avgFps = frameCount / (fpsTimer.getTicks() / 1000.f);
        if (avgFps > 2000000)
            avgFps = 0;

        window->renderText(std::to_string((int)avgFps), window->getWidth()-30, 0, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED, { 0, 0, 0 });

        window->render();

        frameCount++;

        // if our fps it too high, wait here until we're back to ~60fps
        if (capTimer.getTicks() < (1000 / window->getMaxFps()))
        {
            int waitTime = (1000 / window->getMaxFps()) - capTimer.getTicks();
            SDL_Delay(waitTime);
        }
    }
}

void GameManager::gameTick()
{
    bool repeatKey = SDL_PollEvent(&event) == 1;

    if(ball->getLives() < 1)
    {
        window->renderCenteredText("GAME OVER", window->getHeight()/4, {0,0,0}, 50, FONT_RENDER_BLENDED, {255,255,255});
        window->renderCenteredText("Score: ", window->getHeight()/2, {0,0,0}, 50, FONT_RENDER_BLENDED, {255,255,255});
        switch (event.type)
        {
        // if user clicks the red X
        case SDL_QUIT:
            _quit = true;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            case SDLK_SPACE:
                setState(STATE_MENU);
                break;
            }
            break;
        }
        return;
    }

    switch (event.type)
    {
    // if user clicks the red X
    case SDL_QUIT:
        _quit = true;
        break;

    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            paddle->startMoving(MOVE_LEFT);
            break;
        case SDLK_RIGHT:
            paddle->startMoving(MOVE_RIGHT);
            break;
        case SDLK_SPACE:
            if (ball->isOnPaddle())
                ball->detach();
            isPressed = true;
            break;
        case SDLK_ESCAPE:
            if (repeatKey)
            {
                setState(STATE_MENU);
                return;
            }
        }
        break;

    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            paddle->stopMoving(MOVE_LEFT);
            break;
        case SDLK_RIGHT:
            paddle->stopMoving(MOVE_RIGHT);
            break;
        }
        break;
    }

    for (Entity* e : entities)
    {
        // don't think this is that cpu intensive but I guess it could be
        if (ball->collidedWith(e))
        {
            ball->handleCollision(e);
            if (e->getTypeId() == TYPEID_BRICK)
                ((Brick*)e)->dealDamage(1);
        }

        e->update();
    }

    /************** Code segment used for powerup implementation ***************/
    if(randNum == 0 && isPressed == true)
    {
        mod->update();
        if(mod->collidedWith(paddle))
        {
            mod->fastPaddle();
            paddle->setMoveRate(7);
            mod->remove();
        }
    }

    if(randNum == 1 && isPressed == true)
    {
        mod->update();
        if(mod->collidedWith(paddle))
        {
            paddle->setTexture("paddle_big.bmp");
            mod->largePaddle();
            mod->remove();
        }
    }

    if(randNum == 2 && isPressed == true)
    {
        mod->update();
            if(mod->collidedWith(paddle))
            {
                mod->slowerPaddle();
                paddle->setMoveRate(3);
                mod->remove();
            }
    }

    if(randNum == 3 && isPressed == true)
    {
        mod->update();
        if(mod->collidedWith(paddle))
        {
            paddle->setTexture("paddle_small.bmp");
            mod->smallPaddle();
            mod->remove();
        }
    }
    /***************************************************************************/

    ball->update();
    window->renderText("Lives: " + std::to_string(ball->getLives()), 0, 0, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED, { 0, 0, 0 });
}

void GameManager::addEntity(Entity* e)
{
	entities.push_back(e);
}

void GameManager::setState(int state)
{
    Log::info("Set state to " + std::to_string(state));
    currentState = state;
}

void GameManager::printCredits()
{
    window->renderCenteredText("Henry Gordon", 20, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED, { 0, 0, 0 });
    window->renderCenteredText("Anthony Brugal", 50, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED, { 0, 0, 0 });
    window->renderCenteredText("Iden Sessani", 80, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED, { 0, 0, 0 });
    window->renderCenteredText("Erik Higginbotham", 110, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED, { 0, 0, 0 });
    window->renderCenteredText("Aaron Hanuschak", 140, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED, { 0, 0, 0 });
    window->renderCenteredText("Kurt Weber", 170, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED, { 0, 0, 0 });
}

void GameManager::listenForQuit()
{
    SDL_Event currEvent;
    bool repeatKey = SDL_PollEvent(&currEvent) == 1;
    
    switch (currEvent.type)
    {
    // if user clicks the red X
    case SDL_QUIT:
        _quit = true;
        return;
    case SDL_KEYDOWN:
        if (repeatKey)
        {
            switch (currEvent.key.keysym.sym)
            {
            case SDLK_SPACE:
            case SDLK_RETURN:
            case SDLK_ESCAPE:
                setState(STATE_MENU);
            }
        }
    }
}
