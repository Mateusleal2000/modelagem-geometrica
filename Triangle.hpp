#include "vec3.hpp"

class Triangle
{
public:
	Triangle(Point3 x, Point3 y, Point3 z);
	Point3 getVertex(int idx);
	void setVertex(Point3 v, int idx);
private:
	std::vector<Point3> vertices;
};
