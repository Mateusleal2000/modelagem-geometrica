#include "Triangle.hpp"
#include "Box.hpp"

class testTriangle
{
public:
	bool separatingAxisTest(Point3 axis, Point3 v0, Point3 v1, Point3 v2, Point3 boxExtent);
	bool checkTriangleIntersect(Triangle triangle, Box* box);
	testTriangle();
	void testIntersection();
	void testIntersection(Box* box);
	Box AABB;
	std::vector<Triangle> triangles;
};
