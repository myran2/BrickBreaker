#include <iostream>
#include <time.h>
#include <array>
#include "GameManager.h"
#include "Log.h"
#include "Menu.h"
#include "Timer.h"


GameManager::GameManager(Window* window):
    window(window)
{
    currentState = STATE_MENU;
    _quit = false;
}

void GameManager::runGame()
{
    Entity* paddle = new Entity(window, "paddle.bmp", 305, 490);
    paddle->setMoveRate(5);
    entities.push_back(paddle);

    ball = new Ball(window, "ball.bmp", window->getWidth() / 2, window->getHeight() / 2, paddle);
    ball->setOnPaddle(true);

    ball2 = new Ball(window, "ball.bmp", window->getWidth() / 2, window->getHeight() / 2, paddle);
    ball2->setOnPaddle(true);

    //used for random powerup spwaning
    srand(time(NULL));
    randNum = rand() % 2;
    if(randNum == 0)
      powerup = new Mods(window, "PowerUP.bmp", 305, 0 );	// makes a new power up object
    else if(randNum == 1)
  	  powerdown = new Mods(window, "PowerDown.bmp", 305, 0 );//makes a new power down object

    upNum = rand() % 2;
	downNum = rand() % 2;

    Timer fpsTimer;
    Timer capTimer;

    uint32_t frameCount = 0;
    fpsTimer.start();

    Menu mainMenu(this);
    mainMenu.addEntry("Play");
    mainMenu.addEntry("Settings");
    mainMenu.addEntry("Exit");

    Menu settingsMenu(this);
    settingsMenu.addEntry("Back");

    while (!_quit)
    {
        window->clear();

        capTimer.start();

        switch (currentState)
        {
        case STATE_MENU:
            mainMenu.tick();
            break;
        case STATE_SETTINGS:
            break;
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
            //Log::info("Waiting " + std::to_string(waitTime) + " MS");
            SDL_Delay(waitTime);
        }
    }
}

void GameManager::gameTick()
{
    SDL_PollEvent(&event);
    
    // paddle is always added to the entities vector first, so this is fine
    Entity* paddle = entities[0];

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
            break;
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
            ball->handleCollision(e);

        if(ball2->collidedWith(e))
            ball2->handleCollision(e);

        e->update();
    }

/************** Code segment used for powerup implementation ***************/
    if(randNum == 0)
    {
        powerup->update();
        if(upNum == 1)
        {
            if(powerup->collidedWith(paddle))
            {
              powerup->doubleBalls();
              ball2->detach();
              powerup->remove();
            }
            ball2->update();
            ball2->outOfBounds();
        }

        else if(upNum == 0)
        {
            if(powerup->collidedWith(paddle))
            {
                powerup->largePaddle();
                powerup->remove();
            }
        }
    }

    if(randNum == 1)
    {
        powerdown->update();
        if(downNum == 0)
        {
            if(powerdown->collidedWith(paddle))
            {
                powerdown->slowerPaddle();
                paddle->setMoveRate(3);
                powerdown->remove();
            }
        }
        else if(downNum == 1)
        {
            if(powerdown->collidedWith(paddle))
            {
                powerdown->smallPaddle();
                powerdown->remove();
            }
        }
    }
/***************************************************************************/

    ball->update();
}
