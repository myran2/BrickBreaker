#ifndef PHYSICS_H
#define PHYSICS_H

class Physics
{
public:
  void getFallingSpeed(); //retrieve the falling speed
  void getBounceAngle();  //retrieve the bounceAngle

private:
  float fallingSpeed;
  float bounceAngle;

};

#endif
