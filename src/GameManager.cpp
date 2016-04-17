#include <iostream>
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

    powerup = new Mods(window, "PowerUP.bmp", 305, 0 );	// makes a new power up object


    
    Timer fpsTimer;
    Timer capTimer;

    uint32_t frameCount = 0;
    fpsTimer.start();

    while (!_quit)
    {
		
        capTimer.start();
		
        switch (currentState)
        {
        case STATE_MENU:
            break;
        case STATE_SETTINGS:
            break;
        case STATE_PLAYING:
            gameTick();
            break;
        }

        window->render();

        frameCount++;
		
        // if our fps it too high, wait here until we're back to ~60fps
        if (capTimer.getTicks() < (1000 / window->getMaxFps()))
            SDL_Delay((1000 / window->getMaxFps()) - capTimer.getTicks());
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

    window->clear();

    for (Entity* e : entities)
    {
        // don't think this is that cpu intensive but I guess it could be
        if (ball->collidedWith(e))
            ball->handleCollision(e);

        e->update();
    }
    ball->update();
    powerup->update();

   
}
