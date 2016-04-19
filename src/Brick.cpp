#include "Brick.h"

Brick::Brick(Window* window, const std::string& textureName, int xPos, int yPos, int maxHealth) :
Entity(window, textureName, xPos, yPos)
{
    this->typeId = TYPEID_BRICK;

	this->maxHealth = maxHealth;
    health = maxHealth;
}

// function for detecting if the brick is damaged
void Brick::dealDamage(int dmg)
{
    health -= dmg;

	if (health == 2)
		setTexture("yellowBrick.bmp");
	if (health == 1)
		setTexture("greenBrick.bmp");

    if (health <= 0)
        remove();
}
