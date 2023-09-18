#include "OctTree.hpp"
#include "Node.hpp"
#include "TestSolid.hpp"
#include "Sphere.hpp"
#include <iostream>
#include <fstream>
int main(){
	OctTree * oct = new OctTree(7);
	// TestSolid * ts = new TestSolid();
  Sphere * sp = new Sphere(5.0, Point3(0.0,0.0,0.0));
  oct->setSolid(sp);
	oct->initOctTree();
  std::cout<<"depois de makeOctTree\n";
  // std::ofstream OUTFILE;
  // OUTFILE.open("esfera.obj");
  // OUTFILE << "o " << "esfera" << std::endl;
  
  return 0;
}