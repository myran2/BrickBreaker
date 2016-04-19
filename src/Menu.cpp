#include "Menu.h"

Menu::Menu(GameManager* mgr) :
manager(mgr)
{
    activeIndex = 0;
}

void Menu::tick()
{    
    SDL_Event currEvent;
    bool repeatKey = SDL_PollEvent(&currEvent) == 1;
    
    switch (currEvent.type)
    {
    // if user clicks the red X
    case SDL_QUIT:
        manager->quit();
        return;
    case SDL_KEYDOWN:
        if (repeatKey)
        {
            switch (currEvent.key.keysym.sym)
            {
            case SDLK_SPACE:
            case SDLK_RETURN:
                switch (activeIndex)
                {
                case 0:
                    manager->setState(STATE_PLAYING);
                    manager->initGame();
                    return;
                case 1: // TODO: NYI
                case 2:
                    //manager->setState(STATE_SETTINGS);
                    break;
                case 3:
                    manager->quit();
                    return;
                }
                break;
            case SDLK_UP:
                activeIndex--;
                if (activeIndex < 0)
                    activeIndex = menuEntries.size() - 1;
                break;
            case SDLK_DOWN:
                activeIndex++;
                if (activeIndex > menuEntries.size() - 1)
                    activeIndex = 0;
                break;
            }
        }
        break;
    }

    int xPos = 200;
    int yPos = 100;
    for (int i = 0; i < menuEntries.size(); i++)
    {
        if (i == activeIndex)
            manager->getWindow()->renderText(menuEntries[i], xPos, yPos, { 0, 0, 0 }, 50, FONT_RENDER_SHADED, {0, 48, 255});
        else
            manager->getWindow()->renderText(menuEntries[i], xPos, yPos, { 0, 0, 0 }, 50, FONT_RENDER_BLENDED, {0, 0, 0});
        yPos += 100;
    }
}

void Menu::addEntry(const std::string& text)
{
    menuEntries.push_back(text);
}
