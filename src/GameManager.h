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
    STATE_WINNER = 2,
    STATE_HOWTOPLAY = 3,
    STATE_CREDITS = 4
};

class GameManager
{
    public:
        GameManager(Window* window);

        // start running the game, Tick functions are run inside this method
        void runGame();

        void quit() { _quit = true; }
        void setState(int state);

        // initializes the game
        // puts the paddle in the default state, re-attaches the ball, set up bricks, etc.
        // if 'fresh' is true, levels and score will be reset
        void initGame(bool fresh);

        Window* getWindow() { return window; }

        // adds the given entity to the GameManager entity vector
		void addEntity(Entity* e);

        // Check events and wait for the user to give some input
        // if the user presses the red X, close the program
        // if the user presses enter, space, or escape, go back to the main menu
        void listenForQuit();

        // really only used once. should this be a function?
        // renders this project's credits to the screen
        void printCredits();

    private:
        Window* window;
        SDL_Event event;

        Ball* ball;
        Entity* paddle;
        Mods* mod;
        Mix_Music* music;

        SDL_Texture* bgTexture;
        SDL_Texture* htpTexture;

        Mix_Chunk* ballHitSound = NULL;

        int randNum;
        int downNum;
        int upNum;

        bool isPressed = false;
		int currentLevel;

        int maxBricks;
        int bricksLeft;
        bool levelOver;

        // calculates the player's score
        int calcScore();

        // runs ~60 times per second
        // this is where most of the game happens
        void gameTick();

        bool _quit;

        // current Game state, see GameState enum for options
        int currentState;

        std::vector<Entity*> entities;
};

#endif
