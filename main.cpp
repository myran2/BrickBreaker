#include <SDl2/SDL.h>
#include <iostream>

int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "Initialized SDL." << std::endl;

    SDL_Window *win = SDL_CreateWindow("Brick Breaker", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (!win)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren)
    {
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    //Our event structure
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
            
            if (e.type == SDL_KEYDOWN)
                quit = true;
    
            if (e.type == SDL_MOUSEBUTTONDOWN)
                quit = true;
        }

        //Render the scene
        SDL_RenderClear(ren);
        //renderTexture(image, ren, x, y);
        SDL_RenderPresent(ren);
    }

    SDL_Quit();
}




