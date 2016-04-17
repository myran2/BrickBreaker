#include "Ball.h"
#include "Log.h"

Ball::Ball(Window* window, const std::string& textureName, int xPos, int yPos) :
    Entity(window, textureName, xPos, yPos)
{
    yVelocity = -5;
    xVelocity = -5;
}


int lives = 3;

void Ball::update()
{
    // first move the ball according to its current velocity
    xPos += xVelocity;
    yPos += yVelocity;
    // then we check to see if the ball is somewhere that it shouldn't be

    // if the ball goes off the left side of the screen
    if (xPos < 0)
    {
        xPos = 0;
        xVelocity = -xVelocity;
    }

    // if the ball goes off the right side of the screen
	if(xPos > window->getWidth() - getWidth())
	{
		xPos = window->getWidth() - getWidth();
		xVelocity = -xVelocity;
	}

    // if the ball goes off the top of the screen
    if (yPos < 0)
    {
        yPos = 0;
        yVelocity = -yVelocity;
    }

    // if the ball goes off the bottom of the screen
    if (yPos > window->getHeight() - height)
    {
        setOnPaddle();
        lives--;

        if (lives >= 0)
            Log::info("Lives left: " + lives);

        if (lives == 0)
        {
            xPos = window->getWidth() / 2;
            yPos = window->getHeight() / 2;
        }
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
    xPos = 320; // initial x-position
    yPos = 368; // initial y-position
    xVelocity = 0;  // initial x-velocity
    yVelocity = 0;  // initial y-velocity
    onPaddle = true;  // ball is on paddle
}