#include "Triangle.hpp"

Triangle::Triangle(Point3 x, Point3 y, Point3 z){
  vertices.reserve(3);
  vertices.resize(3);
  vertices[0] = x;
  vertices[1] = y;
  vertices[2] = z;
}

Point3 Triangle::getVertex(int idx){
	return this->vertices[idx];
}

void Triangle::setVertex(Point3 v, int idx){
	vertices[idx] = v;
}