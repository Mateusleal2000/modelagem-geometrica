#include "OctTree.hpp"
#include "Node.hpp"
#include "TestSolid.hpp"
#include <iostream>
int main(){
	Node root = Node();
	OctTree oct = OctTree(2);
	TestSolid ts = TestSolid();
  oct.setSolid(&ts);
	oct.initOctTree();
  std::cout<<"depois de makeOctTree\n";
  return 0;
}