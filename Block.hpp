#ifndef BLOCK_H
#define BLOCK_H

#include "Solid.hpp"

class Block: public Solid{
	public:
    Block();
    Block(Point3 p_min, double size_x,double size_y,double size_z);
		void classify(Node * node);
		double dMax();
		Point3 getCenter();
	private:
			double side_x;
			double side_y;
			double side_z;
};

#endif // BLOCK_H