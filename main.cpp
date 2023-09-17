#include "OctTree.hpp"
#include "Node.hpp"
#include "TestSolid.hpp"
#include <iostream>
int main(){
	OctTree * oct = new OctTree(2);
	TestSolid * ts = new TestSolid();
  oct->setSolid(ts);
	oct->initOctTree();
  std::cout<<"depois de makeOctTree\n";
  return 0;
}