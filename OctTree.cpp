#include "OctTree.hpp"

#include <iomanip>
#include <fstream>

OctTree::OctTree() : solid(nullptr), root(nullptr) {}

OctTree::OctTree(int maxDepth) : maxDepth(maxDepth), solid(nullptr), root(nullptr)
{
  globalVerticesSet = new std::set<Point3>();
  globalVerticesVector = new std::vector<Point3>();
}

OctTree::~OctTree()
{
  root->deletePoints();
  delete root;
  delete solid;
}

void OctTree::initOctTree()
{
  float dmax = solid->dMax();
  Point3 center = solid->getCenter();
  float halfdMax = dmax / 2.0;
  Point3 TLB = Point3(center.x() - halfdMax, center.y() + halfdMax, center.z() - halfdMax);

  Point3 BRF = Point3(center.x() + halfdMax, center.y() - halfdMax, center.z() + halfdMax);

  Box *box = new Box(TLB, BRF);
  box->calcBoxPoints();
  root = new Node(nullptr, box);
  root->setGlobalVerticesSet(globalVerticesSet);
  root->setGlobalVerticesVector(globalVerticesVector);
  root->insertPointsIntoSet();
  makeOctTree(root, maxDepth);

  std::sort(globalVerticesVector->begin(), globalVerticesVector->end());


  //auto it = std::unique(globalVerticesVector->begin(), globalVerticesVector->end());
  //bool wasUnique = (it == globalVerticesVector->end());
  //if(wasUnique) std::cout<<"Was unique\n";


  root->mapPointsToIndex();
  printOctTree(root);
}

void OctTree::makeOctTree(Node *child, int depth)
{
  Node *root = child;
  root->setState(State::BLACK);
  if (depth > 1)
  {
    solid->classify(root);
    if (root->getState() == State::GRAY)
    {
      subdivide(root);
      for (int i = 0; i < 8; i++)
      {
        makeOctTree(root->getChild(i), depth - 1);
      }
    }
  }
}

void OctTree::subdivide(Node *node)
{

  Box *parentBox = node->getBox();
  calcBox(node, parentBox->getPoint(PointLabel::TLB), parentBox->getPoint(PointLabel::BRF), 3);
}

Node *OctTree::getRoot()
{
  return root;
}

int OctTree::getMaxDepth() const
{
  return maxDepth;
}

std::vector<Point3> *OctTree::getGlobalVerticesVector()
{
  return globalVerticesVector;
}

void OctTree::calcBox(Node *node, Point3 TLB, Point3 BRF, uint8_t depth)
{
  Point3 new_TLB, new_BRF;

  if (depth == 0)
  {
    Box *box = new Box(TLB, BRF);
    box->calcBoxPoints();

    Node *child = new Node(node, box);
    node->setChild(child);
    child->setGlobalVerticesSet(globalVerticesSet);
    child->setGlobalVerticesVector(globalVerticesVector);
    child->insertPointsIntoSet();

    return;
  }

  divideBox(TLB, BRF, new_TLB, new_BRF, depth);
  calcBox(node, new_TLB, BRF, depth - 1);
  calcBox(node, TLB, new_BRF, depth - 1);
}

// Caso 3: Plano xy, divide o z ao meio
// Caso 2: Plano xz, divide o y ao meio
// Caso 1: plano yz, divide o x ao meio

void OctTree::divideBox(const Point3 &TLB, const Point3 &BRF, Point3 &new_TLB, Point3 &new_BRF, uint8_t depth)
{
  int coord = depth - 1;
  float l = TLB[coord] - BRF[coord];
  new_TLB = TLB;
  new_TLB[coord] = TLB[coord] - (l / 2.0);

  new_BRF = BRF;
  new_BRF[coord] = BRF[coord] + (l / 2.0);
}

void OctTree::printOctTree(Node *node)
{
  std::ofstream MyFile("sphere.obj", std::ios::app);
  std::vector<Point3>::iterator itr;
  for (itr = globalVerticesVector->begin(); itr != globalVerticesVector->end(); itr++)
  {
    MyFile << std::setprecision(4) << "v  " << itr->x() << " " << itr->y() << " " << itr->z() << "\n";
  }
  // Point3 tlb = node->getBox()->getPoint(PointLabel::TLB);
  // Point3 brf = node->getBox()->getPoint(PointLabel::BRF);
  // std::ofstream MyFile("sphere.obj", std::ios::app);
  // if (node->getState() == State::BLACK)
  // {
  //   MyFile << std::setprecision(4) << "v  " << tlb.x() << " " << tlb.y() << " " << tlb.z() << "\n";
  //   MyFile << std::setprecision(4) << "v  " << brf.x() << " " << brf.y() << " " << brf.z() << "\n";
  // }
  // if (node->getState() != State::GRAY)
  // {
  //   return;
  // }
  // for (int i = 0; i < 8; i++)
  // {
  //   printOctTree(node->getChild(i));
  // }
  // std::cout << globalVertices->size() << std::endl;
}