#include <iostream>
#include "GameManager.h"
#include "Log.h"
#include "Timer.h"

GameManager::GameManager(Window* window):
    window(window)
{

}

void GameManager::go()
{
    bool quit = false;

    Entity* paddle = new Entity(window, "paddle.bmp", 305, 400);
    paddle->setMoveRate(5);
    entities.push_back(paddle);

    Ball* ball = new Ball(window, "ball.bmp", window->getWidth() / 2, window->getHeight() / 2);
    Timer fpsTimer;
    Timer capTimer;

    uint32_t frameCount = 0;
    fpsTimer.start();

    //ball->setOnPaddle();

    while (!quit)
    {
        capTimer.start();

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
                        ball->remove();
                        ball = new Ball(window, "ball.bmp", window->getWidth() / 2, window->getHeight() / 2);
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


        // TODO: add FPS counter to screen (only in debug mode?)
        // divide the amount of frames displayed by the runtime in seconds to get the average fps
        /*float avgFps = frameCount / (fpsTimer.getTicks() / 1000.f);
        if (avgFps > 2000000)
            avgFps = 0;*/

        window->clear();

        for (Entity* e : entities)
        {
            // don't think this is that cpu intensive but I guess it could be
            if (ball->collidedWith(e))
                ball->handleCollision(e);

            e->update();
        }

        ball->update();

        window->render();

        frameCount++;

        // if our fps it too high, wait here until we're back to ~60fps
        if (capTimer.getTicks() < (1000 / window->getMaxFps()))
            SDL_Delay((1000 / window->getMaxFps()) - capTimer.getTicks());
    }
}
