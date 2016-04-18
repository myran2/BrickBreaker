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

// function to spawn the other ball
void Mods::doubleBalls()
{
  Log::info("Spawn another ball!");
}
void Mods::largePaddle()
{
	Log::info("Sqawn bigger paddle");
}
// function to make the paddle slower
void Mods::slowerPaddle()
{
	Log::info("Make the paddle slower!");
}
void Mods::smallPaddle()
{
	Log::info("Spawn smaller paddle");
}
