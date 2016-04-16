#include "Ball.h"
#include "Log.h"

Ball::Ball(Window* window, const std::string& textureName, int xPos, int yPos) :
    Entity(window, textureName, xPos, yPos)
{
    yVelocity = 1;
    xVelocity = 1;
}

void Ball::update()
{
    xPos += xVelocity;
    yPos += yVelocity;

    if (xPos < 0)
    {
        xPos = 0;
        xVelocity = -xVelocity;
    }
	if(xPos > 610)
	{
		xPos = 610;
		xVelocity = -xVelocity;
	}

    if (yPos < 0)
    {
        yPos = 0;
        yVelocity = -yVelocity;
    }

    if (yPos > window->getHeight() - height)
    {
        yPos = window->getHeight() - height;
        yVelocity = -yVelocity;
    }

    window->renderTexture(texture, xPos, yPos);
}


void Ball::handleCollision(Entity* entity)
{
		
    yVelocity = -yVelocity;
    Log::info("Ball hit something!");
}

void Ball::setOnPaddle()
{
    //TODO: make function for setting the ball on the paddle
    onPaddle = true;
}
