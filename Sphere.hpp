#ifndef SPHERE_H
#define SPHERE_H

#include "Solid.hpp"
#include "vec3.hpp"

class Sphere : public Solid
{
public:
	Sphere();
	Sphere(float rad, Point3 center);
	void classify(Node *node) override;
	void setRadius(float rad);
	void setCenter(Point3 center);
	float getRadius();
	Point3 getCenter() override;
	float dMax() override;

private:
	float radius;
	Point3 center;
};

#endif // SPHERE_H