#ifndef _BALL_H
#define _BALL_H

#include <iostream>
#include "Entity.h"

class Ball : public Entity
{
public:
    Ball(Window* window, const std::string& textureName, int xPos, int yPos, Entity* linkedPaddle);

    virtual void update();

    // called when the ball hits something
    void handleCollision(Entity* entity);

    // called to place the ball on the paddle
    void setOnPaddle(bool apply);

    bool isOnPaddle() { return onPaddle; }

    // detaches the ball from the paddle and gives the ball some initial velocity
    void detach();

    void setLives(int count);

private:
    int xVelocity;  //left and right velocity
    int yVelocity;  //up and down velocity

    Entity* linkedPaddle;
    bool onPaddle;

    int lives;
};
#endif
