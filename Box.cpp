#include "Box.hpp"

Box::Box(){}


Box::Box(Point3 tlb, Point3 brf){
  top_left_back = tlb;
  bottom_right_front = brf;
}

Point3 & Box::getBRF(){
  return bottom_right_front;
}

Point3 & Box::getTLB(){
  return top_left_back;
}

double Box::getBmin(int axis){
  double min = top_left_back[axis] <= bottom_right_front[axis] ? top_left_back[axis] : bottom_right_front[axis];
  return min;
}


double Box::getBmax(int axis){
  double max = top_left_back[axis] > bottom_right_front[axis] ? top_left_back[axis] : bottom_right_front[axis];
  return max;
}