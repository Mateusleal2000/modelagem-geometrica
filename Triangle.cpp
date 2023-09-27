#include "Triangle.hpp"

Triangle::Triangle(Point3 vertex1, Point3 vertex2, Point3 vertex3)
{
  vertices.reserve(3);
  vertices.resize(3);
  vertices[0] = vertex1;
  vertices[1] = vertex2;
  vertices[2] = vertex3;
}

Point3 Triangle::getVertex(int idx)
{
  return this->vertices[idx];
}

void Triangle::setVertex(Point3 v, int idx)
{
  vertices[idx] = v;
}