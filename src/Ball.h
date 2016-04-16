#ifndef _BALL_H
#define _BALL_H

#include <iostream>
#include "Entity.h"

class Ball : public Entity
{
public:
    Ball(Window* window, const std::string& textureName, int xPos, int yPos);

    virtual void update();

    // called when the ball hits something
    void handleCollision(Entity* entity);

    //called to place the ball on the paddle
    void setOnPaddle();

private:
    int xVelocity;  //left and right velocity
    int yVelocity;  //up and down velocity
    bool onPaddle;  //checks if the ball is on the paddle
};

#endif
