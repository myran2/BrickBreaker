#include <iostream>
#include <time.h>
#include <array>
#include "GameManager.h"
#include "Log.h"
#include "Timer.h"


GameManager::GameManager(Window* window):
    window(window)
{
    currentState = STATE_PLAYING;
    _quit = false;
}

void GameManager::runGame()
{
    Entity* paddle = new Entity(window, "paddle.bmp", 305, 400);
    paddle->setMoveRate(5);
    entities.push_back(paddle);

    ball = new Ball(window, "ball.bmp", window->getWidth() / 2, window->getHeight() / 2, paddle);
    ball->setOnPaddle(true);

    srand(time(NULL));
    randNum = rand() % 2;
    if(randNum == 0)
      powerup = new Mods(window, "PowerUP.bmp", 305, 0 );	// makes a new power up object
    else if(randNum == 1)
  	  powerdown = new Mods(window, "PowerDown.bmp", 305, 0 );//makes a new power down object

    Timer fpsTimer;
    Timer capTimer;

    uint32_t frameCount = 0;
    fpsTimer.start();

    while (!_quit)
    {
        SDL_PollEvent(&event);

        window->clear();

        capTimer.start();

        switch (currentState)
        {
        case STATE_MENU:
            menuTick();
            break;
        case STATE_SETTINGS:
            break;
        case STATE_PLAYING:
            gameTick();
            break;
        default:
            Log::error("Recieved unhandled gamestate: " + std::to_string(currentState));
            break;
        }

        // divide the amount of frames displayed by the runtime in seconds to get the average fps
        float avgFps = frameCount / (fpsTimer.getTicks() / 1000.f);
        if (avgFps > 2000000)
            avgFps = 0;

        window->renderText(std::to_string((int)avgFps), 0, 0, { 0, 0, 0 }, 25, FONT_RENDER_BLENDED);

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

void GameManager::menuTick()
{
    switch (event.type)
    {
    // if user clicks the red X
    case SDL_QUIT:
        _quit = true;
        return;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_SPACE:
        case SDLK_KP_ENTER:
            // Play, go to settings, or close the game
            break;
        case SDLK_UP:
            // switch to the above menu option
            break;
        case SDLK_DOWN:
            // switch to the below menu option
            break;
        }
        break;
    case SDL_MOUSEMOTION:
        int mouseX = event.motion.x;
        int mouseY = event.motion.y;
        break;
    }

    std::array<std::string, 3> menuOptions = { "Play", "Settings", "Exit" };
    int xPos = 200;
    int yPos = 100;
    for (std::string option : menuOptions)
    {
        window->renderText(option, xPos, yPos, { 0, 0, 0 }, 50, FONT_RENDER_BLENDED);
        yPos += 100;
    }
}

void GameManager::gameTick()
{
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

        e->update();
    }

    ball->update();

    if(randNum == 0)
      powerup->update();
    else if(randNum == 1)
      powerdown->update();

}
