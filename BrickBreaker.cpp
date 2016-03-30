#include "Window.h"
#include <iostream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char ** argv)
{
    // variables
    int x = 288;
    int y = 288;

    Window window;
    window.init(SCREEN_WIDTH, SCREEN_HEIGHT);

    window.gameLoop();

    window.cleanupAndExit();
    return 0;
}