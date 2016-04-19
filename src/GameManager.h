#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include <vector>
#include <SDL_mixer.h>

#include "Window.h"
#include "Entity.h"
#include "Ball.h"
#include "Mods.h"

enum GameState
{
    STATE_MENU = 0,
    STATE_PLAYING = 1,
    STATE_HOWTOPLAY = 2,
    STATE_CREDITS = 3
};

class GameManager
{
    public:
        GameManager(Window* window);

        void runGame();
        void quit() { _quit = true; }
        void setState(int state);
        void initGame();

        Window* getWindow() { return window; }
		void addEntity(Entity* e);

    private:
        Window* window;
        SDL_Event event;

        Ball* ball;
        Entity* paddle;
        Mods* mod;
        Mix_Music* music;

        int randNum;
        int downNum;
        int upNum;

        bool isPressed = false;
		int currentLevel;

        // runs ~60 times per second
        // this is where most of the game happens
        void gameTick();

        bool _quit;

        int currentState;

        std::vector<Entity*> entities;
};

#endif
