#include "Node.hpp"
#include <algorithm>
#include <unistd.h>

Node::Node() : parent(nullptr), box(nullptr)
{
  children.reserve(8);
}

Node::Node(Node *parent, Box *box) : parent(parent), box(box)
{
  children.reserve(8);
}

Node::~Node()
{
  for (int i = 0; i < children.size(); ++i)
  {
    delete children[i];
  }
  delete box;
}

void Node::setGlobalVerticesSet(std::set<Point3> *gvs)
{
  globalVerticesSet = gvs;
  return;
}

void Node::setGlobalVerticesVector(std::vector<Point3> *gvv)
{
  globalVerticesVector = gvv;
  return;
}

void Node::mapPointsToIndex()
{
  // std::cout << "Entrou no mapPointsToIndex\n";
  for (int i = 0; i < 8; i++)
  {
    std::vector<Point3>::iterator it = std::lower_bound(globalVerticesVector->begin(), globalVerticesVector->end(), box->getPoint(i));
    // std::vector<Point3>::iterator it = std::find(globalVerticesVector->begin(), globalVerticesVector->end(), box->getPoint(i));
    int idx = std::distance(globalVerticesVector->begin(), it);
    // std::cout << "index: " << idx << " of point: " << box->getPoint(i) << std::endl;
    // sleep(2);
    box->setIndex(i, idx);
  }

  for (int j = 0; j < 8; j++)
  {
    Point3 p = box->getPoint(j);
    int idx2 = box->getIndex(j);
    if (!(globalVerticesVector->at(idx2) == p))
    {
      std::cout << "Diferente\n";
    }
  }

  for (Node *node : children)
  {
    node->mapPointsToIndex();
  }
  // std::cout << "Terminou o mapPointsToIndex\n";
}

void Node::insertPointsIntoSet()
{
  for (int i = 0; i < 8; i++)
  {
    bool inserted = globalVerticesSet->insert(box->getPoint(i)).second;
    if (inserted)
    {
      globalVerticesVector->push_back(box->getPoint(i));
    }
  }
}

Node *Node::getChild(int index)
{
  return children[index];
}
State Node::getState()
{
  return state;
}
Node *Node::getParent()
{
  return parent;
}

Box *Node::getBox()
{
  return box;
}

unsigned int Node::getIndex(int i)
{
  return box->getIndex(i);
}

void Node::deletePoints()
{
  delete globalVerticesSet;
}