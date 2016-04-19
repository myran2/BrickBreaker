#ifndef _BRICK_H
#define _BRICK_H

#include "Entity.h"

class Brick : public Entity
{
    public:
        Brick(Window* window, const std::string& textureName, int xPos, int yPos, int maxHealth);

        int getHealth() { return health; }
        int getMaxHealth() { return maxHealth; }

        // deal 'dmg' damage to the brick.
        // if the brick survives the damage (health > 0), return true
        // otherwise, false
        bool dealDamage(int dmg);

    private:
        int health;
        int maxHealth;
};

#endif
