#ifndef PHYSICS_H
#define PHYSICS_H

class Physics
{
public:
  float getFallingSpeed(); //retrieve the falling speed
  float getBounceAngle();  //retrieve the bounceAngle

private:
  float fallingSpeed;
  float bounceAngle;

};

#endif
