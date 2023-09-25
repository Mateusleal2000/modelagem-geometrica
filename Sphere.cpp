#include "Sphere.hpp"
#include <iostream>
#include <math.h>

Sphere::Sphere(double rad, Point3 center) : radius(rad), center(center)
{
}

void Sphere::classify(Node *node)
{
  double dmin = 0;
  double dmax = 0;

  for (int i = 0; i < 3; i++)
  {
    double min = node->getBox()->getBmin(i);
    double max = node->getBox()->getBmax(i);
    double a = center[i] - min;
    double b = center[i] - max;
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
  double radius2 = radius * radius;
  if (dmax <= radius2)
  {
    node->setState(State::BLACK);
  }
  else if (dmin <= radius2)
  {
    node->setState(State::GRAY);
  }
  else
  {
    node->setState(State::WHITE);
  }
}

void Sphere::setRadius(double rad)
{
  this->radius = rad;
}

void Sphere::setCenter(Point3 center)
{
  this->center = center;
}

double Sphere::getRadius()
{
  return radius;
}

Point3 Sphere::getCenter()
{
  return center;
}

double Sphere::dMax()
{
  return 2.0 * radius;
}
