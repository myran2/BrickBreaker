#ifndef _WINDOW_H
#define _WINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

// path seperators are different in windows and not-windows
#ifdef _WIN32
const char PATH_SEP = '\\';
#else
const char PATH_SEP = '/';
#endif

#define FONT_NAME "UbuntuMono.ttf"

enum FontRenderTypes
{
    FONT_RENDER_SOLID = 0,
    FONT_RENDER_BLENDED,
    FONT_RENDER_SHADED
};

class Window
{
    public:
        Window(const std::string& title, int width, int height, int fps);
        void cleanupAndExit();
        SDL_Texture* loadTexture(const std::string &file);
        void renderTexture(SDL_Texture* texture, int xPos, int yPos);
        void renderText(const std::string& msg, int xPos, int yPos, SDL_Color color, int size, int renderType);

        void clear() { SDL_RenderClear(renderer); }
        void render() { SDL_RenderPresent(renderer); }

        int getWidth() { return width; }
        int getHeight() { return height; }
        int getMaxFps() { return maxFps; }

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

        TTF_Font* font;

        int width;
        int height;
        int maxFps;

};

#endif
