#include "TestSolid.hpp"

TestSolid::TestSolid(){}

TestSolid::~TestSolid(){}

void TestSolid::classify(Node * node){
  std::cout<<"opa\n";
  node->setState(State::GRAY);
}

double TestSolid::dMax(){
  return 5.0;
}

Point3 TestSolid::getCenter(){
  return Point3(0.0,0.0,0.0);
}