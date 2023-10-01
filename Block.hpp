#ifndef BLOCK_H
#define BLOCK_H

#include "Solid.hpp"

class Block : public Solid
{
public:
	Block();
	Block(Point3 p_min, float size_x, float size_y, float size_z);
	State classify(Node *node) override;
	float dMax();
	Vec3 maxValAxis();
	Vec3 minValAxis();
	Point3 getCenter();

private:
	float size_x;
	float size_y;
	float size_z;
	Point3 p_min;
};

#endif // BLOCK_H