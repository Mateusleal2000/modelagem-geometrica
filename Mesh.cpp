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
		bool inside = checkMembership(node->getBox());
		inside ? node->setState(State::BLACK) : node->setState(State::WHITE);
	}
	return;
}

Point3 Mesh::getCenter()
{
	return Point3(0, 0, 0);
}

float Mesh::dMax()
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

bool Mesh::checkTriangleIntersect(Triangle triangle, Box* box){
// função esboço
	Point3 v0 = triangle.getVertex(0);
	Point3 v1 = triangle.getVertex(1);
	Point3 v2 = triangle.getVertex(2);

	// necessário o centro e a extensão da caixa, ou seja, a dimensão em cada um dos eixos
	Point3 boxCenter = box->getCenter();
	Point3 boxExtent = box->getExtent();

	v0 -= boxCenter;
	v1 -= boxCenter;
	v2 -= boxCenter;
	

    // Compute the edge vectors of the triangle  (ABC)
    // That is, get the lines between the points as vectors
    Point3 f0 = v1 - v0; // B - A
    Point3 f1 = v2 - v1; // C - B
    Point3 f2 = v0 - v2; // A - C

    // Compute the face normals of the AABB, because the AABB
    // is at center, and of course axis aligned, we know that 
    // it's normals are the X, Y and Z axis.
    Point3 u0 = Point3(1.0f, 0.0f, 0.0f);
    Point3 u1 = Point3(0.0f, 1.0f, 0.0f);
    Point3 u2 = Point3(0.0f, 0.0f, 1.0f);

    // There are a total of 13 axis to test!

    // We first test against 9 axis, these axis are given by
    // cross product combinations of the edges of the triangle
    // and the edges of the AABB. You need to get an axis testing
    // each of the 3 sides of the AABB against each of the 3 sides
    // of the triangle. The result is 9 axis of seperation
    // https://awwapp.com/b/umzoc8tiv/

    // then the remaining 4 are the normals of the cube, plus the normal from the triangle.

    // Compute the 9 axis
    Point3 axis_u0_f0 = cross(u0, f0);
    Point3 axis_u0_f1 = cross(u0, f1);
    Point3 axis_u0_f2 = cross(u0, f2);

    Point3 axis_u1_f0 = cross(u1, f0);
    Point3 axis_u1_f1 = cross(u1, f1);
    Point3 axis_u1_f2 = cross(u2, f2);

    Point3 axis_u2_f0 = cross(u2, f0);
    Point3 axis_u2_f1 = cross(u2, f1);
    Point3 axis_u2_f2 = cross(u2, f2);

    // We can get the normal of the triangle by crossing the first two line segments
    Point3 triangleNormal = cross(f0, f1);
    
    std::vector<Point3> axisArray = std::vector<Point3>({
                                                        axis_u0_f0,
                                                        axis_u0_f1,
                                                        axis_u0_f2,
                                                        axis_u1_f0,
                                                        axis_u1_f1,
                                                        axis_u1_f2,
                                                        axis_u2_f0,
                                                        axis_u2_f1,
                                                        axis_u2_f2,
                                                        u0,
                                                        u1,
                                                        u2,
                                                        triangleNormal});

    for (Point3 axis : axisArray){
        if (!separatingAxisTest(axis, v0, v1, v2, boxExtent)){
            return false;
        }
    }

	return true;
}

//Checar a existência de uma 
bool checkMembership(Box* box){
	bool found = false;

		/*TODO*/

	return found;
}

bool separatingAxisTest(Point3 axis, Point3 v0, Point3 v1, Point3 v2, Point3 boxExtent){
    // Normals from the AABB's faces (need only 3).
    // Since it is centered at the origin in relation to the triangle
    // we can use the unit vectors for all 3 axis.
    Point3 u0 = Point3(1.0f, 0.0f, 0.0f);
    Point3 u1 = Point3(0.0f, 1.0f, 0.0f);
    Point3 u2 = Point3(0.0f, 0.0f, 1.0f);
    
    // Project all 3 vertices of the triangle onto the Seperating axis
    float p0 = dot(v0, axis);
    float p1 = dot(v1, axis);
    float p2 = dot(v2, axis);
    // Project the AABB onto the seperating axis
    // We don't care about the end points of the projection
    // just the length of the half-size of the AABB
    // That is, we're only casting the extents onto the 
    // seperating axis, not the AABB center. We don't
    // need to cast the center, because we know that the
    // aabb is at origin compared to the triangle!
    float r = boxExtent[0] * fabs(dot(u0, axis)) +
                boxExtent[1] * fabs(dot(u1, axis)) +
                boxExtent[2] * fabs(dot(u2, axis));
    // Now do the actual test, basically see if either of
    // the most extreme of the triangle points intersects r
    // You might need to write Min & Max functions that take 3 arguments
    if (std::max({-(std::max({p0, p1, p2})), std::min({p0, p1, p2})}) > r) {
        // This means BOTH of the points of the projected triangle
        // are outside the projected half-length of the AABB
        // Therefore the axis is seperating and we can exit
        return false;
	} else {
        return true;
    }
}