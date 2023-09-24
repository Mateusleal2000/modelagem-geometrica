#include "Node.hpp"

Node::Node() : parent(nullptr) , box(nullptr){
  children.reserve(8);
}

Node::Node(Node * parent, Box * box) : parent(parent), box(box) {
  children.reserve(8);
}

Node::~Node(){
  std::cout<<"Calling Node Destructor\n";
  std::cout<< "Children size: "<< children.size() <<"\n";
  for(int i = 0;i < children.size();++i){
    std::cout<<"deleting child\n";
    delete children[i];
  }
  delete box;
}


void Node::setGlobalVertices(std::unordered_set<Point3> * globalVertices){
  setOfPoints = globalVertices;
  return;
}

void Node::mapPointsToIndex(){
	for(int i = 0;i < 8;i++){
		
    std::unordered_set<Vec3>::iterator it = setOfPoints->find(box->getPoint(i));
    int idx = std::distance(setOfPoints->begin(), it);
    box->setIndex(i,idx);
	}


	for(Node * node : children){
		node->mapPointsToIndex();
	}
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

void Node::deletePoints(){
  delete setOfPoints;
}