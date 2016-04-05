#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include <vector>
#include "Window.h"
#include "Entity.h"
#include "Ball.h"

class GameManager
{
    public:
        GameManager(Window* window);

        void go();

    private:
        Window* window;
        SDL_Event event;

        std::vector<Entity*> entities;
};

#endif
