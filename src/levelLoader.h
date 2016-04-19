#include <vector>
#include "Window.h"
#include "Entity.h"
#include "Ball.h"
#include "Mods.h"
#include "Log.h"
#include <iostream>
#include <vector>

class LevelLoader
{
    public:
    	LevelLoader(Window* win, const std::vector<Entity*>& ent);
        void openMap(const std::string& mapName);

    private:
        Window* window;
        std::vector<Entity*> entities;
};