#ifndef NODE_H
#define NODE_H
#include <vector>
#include "vec3.hpp"
#include "Box.hpp"


enum class State{
    BLACK,
    WHITE,
    PARTIAL
};

class Node{
	public:   
		Node();
		State getState();
		Node * getParent();
		Node * getChild(int index);
		Box * getBox();
		void setState(State state);
    void setParent(Node * parent);
    void setChild(Node * child, int index);
    void setBox(Box* box);
    
    
  //operators  
  public:  
    Node & operator=(Node & n){
			state = n.getState();
			parent = n.getParent();
			if(n.getState() == State::PARTIAL){
			  for(int i = 0; i < 8; i++){
          children[i] = n.getChild(i);
        }
      }
      return *this;
    }

  private:
		State state;
    Node * parent;
    Box * box;
    std::vector<Node*> children;

};

inline void Node::setChild(Node * child, int index){
	this->children[index] = child;
};

inline void Node::setState(State state){
	this->state = state;
};

inline void Node::setParent(Node * parent){
	this->parent = parent;
};

inline void Node::setBox(Box * Box){
	this->box = box;
};

#endif