#ifndef _WINDOW_H
#define _WINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>

// path seperators are different in windows and not-windows
#ifdef _WIN32
const char PATH_SEP = '\\';
#else
const char PATH_SEP = '/';
#endif

#define FONT_NAME "UbuntuMono.ttf"
#define FONT_STROKE_SIZE 2 

enum FontRenderTypes
{
    // Pixel-y looking. Default setting
    FONT_RENDER_SOLID = 0,

    // smoother than Solid
    FONT_RENDER_BLENDED = 1,

    // puts the rendered text on top of a rectangle of color 'stroke'
    FONT_RENDER_SHADED = 2
};

class Window
{
    public:
        Window(const std::string& title, int width, int height, int fps);
        // shut down SDL systems, then exit the program
        void cleanupAndExit();

        // loads a texture from the res/ folder with name 'file'
        SDL_Texture* loadTexture(const std::string &file);

        // renders given texture at (xPos, yPos). The top left corner of the texture will be placed at (xPos, yPos)
        void renderTexture(SDL_Texture* texture, int xPos, int yPos);

        // renders text to the window at (xPos, yPos)
        // SDL_color is an array of 3 integers {r, g, b} that form a color
        // size is the font size
        // renderType information can be found in the FontRenderTypes enum
        // stroke is the background color of the text (ONLY USED WITH FONT_RENDER_SHADED)
        void renderText(const std::string& msg, int xPos, int yPos, SDL_Color color, int size, int renderType, SDL_Color stroke);

        // same as renderText but without the xPos argument.
        // centers the text at the given y position
        void renderCenteredText(const std::string& msg, int yPos, SDL_Color color, int size, int renderType, SDL_Color stroke);

        // clear the screen
        void clear() { SDL_RenderClear(renderer); }
        // render the screen
        void render() { SDL_RenderPresent(renderer); }

        int getWidth() { return width; }
        int getHeight() { return height; }
        int getMaxFps() { return maxFps; }

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

        int width;
        int height;
        int maxFps;

};

#endif
