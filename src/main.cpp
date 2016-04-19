#include <iostream>
#include "Log.h"
#include "GameManager.h"
#include "Window.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
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
    Window window("Brick Breaker", SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_MAX_FPS);
    GameManager manager(&window);

    // Actual game loop
    manager.runGame();

    // Cleaning up the window
    window.cleanupAndExit();
    
    return 0;
}
