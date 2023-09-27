#include "Mesh.hpp"

Mesh::Mesh(std::string fileName)
{
	buildMesh();
	calculateCenter();
}

void Mesh::classify(Node *node)
{
	bool found = false;
	int i = 0;
	while (!found && (i < triangles.size()))
	{
		found = checkTriangleIntersect(triangles[i], node->getBox());
		i++;
	}
	if (found)
	{
		node->setState(State::GRAY);
	}
	else
	{
		bool inside = checkBoxMembership(node->getBox());
		inside ? node->setState(State::BLACK) : node->setState(State::WHITE);
	}
	return;
}

Point3 Mesh::getCenter()
{
	return Point3(0, 0, 0);
}

double Mesh::dMax()
{
	return 0.0;
}

void Mesh::setCenter(Point3 center)
{
	this->center = center;
}

void Mesh::buildMesh()
{
	return;
}