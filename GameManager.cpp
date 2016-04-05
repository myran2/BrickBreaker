#include "GameManager.h"
#include <iostream>

GameManager::GameManager(Window* window):
    window(window)
{

}

void GameManager::go()
{
    bool quit = false;

    Entity* paddle = new Entity(window, "paddle.bmp", 0, 0);
    paddle->setMoveRate(6);
    entities.push_back(paddle);

    Ball* ball = new Ball(window, "ball.bmp", window->getWidth() / 2, window->getHeight() / 2);
    entities.push_back(ball);
    
    while (!quit)
    {
        // 15ms is an arbitrary value. Increasing the value will make the loop execute less often.
        SDL_Delay(15);
        SDL_PollEvent(&event);

        switch (event.type)
        {
            // if user clicks the red X
        case SDL_QUIT:
            quit = true;
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
                paddle->remove();
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
            e->update();
        std::cout << std::endl;

        window->render();
    }
}