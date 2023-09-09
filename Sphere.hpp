#ifndef SPHERE_H
#define SPHERE_H

#include "Solid.hpp"
#include "vec3.hpp"

class Sphere: public Solid{
	public:
		Sphere();
		Sphere(double rad, Point3 & center);
		void classify(Node * node);
		void setRadius(double rad);
		void setCenter(Point3 & center);
		double getRadius();
		Point3 * getCenter();
		
	private:
		double radius;
		Point3 center;
};

#endif // SPHERE_H