#include <iostream>
#include "Log.h"
#include "GameManager.h"
#include "Window.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char ** argv)
{
    // TODO: remove hardcoded logfile
    if (!Log::init("Game.log", false))
    {
        std::cout << "Couldn't open Game.log!";
        exit(1);
    }

    Window window("Brick Breaker", SCREEN_WIDTH, SCREEN_HEIGHT);

    GameManager manager(&window);
    
    // Actual game loop
    manager.go();

    window.cleanupAndExit();
    return 0;
}
