#include <iostream>
#include "Window.h"
#include "GameManager.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char ** argv)
{
    Window window("Brick Breaker", SCREEN_WIDTH, SCREEN_HEIGHT);

    GameManager manager(&window);
    manager.go();

    window.cleanupAndExit();
    return 0;
}
