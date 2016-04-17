#include "Mods.h"

Mods::Mods(Window* window, const std::string& textureName, int xPos, int yPos) :
    Entity(window, textureName, xPos, yPos)
{
	yVelocity = 5;
	xVelocity = 0;
}

// makes the Powerup drop and updates the Powerup to its current location
void Mods::update()	
{
	xPos += xVelocity;
    yPos += yVelocity;
	window->renderTexture(texture, xPos, yPos);
}
