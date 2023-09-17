#include "OctTree.hpp"

OctTree::OctTree() : solid(nullptr),root(nullptr) {}

OctTree::OctTree(int maxDepth) : maxDepth(maxDepth), solid(nullptr), root(nullptr){}

OctTree::~OctTree() {
  std::cout<<"Calling octtree destructor\n";
  delete root;
  delete solid;
}

void OctTree::initOctTree(){
  double dmax = solid->dMax();
  Point3 center = solid->getCenter();
  double halfdMax = dmax / 2.0;
  Point3 TLB = Point3(center.x() - halfdMax,center.y() + halfdMax, center.z() - halfdMax);

  Point3 BRF = Point3(center.x() + halfdMax,center.y() - halfdMax, center.z() + halfdMax);

  Box * box = new Box(TLB,BRF);
  root = new Node(nullptr,box);
  std::cout<<"entering makeOctTree\n";
  makeOctTree(root,maxDepth);
  std::cout<<"exiting makeOctTree within initOctTree\n";
  printOctTree(root);
}

void OctTree::makeOctTree(Node * child, int depth) {
  Node* root = child;
  // std::cout<<"=====current depth is "<< depth <<"==========\n";
  root->setState(State::BLACK);
  std::cout<<"setState done\n";
  if (depth>1){
    solid->classify(root);
    std::cout<<"classify done\n"; 
    if (root->getState()==State::GRAY){
      subdivide(root);
      std::cout<<"subdivide done\n";
      std::cout<<"==//====//====//==";
      std::cout<<"doing 8 children";
      std::cout<<"==//====//====//==\n";
      for (int i=0; i<8; i++){
        makeOctTree(root->getChild(i), depth-1);
      }
      std::cout<<"==//====//====//==";
      std::cout<<"8 children done";
      std::cout<<"==//====//====//==\n";
    }
  }
}

void OctTree::subdivide(Node * node) {
  
  Box *parentBox = node->getBox(); 
  calcBox(node, parentBox->getTLB(), parentBox->getBRF(), 3);

}

Node * OctTree::getRoot(){
  return root;
}

int OctTree::getMaxDepth() const {
  return maxDepth;
}

void OctTree::calcBox(Node* node, Point3 TLB, Point3 BRF, uint8_t depth) {
  Point3 new_TLB, new_BRF;
  
  if(depth == 0){
    Box * box = new Box(TLB, BRF);
    Node * child = new Node(node, box); 
    node->setChild(child);
    return;
  }

  divideBox(TLB, BRF, new_TLB, new_BRF, depth);
  calcBox(node, new_TLB, BRF, depth-1);
  calcBox(node, TLB, new_BRF, depth-1);
}

// Caso 3: Plano xy, divide o z ao meio
// Caso 2: Plano xz, divide o y ao meio
// Caso 1: plano yz, divide o x ao meio

void OctTree::divideBox(const Point3 &TLB, const Point3 &BRF, Point3 &new_TLB, Point3 &new_BRF, uint8_t depth){
  int coord = depth - 1;
  double l = TLB[coord] - BRF[coord];
  new_TLB = TLB;
  new_TLB[coord] = TLB[coord]-(l/2.0);

  new_BRF = BRF;
  new_BRF[coord] = BRF[coord]+(l/2.0);
}

void OctTree::printOctTree(Node * node){
  Point3 tlb = node->getBox()->getTLB();
  Point3 brf = node->getBox()->getBRF();
  std::cout << "(" << tlb.x() << "," << tlb.y() << "," << tlb.z() << ")" << ","; 
  std::cout<<"(" << brf.x() << "," << brf.y() << "," << brf.z() << ")" << ",";
  if(node->getState() != State::GRAY){
    return;
  }
  for(int i = 0;i<8;i++){
    printOctTree(node->getChild(i));
  }
}