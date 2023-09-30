#include "Triangle.hpp"

Triangle::Triangle(int index1, int index2, int index3)
{
  indices.reserve(3);
  indices.resize(3);
  indices[0] = index1;
  indices[1] = index2;
  indices[2] = index3;
}

int Triangle::getIndex(int idx)
{
  return this->indices[idx];
}

void Triangle::setIndex(int i, int idx)
{
  indices[idx] = i;
}