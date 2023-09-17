#ifndef SOLID_H
#define SOLID_H

#include "Node.hpp"
#include "vec3.hpp"

class Solid{

  public:
    virtual ~Solid(){}
    virtual void classify(Node * node) = 0;
    virtual double dMax() = 0;
    virtual Point3 getCenter() = 0;
    //virtual 
    void setColor(RGBcolor color);

  private:
    RGBcolor color;

};

inline void Solid::setColor(RGBcolor color){
  this->color = color;
}

#endif