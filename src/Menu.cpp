#include "Menu.h"

Menu::Menu(GameManager* mgr) :
manager(mgr)
{

}

void Menu::tick(SDL_Event event)
{
    switch (event.type)
    {
    // if user clicks the red X
    case SDL_QUIT:
        manager->quit();
        return;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_SPACE:
        case SDLK_KP_ENTER:
            // Play, go to settings, or close the game
            break;
        case SDLK_UP:
            // switch to the above menu option
            break;
        case SDLK_DOWN:
            // switch to the below menu option
            break;
        }
        break;
    case SDL_MOUSEMOTION:
        //int mouseX = event.motion.x;
        //int mouseY = event.motion.y;
        break;
    }

    int xPos = 200;
    int yPos = 100;
    for (MenuEntry entry : menuEntries)
    {
        if (entry.active)
            manager->getWindow()->renderText(entry.text, xPos, yPos, { 0, 0, 0 }, 50, FONT_RENDER_SHADED, {0, 48, 255});
        else
            manager->getWindow()->renderText(entry.text, xPos, yPos, { 0, 0, 0 }, 50, FONT_RENDER_BLENDED, {0, 0, 0});
        yPos += 100;
    }
}

void Menu::addEntry(const std::string& text)
{
    MenuEntry entry;
    entry.text = text;
    entry.active = menuEntries.size() == 0;

    menuEntries.push_back(entry);
}
