#include "Window.h"
#include <iostream>

// Initializes the SDL window
bool Window::init(int width, int height)
{
    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    return true;
}

void Window::cleanupAndExit()
{
    for (auto texture : textures)
        SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::gameLoop()
{
    // TODO: move these out of here
    int xPos = 288;
    int yPos = 450;
    SDL_Texture* paddleTexture = loadTexture("paddle.bmp");
    bool moveLeft = false;
    bool moveRight = false;
    
    while (!quit)
    {
        // 10ms is an arbitrary value. Increasing the value will make the loop execute less often.
        SDL_Delay(10);
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
                        moveLeft = true;
                        break;
                    case SDLK_RIGHT:
                        moveRight = true;
                        break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_LEFT:
                    moveLeft = false;
                    break;
                case SDLK_RIGHT:
                    moveRight = false;
                    break;
                }
                break;
        }

        if (moveLeft)
            xPos--;
        if (moveRight)
            xPos++;

        SDL_RenderClear(renderer);
        renderTexture(paddleTexture, xPos, yPos);
        SDL_RenderPresent(renderer);
    }
}

SDL_Texture* Window::loadTexture(const std::string &file)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* img = SDL_LoadBMP(file.c_str());
    
    // if the texture fails to load
    if (!img)
    {
        std::cout << "Window::loadTexture error: " << SDL_GetError() << std::endl;
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);

    if (!texture)
    {
        std::cout << "Window::loadTexture error: " << SDL_GetError() << std::endl;
        return NULL;
    }

    // keep track of each texture we have loaded so we can remove them when we're done
    textures.push_back(texture);
    return texture;
}

void Window::renderTexture(SDL_Texture* texture, int xPos, int yPos)
{
    SDL_Rect destination;
    destination.x = xPos;
    destination.y = yPos;

    // queries the texture and places its width and height into w and h in destination
    SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);

    // actually renders the texture to the screen
    SDL_RenderCopy(renderer, texture, NULL, &destination);
}
