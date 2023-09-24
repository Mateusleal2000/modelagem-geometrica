#include "Box.hpp"

Box::Box(){}


Box::Box(Point3 tlb, Point3 brf){
  top_left_back = tlb;
  bottom_right_front = brf;
}

Point3 Box::getPoint(int label){
  return boxPoints[label];
}


double Box::getBmin(int axis){
  double min = top_left_back[axis] <= bottom_right_front[axis] ? top_left_back[axis] : bottom_right_front[axis];
  return min;
}


double Box::getBmax(int axis){
  double max = top_left_back[axis] > bottom_right_front[axis] ? top_left_back[axis] : bottom_right_front[axis];
  return max;
}