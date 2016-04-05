#ifndef _WINDOW_H
#define _WINDOW_H

#include <SDL.h>
#include <string>


class Window
{
    public:
        Window(const std::string& title, int width, int height);
        void cleanupAndExit();
        SDL_Texture* loadTexture(const std::string &file);
        void renderTexture(SDL_Texture* texture, int xPos, int yPos);

        void clear() { SDL_RenderClear(renderer); }
        void render() { SDL_RenderPresent(renderer); }

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

};

#endif
