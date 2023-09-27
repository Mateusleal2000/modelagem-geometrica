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
	float dMax() override;
	bool checkTriangleIntersect(Triangle triangle, Box *box);
	bool checkMembership(Box *box);

private:
	void buildMesh();
	void calculateCenter();

private:
	Point3 center;
	std::vector<Triangle> triangles;
	std::vector<int> indices;
	std::string fileName;
};