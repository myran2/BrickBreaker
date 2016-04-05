#include <iostream>
#include "Window.h"


// Initializes the SDL window
Window::Window(const std::string& title, int width, int height)
{
    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    this->width = width;
    this->height = height;
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

}

void Window::cleanupAndExit()
{
    // this might crash stuff, not sure
    //for (Entity* e : spawnedEntities)
        //SDL_DestroyTexture(e->getTexture());

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Texture* Window::loadTexture(const std::string& file)
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
