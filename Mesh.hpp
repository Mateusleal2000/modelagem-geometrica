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
	double dMax() override;

private:
	void buildMesh();
	void calculateCenter();

private:
	Point3 center;
	std::vector<Point3> triangles;
	std::string fileName;
};