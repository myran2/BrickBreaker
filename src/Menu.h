#ifndef _MENU_H
#define _MENU_H

#include <vector>
#include "GameManager.h"

struct MenuEntry
{
    std::string text;
    bool active;
};

class Menu
{
    public:
        Menu(GameManager* mgr);
        void tick(SDL_Event event);
        void addEntry(const std::string& text);

    private:
        std::vector<MenuEntry> menuEntries;
        GameManager* manager;
};

#endif