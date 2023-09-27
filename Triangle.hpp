#include "vec3.hpp"

class Triangle
{
public:
	Triangle(Point3 x, Point3 y, Point3 z);

private:
	Point3 vertex1;
	Point3 vertex2;
	Point3 vertex3;
};
