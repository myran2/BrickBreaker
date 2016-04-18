#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include <vector>
#include "Window.h"
#include "Entity.h"
#include "Ball.h"
#include "Mods.h"

enum GameState
{
    STATE_MENU = 0,
    STATE_PLAYING,
    STATE_SETTINGS
};

class GameManager
{
    public:
        GameManager(Window* window);

        void runGame();
        void quit() { _quit = true; }
        void setState(int state) { currentState = state; }

        Window* getWindow() { return window; }

    private:
        Window* window;
        SDL_Event event;

        Ball* ball;
        Mods* powerup;
        Mods* powerdown;
        int randNum;

        // runs ~60 times per second
        // this is where most of the game happens
        void gameTick();

        bool _quit;

        int currentState;

        std::vector<Entity*> entities;
};

#endif
