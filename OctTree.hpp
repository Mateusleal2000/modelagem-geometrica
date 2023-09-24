#ifndef OCTREE_H
#define OCTREE_H

#include <string>
#include <cstdint>

#include "Node.hpp"
#include "Solid.hpp"

class OctTree{
	public:
		OctTree();
		OctTree(int maxDepth);
		~OctTree();
		void initOctTree();
		Node * getRoot();
		void setRoot(Node * root);
		int getMaxDepth() const;
		void setSolid(Solid * solid);
		void setMaxDepth(int maxDepth);
		double calcArea() const;
		double calcVolume() const;
		void printOctTree(Node * node);

	private:
    void subdivide(Node * node);
		void calcBox(Node* node, Point3 TLB, Point3 BRF, uint8_t depth);
		void divideBox(const Point3 &TLB, const Point3 &BRF, Point3 &new_TLB, Point3 &new_BRF, uint8_t depth);
		void makeOctTree(Node * root, int depth);
		Node * root;
		int maxDepth;
		Solid * solid;


};


inline void OctTree::setRoot(Node * root){
  this->root = root;
}

inline void OctTree::setMaxDepth(int maxDepth) {
  this->maxDepth = maxDepth;
}

inline void OctTree::setSolid(Solid * solid){
	this->solid = solid;
}

#endif
