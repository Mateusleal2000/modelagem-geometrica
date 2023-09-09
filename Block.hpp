#ifndef BLOCK_H
#define BLOCK_H

#include "Solid.hpp"

class Block: public Solid{
	public:
    Block();
    Block(Point3 tlb, Point3 brf);
		void classify(Node * node);

		void setTLB(Point3 & tlb);
		void setBRF(Point3 & brf);
		Point3 & getTLB();
		Point3 & getBRF();
	private:
			double side;
			Point3 top_left_back;
      Point3 bottom_right_front;
};

#endif