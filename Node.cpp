#include "Node.hpp"

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


