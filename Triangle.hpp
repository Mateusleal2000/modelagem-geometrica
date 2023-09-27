#include "vec3.hpp"

class Triangle
{
public:
	Triangle(Point3 vertex1, Point3 vertex2, Point3 vertex3);
	Point3 getVertex(int idx);
	void setVertex(Point3 v, int idx);

private:
	std::vector<Point3> vertices;
};
