#include <iostream>
#include "Entity.h"
#include "Window.h"

Entity::Entity(Window* window, const std::string& textureName, int xPos, int yPos)
{
    this->window = window;
    this->xPos = xPos;
    this->yPos = yPos;
    
    this->texture = window->loadTexture(textureName);

    // store the texture's width and height
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);

    moveState = MOVE_NONE;
    moveRate = 1;
}

Entity::~Entity()
{
    std::cout << "Destroyed entity with texture" << std::endl;
    SDL_DestroyTexture(texture);
}

void Entity::update()
{
    if (isMoving(MOVE_UP))
        yPos -= moveRate;

    if (isMoving(MOVE_DOWN))
        yPos += moveRate;

    if (isMoving(MOVE_LEFT))
        xPos -= moveRate;

    if (isMoving(MOVE_RIGHT))
        xPos += moveRate;

    if (xPos < 0)
        xPos = 0;

    if (yPos < 0)
        yPos = 0;

    if (xPos > window->getWidth() - width)
        xPos = window->getWidth() - width;

    if (yPos > window->getHeight() - height)
        yPos = window->getHeight() - height;
    
    window->renderTexture(texture, xPos, yPos);
}

void Entity::startMoving(int direction)
{
    moveState |= direction;
}

void Entity::stopMoving(int direction)
{
    moveState &= ~direction;
}

bool Entity::isMoving(int direction)
{
    return (moveState & direction) != 0;
}
