#include "Ball.h"
#include <iostream>

Ball::Ball(Window* window, const std::string& textureName, int xPos, int yPos) :
    Entity(window, textureName, xPos, yPos)
{
    yVelocity = 1;
    xVelocity = 0;
}

void Ball::update()
{
    std::cout << "Updating ball position" << std::endl;
    xPos += xVelocity;
    yPos += yVelocity;

    if (xPos < 0)
    {
        xPos = 0;
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