#include "Node.hpp"

Node::Node() : parent(nullptr) , box(nullptr){
  children.reserve(8);
}

Node::Node(Node * parent, Box * box) : parent(parent), box(box) {
  children.reserve(8);
}

Node::~Node(){
  for(int i = 0;i < children.size();++i){
    delete children[i];
  }
  delete box;
}


Node* Node::getChild(int index){
  return children[index];
}
State Node::getState(){
    return state;
}
Node* Node::getParent(){
  return parent;
}

Box * Node::getBox(){
	return box;
}
