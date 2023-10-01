#ifndef NODE_H
#define NODE_H
#include <vector>
#include "vec3.hpp"
#include "Box.hpp"
#include <set>

enum State
{
  BLACK = 3,
  WHITE = 0,
  GRAY = 1
};

class Node
{
public:
  Node();
  Node(Node *parent, Box *box);
  ~Node();
  State getState();
  Node *getParent();
  Node *getChild(int index);
  Box *getBox();
  unsigned int getIndex(int i);
  void setState(State state);
  void setParent(Node *parent);
  void setChild(Node *child);
  void setBox(Box *box);
  void setGlobalVerticesSet(std::set<Point3> *globalVerticesSet);
  void setGlobalVerticesVector(std::vector<Point3> *globalVerticesVector);
  void deletePoints();
  void mapPointsToIndex();
  void insertPointsIntoSet();
  float calcArea();
  float calcVolume();

  // operators
public:
  Node &operator=(Node &n)
  {
    state = n.getState();
    parent = n.getParent();
    if (n.getState() == State::GRAY)
    {
      for (int i = 0; i < 8; i++)
      {
        children[i] = n.getChild(i);
      }
    }
    return *this;
  }

private:
  State state;
  Node *parent;
  Box *box;
  std::set<Point3> *globalVerticesSet;
  std::vector<Point3> *globalVerticesVector;
  std::vector<Node *> children;
};

inline void Node::setChild(Node *child)
{
  this->children.emplace_back(child);
};

inline void Node::setState(State state)
{
  this->state = state;
};

inline void Node::setParent(Node *parent)
{
  this->parent = parent;
};

inline void Node::setBox(Box *Box)
{
  this->box = box;
};

#endif