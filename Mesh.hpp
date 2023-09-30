#include "Solid.hpp"
#include "Triangle.hpp"
#include <vector>
#include <string>

class Mesh : public Solid
{
public:
	Mesh();
	Mesh(std::string fileName);
	void classify(Node *node) override;
	void setCenter(Point3 center);
	Point3 getCenter() override;
	Point3 getVertex(int idx);
	std::vector<Triangle> getTriangles();
	float dMax() override;
	bool checkTriangleIntersect(Triangle triangle, Box *box);
	bool checkMembership(Box *box);
	bool checkRayTriangleIntersect(std::pair<Point3,Vec3> normal, Triangle triangle);
	bool separatingAxisTest(Point3 axis, Point3 v0, Point3 v1, Point3 v2, Point3 boxExtent);

private:
	void buildMesh();
	void calculateCenter();

private:
	Point3 center;
	std::vector<Triangle> triangles;
	std::vector<int> indices;
	std::vector<int> indices_normal;
	std::vector<Point3> vertices;
	std::string fileName;
};