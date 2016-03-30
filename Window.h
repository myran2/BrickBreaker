#include <SDL.h>
#include <vector>

class Window
{
    public:
        bool init(int width, int height);
        void cleanupAndExit();
        void gameLoop();
        SDL_Texture* loadTexture(const std::string &file);
        void renderTexture(SDL_Texture* texture, int xPos, int yPos);

        SDL_Event event;

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

        bool quit = false;

        std::vector<SDL_Texture*> textures;
};
