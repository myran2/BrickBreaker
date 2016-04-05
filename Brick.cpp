#include "Brick.h"

Brick::Brick(Window* window, const std::string& textureName, int xPos, int yPos, int maxHealth) :
Entity(window, textureName, xPos, yPos)
{
    this->maxHealth = maxHealth;
    health = maxHealth;
}

void Brick::dealDamage(int dmg)
{
    health -= dmg;

    if (health <= 0)
        remove();
}