#ifndef BLOCK_H
#define BLOCK_H

#include "Solid.hpp"

class Block: public Solid{
	public:
    Block();
    Block(Point3 p_min, float size_x,float size_y,float size_z);
		void classify(Node * node);
		float dMax();
		Point3 getCenter();
	private:
			float side_x;
			float side_y;
			float side_z;
};

#endif // BLOCK_H