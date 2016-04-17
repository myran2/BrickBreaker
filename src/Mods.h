#ifndef _MODS_H
#define _MODS_H

#include "Entity.h"
#include <iostream>

class Mods : public Entity
{
public:
    Mods(Window* window, const std::string& textureName, int xPos, int yPos);

    virtual void update();


private:
    int xVelocity;  //left and right velocity
    int yVelocity;  //up and down velocity

   
};
#endif
