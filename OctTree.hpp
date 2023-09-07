#ifndef OCTREE_H
#define OCTREE_H

#include <string>
#include <cstdint>

#include "Box.hpp"
#include "Node.hpp"
#include "Solid.hpp"

class OctTree{
	public:
		OctTree();
		void makeOctTree( Node * root, uint8_t depth);
    State classify(Box * box);
    void subdivide(Node * node);

	private:
		Node * root;
		Solid * solid;
		uint8_t maxDepth;
};

#endif
