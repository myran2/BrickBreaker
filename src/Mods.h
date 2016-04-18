#ifndef _MODS_H
#define _MODS_H

#include "Entity.h"
#include "Log.h"
#include <iostream>

class Mods : public Entity
{
    public:
        Mods(Window* window, const std::string& textureName, int xPos, int yPos);

        virtual void update();
        void doubleBalls();

    private:
        int xVelocity;  //left and right velocity
        int yVelocity;  //up and down velocity
};

#endif
