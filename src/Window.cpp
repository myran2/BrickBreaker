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
    if (TTF_Init() == -1)
    {
        Log::error("Couldn't initialize sdl2-ttf!");
        exit(1);
    }
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

void Window::renderText(const std::string& msg, int xPos, int yPos, SDL_Color color, int size, int renderType, SDL_Color bgColor = {0, 0, 0})
{   
    std::string resPath = "res";
    std::string filePath = "";
    filePath = resPath + PATH_SEP + FONT_NAME;

    TTF_Font* font = TTF_OpenFont(filePath.c_str(), size);
    if (!font)
    {
        Log::error(buildSDLError("Window::renderText error: "));
        return;
    }

    SDL_Surface* msgSurface = nullptr;

    switch (renderType)
    {
    case FONT_RENDER_SOLID:
        msgSurface = TTF_RenderText_Solid(font, msg.c_str(), color);
        break;
    case FONT_RENDER_BLENDED:
        msgSurface = TTF_RenderText_Blended(font, msg.c_str(), color);
        break;
    case FONT_RENDER_SHADED:
        msgSurface = TTF_RenderText_Shaded(font, msg.c_str(), color, bgColor);
        break;
    default:
        Log::warn("Got unknown render type (" + std::to_string(renderType) + "), using RENDER_SOLID.");
        msgSurface = TTF_RenderText_Solid(font, msg.c_str(), color);
        break;
    }

    SDL_Texture* msgTexture = SDL_CreateTextureFromSurface(renderer, msgSurface);
    SDL_FreeSurface(msgSurface);

    SDL_Rect rect;
    rect.x = xPos;
    rect.y = yPos;
    SDL_QueryTexture(msgTexture, NULL, NULL, &rect.w, &rect.h);

    SDL_RenderCopy(renderer, msgTexture, NULL, &rect);
    TTF_CloseFont(font);
}
