#include "Sphere.hpp"
#include <iostream>
#include <math.h>

Sphere::Sphere(float rad, Point3 center) : radius(rad), center(center)
{
}

State Sphere::classify(Node *node)
{
  float dmin = 0;
  float dmax = 0;

  for (int i = 0; i < 3; i++)
  {
    float min = node->getBox()->getBmin(i);
    float max = node->getBox()->getBmax(i);
    float a = center[i] - min;
    float b = center[i] - max;
    if (center[i] < min)
    {
      dmin += (a * a);
    }
    else if (center[i] > node->getBox()->getBmax(i))
    {
      dmin += (b * b);
    }
    // dmin = std::min(a*a, b*b)
    dmax += std::max(a * a, b * b);
  }
  float radius2 = radius * radius;
  if (dmax <= radius2)
  {
    node->setState(State::BLACK);
    return State::BLACK;
  }
  else if (dmin <= radius2)
  {
    node->setState(State::GRAY);
    return State::GRAY;
  }
  else
  {
    node->setState(State::WHITE);
    return State::WHITE;
  }
}

void Sphere::setRadius(float rad)
{
  this->radius = rad;
}

void Sphere::setCenter(Point3 center)
{
  this->center = center;
}

float Sphere::getRadius()
{
  return radius;
}

Point3 Sphere::getCenter()
{
  return center;
}

float Sphere::dMax()
{
  return 2.0 * radius;
}

Vec3 Sphere::maxValAxis()
{
  return Vec3(center.x() + radius, center.y() + radius, center.z() + radius);
}

Vec3 Sphere::minValAxis()
{
  return Vec3(center.x() - radius, center.y() - radius, center.z() - radius);
}
