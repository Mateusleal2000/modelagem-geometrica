#ifndef OCTREE_H
#define OCTREE_H

#include <string>
#include <cstdint>
#include <set>
#include <QObject>

#include "Node.hpp"
#include "Solid.hpp"

class OctTree : public QObject
{
	Q_OBJECT
public:
	OctTree();
	OctTree(int maxDepth);
	~OctTree();
	void initOctTree();
	Node *getRoot();
	void setRoot(Node *root);
	int getMaxDepth() const;
	void setSolid(Solid *solid);
	void setMaxDepth(int maxDepth);
	float calcArea() const;
	std::vector<Point3> *getGlobalVerticesVector();
	float calcVolume() const;
	void printOctTree(Node *node);

public slots:
	void treeScale(float scaleFactor, Node *node);
	void treeVolume(float *volume, Node *node);
	void addSolid(Solid *solid);

private:
	void subdivide(Node *node);
	void calcBox(Node *node, Point3 TLB, Point3 BRF, uint8_t depth);
	void divideBox(const Point3 &TLB, const Point3 &BRF, Point3 &new_TLB, Point3 &new_BRF, uint8_t depth);
	void makeOctTree(Node *root, int depth);
	void convertSetToVector();
	void getMaxDimensionAndCenter(float *dmax, Point3 *center);
	void treeScaleRecursive(float scaleFactor, Node *node = nullptr);
	void updateGlobalVertexVector(float scaleFactor);
	Node *root;
	int maxDepth;
	std::vector<Solid *> solid;
	std::set<Point3> *globalVerticesSet;
	std::vector<Point3> *globalVerticesVector;
};

inline void OctTree::setRoot(Node *root)
{
	this->root = root;
}

inline void OctTree::setMaxDepth(int maxDepth)
{
	this->maxDepth = maxDepth;
}

inline void OctTree::setSolid(Solid *solid)
{
	this->solid.push_back(solid);
}

inline void OctTree::convertSetToVector()
{
	if (globalVerticesVector != nullptr)
		delete globalVerticesVector;
	globalVerticesVector = new std::vector<Point3>(globalVerticesSet->begin(), globalVerticesSet->end());
}

#endif
