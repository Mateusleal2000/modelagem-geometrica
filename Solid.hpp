#ifndef SOLID_H
#define SOLID_H

#include "Node.hpp"
#include "vec3.hpp"

class Solid{

  public:
    ~Solid();
    void classify(Node * node);
    void setColor(RGBcolor color);

  private:
    RGBcolor color;

};

inline void Solid::setColor(RGBcolor color){
  this->color = color;
}

#endif