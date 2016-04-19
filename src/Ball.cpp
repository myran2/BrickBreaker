#include "Ball.h"
#include "Log.h"

Ball::Ball(Window* window, const std::string& textureName, int xPos, int yPos, Entity* linkedPaddle) :
    Entity(window, textureName, xPos, yPos)
{
    this->linkedPaddle = linkedPaddle;
    lives = 3;
    yVelocity = 0;
    xVelocity = 0;
}

void Ball::update()
{
    // don't render the ball if there are no lives left
    if (lives <= 0)
        return;

    // if the ball is still on the paddle, make it move in sync with the paddle
    if (onPaddle)
    {
        xPos = linkedPaddle->getX() + (linkedPaddle->getWidth() / 4);
        yPos = linkedPaddle->getY() - getHeight();
        window->renderTexture(texture, xPos, yPos);
        return;
    }

    // first move the ball according to its current velocity
    xPos += xVelocity;
    yPos += yVelocity;

    // then we check to see if the ball is somewhere that it shouldn't be
    // if it is, correct that

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
        lives--;
        Log::info("Lives left: " + std::to_string(lives));
        setOnPaddle(true);
    }

    // actually render the ball at its new position to the screen
    window->renderTexture(texture, xPos, yPos);
}

void Ball::handleCollision(Entity* entity)
{
    Log::info("Ball hit something!");


    double ballCenter = xPos + (width / 2);
    double entityCenter = entity->getX() + (entity->getWidth() / 2);
	double ballY = yPos + (width / 2);
	double entityY = entity->getX() + (entity->getWidth() / 2);
	double verticalDifference = std::abs(ballY - entityY);
	if(verticalDifference>20.0)
		yVelocity = -yVelocity;

    // if the ball is on the right side of the paddle, make it bounce right
    if (ballCenter > entityCenter)
        xVelocity = std::abs(xVelocity);
    // if the ball is on the left side of the paddle, make it bounce left
    else
        xVelocity = -std::abs(xVelocity);
}

void Ball::setOnPaddle(bool apply)
{
    if (apply)
        Log::info("Placed ball on paddle.");
    else
        Log::info("Freed ball from paddle.");

    onPaddle = apply;
}

void Ball::outOfBounds()
{
  if (yPos > window->getHeight() - height)
  {
    Log::info("Ball2 removed.");
    remove();
  }
}

void Ball::setLives(int count)
{
    lives = count;
    Log::info("Set new life count to " + std::to_string(count));
}

void Ball::detach()
{
    Log::info("Detached ball from paddle.");
    onPaddle = false;

    // TODO: physics this part
    xVelocity = -5;
    yVelocity = -5;
}
