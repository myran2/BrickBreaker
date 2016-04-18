#include <iostream>
#include "Log.h"
#include "GameManager.h"
#include "Window.h"
#include "SDL_mixer.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 520
#define SCREEN_MAX_FPS 60

int main(int argc, char ** argv)  // start main
{
    // TODO: remove hardcoded logfile
    if (!Log::init("Game.log", false))
    {
        std::cout << "Couldn't open Game.log!";
        exit(1);
    }

    // Initialize the game 
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_Music *music = NULL;
    music = Mix_LoadMUS("backgroundmusic.wav");
    //music to play, -1(unlimited repeats)
    if(!music) {
        printf("Mix_LoadMUS(\"backgroundmusic.wav\"): %s\n", Mix_GetError());
    }
    Mix_PlayMusic(music, -1);
    Window window("Brick Breaker", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_MAX_FPS);

    GameManager manager(&window);

    // Actual game loop
    manager.runGame();

    // Cleaning up the window
    window.cleanupAndExit();
    
    return 0;
}                               // end main
