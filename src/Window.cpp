#include <iostream>
#include <string>
#include <sstream>
#include "Log.h"
#include "Window.h"


// Initializes the SDL window
Window::Window(const std::string& title, int width, int height, int fps)
{
    // init SDL
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
    this->width = width;
    this->height = height;
    this->maxFps = fps;
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Window::cleanupAndExit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

static std::string buildSDLError(const std::string& err)
{
    std::ostringstream stream;
    stream << err << SDL_GetError();
    return stream.str();
}

SDL_Texture* Window::loadTexture(const std::string& fileName)
{
    std::string resPath = "res";
    std::string filePath = "";
    filePath = resPath + PATH_SEP + fileName;
    
    SDL_Texture* texture = NULL;
    SDL_Surface* img = SDL_LoadBMP(filePath.c_str());

    // if the texture fails to load
    if (!img)
    {
        Log::error(buildSDLError("Window::loadTexture error: "));
        return NULL;
    }

    texture = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);

    if (!texture)
    {
        Log::error(buildSDLError("Window::loadTexture error: "));
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

void Window::renderText(const std::string& msg, int xPos, int yPos, SDL_Color color)
{
    std::string resPath = "res";
    std::string filePath = "";
    filePath = resPath + PATH_SEP + "UbuntuMono.ttf";
    
    TTF_Font* font = TTF_OpenFont(filePath.c_str(), 24);
    if (!font)
    {
        Log::error(buildSDLError("Window::renderText error: "));
        return;
    }
    
    SDL_Surface* msgSurface = TTF_RenderText_Solid(font, msg.c_str(), color);
    SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(renderer, msgSurface);

    SDL_FreeSurface(msgSurface);

    SDL_Rect destination;
    destination.x = xPos;
    destination.y = yPos;
    destination.h = 100;
    destination.w = 100;

    SDL_RenderCopy(renderer, msgTexture, NULL, &destination);
}
