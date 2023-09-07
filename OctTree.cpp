#include "OctTree.hpp"



OctTree::OctTree() : solid(nullptr) {}


void OctTree::makeOctTree(Node * child, uint8_t depth){
  Node* root = child;
  State state = State::BLACK;
  if (depth>1){
    state = classify(root->getBox());
    root->setState(state);
    if (state==State::PARTIAL){
      subdivide(root);
      for (int i=0; i<8; i++){
        makeOctTree(root->getChild(i), depth-1);
      }
    }
  }
}

State OctTree::classify(Box * box){
  return State::WHITE;
}

void OctTree::subdivide(Node * node){
}

