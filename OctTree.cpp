#include "OctTree.hpp"

OctTree::OctTree() : solid(nullptr) {}

OctTree::~OctTree() {
  delete root;
  delete solid;
}

void OctTree::makeOctTree(Node * child, uint8_t depth) {
  Node* root = child;
  root->setState(State::BLACK);
  if (depth>1){
    solid->classify(root);
    if (root->getState()==State::PARTIAL){
      subdivide(root);
      for (int i=0; i<8; i++){
        makeOctTree(root->getChild(i), depth-1);
      }
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

void calcBox(Node* node, Point3 TLB, Point3 BRF, uint8_t depth) {
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

void divideBox(const Point3 &TLB, const Point3 &BRF, Point3 &new_TLB, Point3 &new_BRF, uint8_t depth){
  int coord = depth - 1;
  double l = TLB[coord] - BRF[coord];
  new_TLB = TLB;
  new_TLB[coord] = TLB[coord]-(l/2.0);

  new_BRF = BRF;
  new_BRF[coord] = BRF[coord]+(l/2.0);
}
